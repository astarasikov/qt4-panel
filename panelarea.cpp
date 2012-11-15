#include "panelarea.h"

#include <QPainter>
#include <QTime>

#include <QDebug>

RocketBar::PanelArea::PanelArea(QWidget *parent) :
    QWidget(parent)
{
}

void RocketBar::PanelArea::paintEvent(QPaintEvent *evt) {
    QPainter painter(this);

    int w = width();
    int h = height();

    painter.fillRect(0, 0, w, h, Qt::white);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, w - 1, h - 1);
}
