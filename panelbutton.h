#ifndef PANELBUTTON_H
#define PANELBUTTON_H

#include <QDeclarativeItem>

namespace RocketBar {

class PanelButton : public QDeclarativeItem
{
    Q_OBJECT
public:
    PanelButton(QDeclarativeItem *parent = 0);

public slots:
    void clicked();
};

} //namespace RocketBar

#endif // PANELBUTTON_H
