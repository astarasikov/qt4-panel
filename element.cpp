#include "element.h"

#include <QPainter>
#include <QLinearGradient>
#include <QColor>

RocketBar::Element::Element() {

}

static const int w = 20, h = 20;

void RocketBar::Element::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    painter->fillRect(0, 0, w, h, Qt::green);

    QLinearGradient g(0, 0, w, h);
    g.setSpread(QGradient::ReflectSpread);
    g.setColorAt(0.0, QColor(255, 255, 255, 0));
    g.setColorAt(1.0, QColor(255, 255, 255, 128));
    painter->setBrush(QBrush(g));
    painter->drawRect(0, 0, w, h);
}

QRectF RocketBar::Element::boundingRect(void) const {
    return QRectF(0, 0, w, h);
}
