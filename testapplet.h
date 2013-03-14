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
    QImage image(void);
    QString name();

public slots:
    virtual void handleClick();
    virtual void handleClick(int x, int y);
    virtual void openFile(QListWidgetItem* item);
    virtual void showMenu();
};

} //namespace RocketBar

#endif // TESTAPPLET_H
