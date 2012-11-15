#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsItem>

#include "layout.h"

namespace RocketBar{

class Element : public QGraphicsItem
{
public:
    Element();

    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    virtual QRectF boundingRect(void) const ;

    void relayout(RocketBar::PanelLayout l) {

    }
};

} //namespace RocketBar

#endif // ELEMENT_H
