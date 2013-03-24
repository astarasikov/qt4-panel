#include "mainwidget.h"
#include "global_defines.h"
#include "panelbutton.h"
#include "launcherhandler.h"
#include "imageprovider.h"
#include "testapplet.h"
#include "stackfolderapplet.h"
#include "trashbinapplet.h"

#include <QGraphicsObject>
#include <QDesktopWidget>

#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeItem>
#include <QDeclarativeEngine>

#include <QContextMenuEvent>

RocketBar::MainWidget::MainWidget(
        RocketBar::Context *config, QWidget *parent)
    : QDeclarativeView(parent), mContext(config),
      mAppletList(QList<QObject*> ())
{
    /* initialize a borderless panel window */
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("border-style: none;background:transparent;");
    setResizeMode(QDeclarativeView::SizeRootObjectToView);
    buildMenu();

    engine()->addImageProvider(QLatin1String("xdg"), mContext->mImageProvider);
    engine()->addImageProvider(QLatin1String("task"),
                               mContext->mWindowManager->taskImageProvider());
    engine()->addImageProvider(QLatin1String("applet"),
                               mContext->mAppletImageProvider);

    updateWindow();
    connect(mContext->mWindowManager,
            SIGNAL(windowsChanged(WindowManager::WindowList&)),
            this, SLOT(updateWindows(WindowManager::WindowList&)));
}

RocketBar::MainWidget::~MainWidget() {

}

void RocketBar::MainWidget::updateWindow() {
    screenRect = QApplication::desktop()->screenGeometry();

    int x(0), y(0), w(0), h(0);
    RocketBar::ScreenEdge o = mContext->screenEdge();
    RocketBar::PanelLayout l = RocketBar::Panel_Horizontal;
    switch (o) {
    case RocketBar::Screen_Bottom:
        h = RocketBar::DefaultPanelHeight;
        y = screenRect.height() - h;
        w = screenRect.width();
        break;
    case RocketBar::Screen_Top:
        h = RocketBar::DefaultPanelHeight;
        w = screenRect.width();
        break;
    case RocketBar::Screen_Left:
        w = RocketBar::DefaultPanelWidth;
        h = screenRect.height();
        l = RocketBar::Panel_Vertical;
        break;
    case RocketBar::Screen_Right:
        w = RocketBar::DefaultPanelWidth;
        x = screenRect.width() - w;
        h = screenRect.height();
        l = RocketBar::Panel_Vertical;
        break;
    }

    if (l == RocketBar::Panel_Horizontal) {
        setSource(mContext->themeManager().qml(ThemeManager::PANEL));
    }
    else {
        setSource(mContext->themeManager().qml(ThemeManager::PANEL_VERTICAL));
    }

    //XXX: wtf is this?
    rootContext()->setContextProperty("rootPanel", this);
    rootContext()->setContextProperty("width", this->width());
    rootContext()->setContextProperty("height", this->height());
    move(x, y);

    buildLauncher();
    buildApplets();
}

void RocketBar::MainWidget::updateWindows
(RocketBar::WindowManager::WindowList &list)
{
    QVariant v = rootContext()->contextProperty("taskListModel");
    QList<QObject*> oldList = v.value<QList<QObject*> >();
    foreach(QObject *handler, oldList) {
        delete handler;
    }
    oldList.clear();

    rootContext()->setContextProperty("tasksListModel",
        QVariant::fromValue(list));
}

void RocketBar::MainWidget::changeTheme()
{
    static int idx=0;
    RocketBar::ThemeManager& themeManager = mContext->themeManager();
    themeManager.update();
    QList<QString> themes = themeManager.themes();
    if (themes.length()) {
        idx = (idx + 1) % themes.length();
        themeManager.setTheme(themes.at(idx));
    }
    updateWindow();
}

void RocketBar::MainWidget::buildMenu(void) {
    mContextMenu = new QMenu(this);

    QAction *aQuit = new QAction(tr("&Quit"), this);
    connect(aQuit, SIGNAL(triggered()), this, SLOT(close()));

    QAction *aRefresh = new QAction(tr("&Refresh"), this);
    connect(aRefresh, SIGNAL(triggered()), this, SLOT(updateWindow()));

    QAction *aTheme = new QAction(tr("&Change Theme"), this);
    connect(aTheme, SIGNAL(triggered()), this, SLOT(changeTheme()));

    mContextMenu->addSeparator();
    mContextMenu->addAction(aQuit);
    mContextMenu->addAction(aRefresh);
    mContextMenu->addAction(aTheme);
}

void RocketBar::MainWidget::buildLauncher()
{
    QList<QObject*> launcherList;

    //XXX: it sucks
    launcherList.append(new LauncherHandler("konsole",
        "/usr/bin/konsole"));
    launcherList.append(new LauncherHandler("x-terminal-emulator",
        "/usr/bin/chromium"));
    launcherList.append(new LauncherHandler("konqueror",
        "/usr/bin/konqueror"));

    rootContext()->setContextProperty("launcherListModel",
                                      QVariant::fromValue(launcherList));
}

void RocketBar::MainWidget::buildApplets()
{
    if (mAppletList.isEmpty()) {
        StackFolderApplet *sfapplet = new StackFolderApplet();
        connect(sfapplet, SIGNAL(imageChanged()), this, SLOT(updateAppletDisplay()));
        mAppletList.append(sfapplet);

        TrashBinApplet *trashapplet = new TrashBinApplet();
        connect(trashapplet, SIGNAL(imageChanged()), this, SLOT(updateAppletDisplay()));
        mAppletList.append(trashapplet);

        for (int i = 0; i < 3; i++) {
            TestApplet *applet = new TestApplet();
            connect(applet, SIGNAL(imageChanged()), this, SLOT(updateAppletDisplay()));
            mAppletList.append(applet);
        }
    }
    updateAppletDisplay();
}

void RocketBar::MainWidget::contextMenuHandler(int x, int y){
    QPoint p(x,y);
    QPoint globalPos = mapToGlobal(p);
    mContextMenu->popup(globalPos);
}

void RocketBar::MainWidget::updateAppletDisplay()
{
    foreach (QObject *o, mAppletList) {
        Applet *a = reinterpret_cast<Applet*>(o);
        mContext->mAppletImageProvider->update(a->name(), a->image());
    }
    rootContext()->setContextProperty("appletListModel",
                                      QVariant::fromValue(mAppletList));
}

QRect RocketBar::MainWidget::getScreenRect(){
    return screenRect;
}
