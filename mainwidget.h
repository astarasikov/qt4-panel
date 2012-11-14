#ifndef RBMAINWIDGET_H
#define RBMAINWIDGET_H

#include <QWidget>

#include "config.h"

namespace RocketBar {

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(RocketBar::Config* config, QWidget *parent = 0);
    ~MainWidget();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);

    void updateWindow(void);
    RocketBar::Config *mConfig;
};

} //namespace RocketBar

#endif // RBMAINWIDGET_H
