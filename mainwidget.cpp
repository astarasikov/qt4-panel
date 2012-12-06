#include "mainwidget.h"
#include "global_defines.h"
#include "panelbutton.h"

#include <QGraphicsObject>
#include <QDesktopWidget>

#include <QDeclarativeComponent>
#include <QDeclarativeItem>

#include <QContextMenuEvent>

RocketBar::MainWidget::MainWidget(
        RocketBar::Config *config, QWidget *parent)
    : QDeclarativeView(parent), mConfig(config)
{
    /* initialize a borderless panel window */
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("border-style: none;");
    buildMenu();

    updateWindow();
}

RocketBar::MainWidget::~MainWidget() {

}

void RocketBar::MainWidget::addButton() {
    QDeclarativeComponent component(engine(), QUrl("qrc:/button.qml"));
    QDeclarativeItem *it = qobject_cast<QDeclarativeItem*>(component.create());
    QDeclarativeItem *launcherArea =
            rootObject()->findChild<QDeclarativeItem*>("tasksArea");
    it->setParentItem(launcherArea);
}

void RocketBar::MainWidget::updateWindow() {
    QRect screenRect = QApplication::desktop()->screenGeometry();

    int x(0), y(0), w(0), h(0);
    RocketBar::ScreenEdge o = mConfig->screenEdge();
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
        setSource(QUrl("qrc:/panel.qml"));
    }
    else {
        setSource(QUrl("qrc:/panel_vertical.qml"));
    }

    QGraphicsObject *root = rootObject();
    root->setProperty("width", w);
    root->setProperty("height", h);
    move(x, y);

    //XXX: this is a hack. should store them to reparent
    for (int i = 0; i < 6; i++) {
        addButton();
    }
}

void RocketBar::MainWidget::cycleOrientation(void) {
    RocketBar::ScreenEdge o = mConfig->screenEdge();
    o = static_cast<RocketBar::ScreenEdge>((o + 1) % 4);
    mConfig->setScreenEdge(o);
    updateWindow();
    repaint();
}

void RocketBar::MainWidget::contextMenuEvent(QContextMenuEvent *evt) {
    QPoint p(this->x() + evt->x(), this->y() + evt->y());
    evt->accept();
    mContextMenu->popup(p);
}

void RocketBar::MainWidget::buildMenu(void) {
    mContextMenu = new QMenu(this);

    QAction *aCycleOrientation = new QAction(tr("Cycle &Orientation"), this);
    connect(aCycleOrientation, SIGNAL(triggered()),
            this, SLOT(cycleOrientation()));

    QAction *aQuit = new QAction(tr("&Quit"), this);
    connect(aQuit, SIGNAL(triggered()), this, SLOT(close()));

    QAction *aToggleDebug = new QAction(tr("Toggle &Debug"), this);
    connect(aToggleDebug, SIGNAL(triggered()), this, SLOT(toggleDebug()));

    mContextMenu->addAction(aCycleOrientation);
    mContextMenu->addAction(aToggleDebug);
    mContextMenu->addSeparator();
    mContextMenu->addAction(aQuit);
}
