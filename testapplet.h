#ifndef TESTAPPLET_H
#define TESTAPPLET_H

#include "applet.h"
#include <QMenu>
#include <QWidget>
#include <QListWidgetItem>

namespace RocketBar {

class TestApplet : public Applet
{
    Q_OBJECT
protected:
    QMenu *mMenu;
    QWidget *mWidget;
    QDir folder;

public:
    TestApplet();
    virtual ~TestApplet();
    virtual QImage image(void);
    virtual QString name();

public slots:
    virtual void handleClick();
    virtual void showMenu();
};

} //namespace RocketBar

#endif // TESTAPPLET_H
