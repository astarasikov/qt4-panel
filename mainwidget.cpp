#include "mainwidget.h"
#include "config.h"

/* Qt Includes */
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>

#include <QContextMenuEvent>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>

/* local includes */
#include "panelarea.h"
#include "global_defines.h"
#include "element.h"

RocketBar::MainWidget::MainWidget(
        RocketBar::Config *config, QWidget *parent)
    : QGraphicsView(parent), mConfig(config)
{
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    mScene = new QGraphicsScene(this);
    mScene->addItem(new Element());
    mScene->addItem(new Element());
    mScene->addItem(new Element());

    setScene(mScene);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("border-style: none;");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    buildMenu();
    updateWindow();
}

RocketBar::MainWidget::~MainWidget()
{
    delete mContextMenu;
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

    setFixedSize(w, h);
    move(x, y);

    setWindowOpacity(mConfig->debugEnabled() ? 0.7 : 1);
    relayout(l);
}

void RocketBar::MainWidget::relayout(RocketBar::PanelLayout o) {
    int w = width();
    int h = height();
    QList<QGraphicsItem*> lst = mScene->items();
    int itemCount = lst.size();

    int i = 0;
    foreach (QGraphicsItem* it, mScene->items()) {
        if (o == RocketBar::Panel_Horizontal) {
            int maxWidth = (1.0 * w) / itemCount;
            it->setPos(i * maxWidth, 0);
        }
        else {
            it->setPos(0, (i * 1.0f * h) / itemCount);
        }
        i++;
    }
}

void RocketBar::MainWidget::cycleOrientation(void) {
    RocketBar::ScreenEdge o = mConfig->screenEdge();
    o = static_cast<RocketBar::ScreenEdge>((o + 1) % 4);
    mConfig->setScreenEdge(o);
    updateWindow();
    repaint();
}

void RocketBar::MainWidget::toggleDebug(void) {
    mConfig->toggleDebug();
    updateWindow();
    repaint();
}

void RocketBar::MainWidget::contextMenuEvent(QContextMenuEvent *evt) {
    QPoint p(this->x() + evt->x(), this->y() + evt->y());
    evt->accept();
    mContextMenu->popup(p);
}

