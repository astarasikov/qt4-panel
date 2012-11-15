#ifndef RBMAINWIDGET_H
#define RBMAINWIDGET_H

#include <QWidget>
#include <QMenu>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>

#include "config.h"

namespace RocketBar {

class MainWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MainWidget(RocketBar::Config* config, QWidget *parent = 0);
    ~MainWidget();

protected:
    virtual void contextMenuEvent(QContextMenuEvent *);

    void buildMenu(void);

    RocketBar::Config *mConfig;
    QMenu *mContextMenu;
    QHBoxLayout *mLayout;

protected slots:
    void cycleOrientation(void);
    void updateWindow(void);
    void toggleDebug(void);
};

} //namespace RocketBar

#endif // RBMAINWIDGET_H
