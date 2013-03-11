#include "mainwidget.h"
#include "global_defines.h"
#include "panelbutton.h"
#include "windowhandler.h"
#include "launcherhandler.h"
#include "xdgimageprovider.h"

#include <QGraphicsObject>
#include <QDesktopWidget>

#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeItem>
#include <QDeclarativeEngine>

#include <QContextMenuEvent>

RocketBar::MainWidget::MainWidget(
        RocketBar::Context *config, QWidget *parent)
    : QDeclarativeView(parent), mContext(config)
{
    /* initialize a borderless panel window */
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("border-style: none;background:transparent;");
    buildMenu();

    engine()->addImageProvider(QLatin1String("xdg"),
                    new XdgImageProvider(QDeclarativeImageProvider::Pixmap));

    updateWindow();
    connect(mContext->mWindowManager,
            SIGNAL(windowsChanged(WindowManager::WindowList&)),
            this, SLOT(updateWindows(WindowManager::WindowList&)));
}

RocketBar::MainWidget::~MainWidget() {

}

void RocketBar::MainWidget::updateWindow() {
    QRect screenRect = QApplication::desktop()->screenGeometry();

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

    QGraphicsObject *root = rootObject();
    root->setProperty("width", w);
    root->setProperty("height", h);
    move(x, y);

    buildLauncher();
}

void RocketBar::MainWidget::updateWindows
(RocketBar::WindowManager::WindowList &list)
{
    QList<QObject*> windowList;

    QVariant v = rootContext()->contextProperty("taskListModel");
    QList<QObject*> oldList = v.value<QList<QObject*> >();
    foreach(QObject *handler, oldList) {
        delete handler;
    }
    oldList.clear();

    foreach(WindowManager::Window* wnd, list) {
        QString title = wnd->getTitle();
        qDebug() << "Adding " << title;
        WindowHandler *handler = new WindowHandler(wnd);
        windowList.append(handler);
    }

    rootContext()->setContextProperty("tasksListModel",
        QVariant::fromValue(windowList));
}

void RocketBar::MainWidget::contextMenuEvent(QContextMenuEvent *evt) {
    QPoint p(this->x() + evt->x(), this->y() + evt->y());
    evt->accept();
    mContextMenu->popup(p);
}

void RocketBar::MainWidget::buildMenu(void) {
    mContextMenu = new QMenu(this);

    QAction *aQuit = new QAction(tr("&Quit"), this);
    connect(aQuit, SIGNAL(triggered()), this, SLOT(close()));

    QAction *aRefresh = new QAction(tr("&Refresh"), this);
    connect(aRefresh, SIGNAL(triggered()), this, SLOT(updateWindow()));

    mContextMenu->addSeparator();
    mContextMenu->addAction(aQuit);
    mContextMenu->addAction(aRefresh);
}

void RocketBar::MainWidget::buildLauncher()
{
    QList<QObject*> launcherList;

    //XXX: it sucks
    launcherList.append(new LauncherHandler("konsole",
        "/usr/bin/konsole"));
    launcherList.append(new LauncherHandler("firefox",
        "/usr/bin/firefox"));
    launcherList.append(new LauncherHandler("konqueror",
        "/usr/bin/konqueror"));

    rootContext()->setContextProperty("launcherListModel",
        QVariant::fromValue(launcherList));
}
