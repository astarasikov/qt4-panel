#include "panelarea.h"
#include "element.h"

RocketBar::PanelArea::PanelArea(QWidget *parent) :
    QGraphicsView(parent)
{
    mScene = new QGraphicsScene(this);
    mScene->addItem(new Element());
    mScene->addItem(new Element());
    mScene->addItem(new Element());
    setScene(mScene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
}

void RocketBar::PanelArea::relayout(RocketBar::PanelLayout o) {
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
