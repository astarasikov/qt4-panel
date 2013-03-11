#ifndef WINDOWMANAGERX11_H
#define WINDOWMANAGERX11_H

#include "windowmanager.h"

namespace RocketBar {

class X11Window : public RocketBar::Window {
    Q_OBJECT
public:
    enum WindowState {
        WS_MODAL,
        WS_STICKY,
        WS_MAXIMIZED_VERT,
        WS_WAXIMIZED_HORZ,
        WS_SHADED,
        WS_NORMAL,
    };

    enum WindowType {
        WT_DESKTOP,
        WT_DOCK,
        WT_TOOLBAR,
        WT_MENU,
        WT_NORMAL,
    };

    class X11WindowData;
    void setParent(RocketBar::Window *parent);

    bool PID(quint64 &pid);
    quint64 desktopNumber(void);
    QString windowClass(void);

    enum WindowState windowState(void);
    enum WindowType windowType(void);

    QString title(void);
    QImage icon(void);

    X11Window(X11WindowData *data);
    ~X11Window();
protected:
    X11WindowData *mData;

public slots:
    virtual void handleClick();
    virtual void close();
    virtual void destroy();
    virtual void kill();
    virtual void map();
    virtual void activate();
    virtual void minimize();
};

class WindowManagerX11 : public WindowManager
{
    Q_OBJECT
public:
    virtual ~WindowManagerX11();
    static WindowManagerX11 *instance(void);
    WindowList &getWindows(void);
    quint64 desktopCount(void);
    quint64 currentDesktop(void);
    void event(XEvent *event);

    class X11WindowManagerData;
    X11WindowManagerData *data(void) const;

protected:
    WindowList mWindows;
    X11WindowManagerData *mData;

    WindowManagerX11();
    void updateWindows(void);
};

} //namespace RocketBar

#endif // WINDOWMANAGERX11_H
