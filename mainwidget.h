#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDeclarativeView>
#include <QMenu>
#include "config.h"

namespace RocketBar {

class MainWidget : public QDeclarativeView
{
    Q_OBJECT
public:
    explicit MainWidget(RocketBar::Config* config, QWidget *parent = 0);
    ~MainWidget();

protected:
    RocketBar::Config *mConfig;
    QMenu *mContextMenu;

    void updateWindow();
    void addButton();
    void buildMenu();

protected slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void cycleOrientation(void);
};

} //namespace RocketBar

#endif // MAINWIDGET_H
