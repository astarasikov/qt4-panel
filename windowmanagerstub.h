#ifndef WINDOWMANAGERSTUB_H
#define WINDOWMANAGERSTUB_H

#include "windowmanager.h"

namespace RocketBar {

class WindowManagerStub : public RocketBar::WindowManager
{
public:
    class Window : public RocketBar::WindowManager::Window {
    public:
        Window(QString name, QIcon icon);

        void activate(void);
        void minimize(void);
        void map(void);
        void close(void);
        void kill(void);
        void destroy(void);
        void setParent(WindowManager::Window *parent);
        QString getTitle(void);
        QIcon getIcon(void);
    protected:
        QString mName;
        QIcon mIcon;
        bool mIsAlive;
        bool mIsActivated;
        bool mIsMapped;
    };

    WindowManagerStub();
    ~WindowManagerStub();

    WindowList &getWindows(void);
protected:
    WindowList mWindows;
};

}

#endif // WINDOWMANAGERSTUB_H
