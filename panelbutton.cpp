#include "panelbutton.h"

RocketBar::PanelButton::PanelButton(QDeclarativeItem *parent)
    : QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void RocketBar::PanelButton::clicked() {
    qDebug() << "RocketBar::PanelButton::clicked()";
}
