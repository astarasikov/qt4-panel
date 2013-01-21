#ifndef WINDOWMANAGERX11_H
#define WINDOWMANAGERX11_H

#include "windowmanager.h"

namespace RocketBar {

class WindowManagerX11 : public WindowManager
{
public:
    class Window : public WindowManager::Window {
    public:
        class X11WindowData;
        void activate(void);
        void minimize(void);
        void map(void);
        void close(void);
        void kill(void);
        void destroy(void);
        void setParent(WindowManager::Window *parent);
        QString getTitle(void);
        QIcon getIcon(void);

        Window(X11WindowData *data);
        ~Window();
    protected:
        X11WindowData *mData;
    };

    static WindowManagerX11 *instance(void);
    ~WindowManagerX11();
    WindowList &getWindows(void);
    class X11WindowManagerData;
    X11WindowManagerData *data(void) const;
protected:
    WindowManagerX11();
    WindowList mWindows;
    X11WindowManagerData *mData;
};

} //namespace RocketBar

#endif // WINDOWMANAGERX11_H
