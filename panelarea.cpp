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

    qsrand(QTime::currentTime().msec());
    int rd = qrand() % 8;

    unsigned r = !!(rd & 1) * 255;
    unsigned g = !!(rd & 2) * 255;
    unsigned b = !!(rd & 4) * 255;
    QColor c(r, g, b);

    painter.fillRect(0, 0, width(), height(), c);
}
