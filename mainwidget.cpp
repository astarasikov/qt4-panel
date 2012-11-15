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

#include <QHBoxLayout>

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

    mLayout = new QHBoxLayout(this);
    mLayout->addWidget(new PanelArea(this));
    mLayout->addWidget(new PanelArea(this));
    mLayout->addWidget(new PanelArea(this));
    setLayout(mLayout);

    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("border-style: none;");

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
    if (l == RocketBar::Panel_Horizontal) {
        mLayout->setDirection(QHBoxLayout::RightToLeft);
    }
    else {
        mLayout->setDirection(QHBoxLayout::TopToBottom);
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

