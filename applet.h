#ifndef APPLET_H
#define APPLET_H

#include <QObject>

#include "context.h"

namespace RocketBar {

class Applet : public QObject {
    Q_OBJECT

    //Q_PROPERTY(QString iconName)
public:
    Applet();
    virtual ~Applet() = 0;

public slots:
    virtual void clicked(void) = 0;
    virtual void showMenu(void) = 0;
};

} //namespace RocketBar

#endif // APPLET_H
