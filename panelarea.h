#ifndef PANELAREA_H
#define PANELAREA_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "layout.h"

namespace RocketBar {

class PanelArea : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PanelArea(QWidget *parent = 0);
    void relayout(RocketBar::PanelLayout);

protected:
    QGraphicsScene *mScene;

signals:

public slots:
};

}

#endif // PANELAREA_H
