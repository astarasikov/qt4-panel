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
      mLauncherList(QList<QObject*>()),
      mAppletList(QList<QObject*> ())
{
    /* initialize a borderless panel window */
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    setStyleSheet("border-style: none;background:transparent;");
    setResizeMode(QDeclarativeView::SizeRootObjectToView);

    engine()->addImageProvider(QLatin1String("xdg"), mContext->mImageProvider);
    engine()->addImageProvider(QLatin1String("task"),
                               mContext->mWindowManager->taskImageProvider());
    engine()->addImageProvider(QLatin1String("applet"),
                               mContext->mAppletImageProvider);

    buildMenu();
    buildLauncher();
    buildApplets();

    updateWindow();
    connect(mContext->mWindowManager,
            SIGNAL(windowsChanged(WindowManager::WindowList&)),
            this, SLOT(updateWindows(WindowManager::WindowList&)));
}

RocketBar::MainWidget::~MainWidget() {
    foreach(QObject *o, mAppletList) {
        delete o;
    }
    mAppletList.clear();
    delete mContextMenu;
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

    resize(w, h);
    move(x, y);

    //XXX: wtf is this?
    rootContext()->setContextProperty("mainWidget", this);
    rootContext()->setContextProperty("width", this->width());
    rootContext()->setContextProperty("height", this->height());

    rootContext()->setContextProperty("launcherListModel",
        QVariant::fromValue(mLauncherList));
    updateAppletDisplay();
}

void RocketBar::MainWidget::themeSelected(QAction *a)
{
    mContext->themeManager().setTheme(a->text());
    updateWindow();
}

void RocketBar::MainWidget::setOrientation(QAction *a)
{
    bool ok;
    int side = a->data().toInt(&ok);
    if (!ok) {
        return;
    }
    mContext->setScreenEdge((RocketBar::ScreenEdge)side);
    updateWindow();
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

void RocketBar::MainWidget::buildMenu(void) {
    mContextMenu = new QMenu(this);
    mContextMenu->setStyleSheet("background-color: black; color: white;");

    QAction *aQuit = new QAction(tr("&Quit"), this);
    connect(aQuit, SIGNAL(triggered()), this, SLOT(close()));

    QAction *aRefresh = new QAction(tr("&Refresh"), this);
    connect(aRefresh, SIGNAL(triggered()), this, SLOT(updateWindow()));

    mContextMenu->addSeparator();
    mContextMenu->addAction(aQuit);
    mContextMenu->addAction(aRefresh);

    /* Theme Selector */
    mContextMenu->addSeparator();
    QMenu *themeMenu = new QMenu(tr("Select Theme"), mContextMenu);
    connect(themeMenu, SIGNAL(triggered(QAction*)), this, SLOT(themeSelected(QAction*)));
    mContextMenu->addMenu(themeMenu);

    RocketBar::ThemeManager &themeManager = mContext->themeManager();
    themeManager.update();
    foreach (QString theme, themeManager.themes() << "Default") {
        QAction *aTheme = new QAction(theme, themeMenu);
        themeMenu->addAction(aTheme);
    }

    /* Orientation Selector */
    mContextMenu->addSeparator();
    QMenu *orientationMenu = new QMenu(tr("Panel Orientation"), mContextMenu);
    connect(orientationMenu, SIGNAL(triggered(QAction*)), this, SLOT(setOrientation(QAction*)));
    mContextMenu->addMenu(orientationMenu);
#define MK_ORIENTATION(o) do { \
    QAction *a = new QAction(tr(#o), orientationMenu); \
    int v = int(RocketBar::Screen_ ## o); \
    a->setData(QVariant::fromValue(v)); \
    orientationMenu->addAction(a); \
} while (0)

    MK_ORIENTATION(Bottom);
    MK_ORIENTATION(Top);
    MK_ORIENTATION(Left);
    MK_ORIENTATION(Right);

#undef MK_ORIENTATION
}

void RocketBar::MainWidget::buildLauncher()
{
    QList<QObject*> launcherList = RocketBar::LauncherHandler::availableApps();
    launcherList.insert(0, new RocketBar::LauncherHandler("rosa-simplelauncher", "rosa-simplelauncher"));
    mLauncherList.append(launcherList);
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

QRect RocketBar::MainWidget::getScreenRect() {
    return screenRect;
}
