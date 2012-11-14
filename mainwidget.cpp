#include "mainwidget.h"
#include "config.h"

/* Qt Includes */
#include <QApplication>
#include <QDesktopWidget>

#include <QPainter>

#include <QMouseEvent>

#include <QDebug>

#include <QGridLayout>

/* local includes */
#include "panelarea.h"

RocketBar::MainWidget::MainWidget(
        RocketBar::Config *config, QWidget *parent)
    : QWidget(parent), mConfig(config)
{
    QRect screenRect = QApplication::desktop()->screenGeometry();

    setFixedSize(screenRect.width(), 50);
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //position
    move(0, screenRect.height() - height());

#ifdef Q_WS_X11
    //XXX: do we need it?
    qDebug() << "running on X11";
    //setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
#endif
    updateWindow();

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(new RocketBar::PanelArea(this), 0, 0);
    grid->addWidget(new RocketBar::PanelArea(this), 0, 1);
    grid->addWidget(new RocketBar::PanelArea(this), 0, 2);

    setLayout(grid);
}

RocketBar::MainWidget::~MainWidget()
{
}

void RocketBar::MainWidget::updateWindow() {
    setWindowOpacity(mConfig->debugEnabled() ? 0.7 : 1);
}

void RocketBar::MainWidget::paintEvent(QPaintEvent *evt) {
    if (!mConfig->debugEnabled()) {
        return;
    }

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::red);
}

void RocketBar::MainWidget::mousePressEvent(QMouseEvent *evt) {
    mConfig->toggleDebug();
    updateWindow();
    repaint();
}
