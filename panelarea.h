#ifndef PANELAREA_H
#define PANELAREA_H

#include <QWidget>
#include <QPaintEvent>

namespace RocketBar {

class PanelArea : public QWidget
{
    Q_OBJECT
public:
    explicit PanelArea(QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *evt);

signals:

public slots:

};

}

#endif // PANELAREA_H
