#ifndef TESTAPPLET_H
#define TESTAPPLET_H

#include "applet.h"
#include <QMenu>
#include <QWidget>

namespace RocketBar {

class TestApplet : public Applet
{
    Q_OBJECT
protected:
    QMenu *mMenu;
    QWidget *mWidget;

public:
    TestApplet();
    virtual ~TestApplet();
    QImage image(void);
    QString name(void);

public slots:
    virtual void handleClick();
    virtual void showMenu();
};

} //namespace RocketBar

#endif // TESTAPPLET_H
