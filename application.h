#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QSharedMemory>

#include "context.h"
#include "global_defines.h"

namespace RocketBar {

class AppLock {
protected:
    QSharedMemory *mSharedMem;
public:
    AppLock() : mSharedMem(new QSharedMemory(RocketBar::ApplicationName)){
        if (mSharedMem->attach(QSharedMemory::ReadOnly)) {
            mSharedMem->detach();
        }

        if (mSharedMem->create(1)) {
            return;
        }

        qDebug() << "already running, not launching second instance";
        ::exit(0);
    }
};

class Application : public QApplication
{
    Q_OBJECT
protected:
    Context *mContext;
    QWidget *mWidget;

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
