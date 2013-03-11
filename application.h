#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "context.h"

namespace RocketBar {

class Application : public QApplication
{
    Q_OBJECT
protected:
    Context *mContext;

public:
    Application(int argc, char *argv[]);
    ~Application();
    int run();

#ifdef ROCKETBAR_WM_X11
    bool x11EventFilter(XEvent *);
#endif
};

} //namespace RocketBar

#endif // ROCKETBARAPPLICATION_H
