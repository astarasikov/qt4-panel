#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDeclarativeView>
#include <QDeclarativeComponent>
#include <QMenu>
#include "context.h"
#include "windowmanager.h"

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

    void buildMenu();
    void buildLauncher();

protected slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void updateWindow();

public slots:
    void updateWindows(WindowManager::WindowList &list);
};

} //namespace RocketBar

#endif // MAINWIDGET_H
