#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDeclarativeView>
#include <QDeclarativeComponent>
#include <QMenu>
#include <QList>
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
    QList<QObject *> mLauncherList;
    QList<QObject *> mAppletList;
    QRect screenRect;

    void buildMenu();
    void buildLauncher();
    void buildApplets();

protected slots:
    void updateWindow();
    void themeSelected(QAction *a);
    void setOrientation(QAction *a);

public slots:
    void updateWindows(WindowManager::WindowList &list);
    void contextMenuHandler(int x, int y);
    void updateAppletDisplay();
    QRect getScreenRect();
};

} //namespace RocketBar

#endif // MAINWIDGET_H
