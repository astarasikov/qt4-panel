#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDeclarativeView>
#include <QDeclarativeComponent>
#include <QMenu>
#include "context.h"

namespace RocketBar {

class MainWidget : public QDeclarativeView
{
    Q_OBJECT
public:
    explicit MainWidget(RocketBar::Context* context, QWidget *parent = 0);
    ~MainWidget();

protected:
    RocketBar::Context *mContext;
    QMenu *mContextMenu;

    void updateWindow();
    void buildMenu();

protected slots:
    void contextMenuEvent(QContextMenuEvent *event);
};

} //namespace RocketBar

#endif // MAINWIDGET_H
