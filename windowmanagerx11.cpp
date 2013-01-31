#include "windowmanagerx11.h"

#include <QDebug>

#include <QtGui/QX11Info>
#include <QMap>

#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xdamage.h>

#define FLOG do { qDebug() << "[WindowManagerX11]: " << __func__; } while (0)

class RocketBar::WindowManagerX11::Window::X11WindowData {
public:
    ::Window mWindow;

    X11WindowData(::Window window)
        : mWindow(window)
    {}
};

class RocketBar::WindowManagerX11::X11WindowManagerData {
public:
    typedef QMap<QString, ::Atom> AtomMap;

    X11WindowManagerData() : mAtomCache(AtomMap()) {}

    ::Atom atom(const QString &name) {
        if (!mAtomCache.contains(name)) {
            mAtomCache[name] = XInternAtom(QX11Info::display(),
                name.toLatin1().data(), False);
        }
        return mAtomCache[name];
    }

protected:
    AtomMap mAtomCache;
};

static RocketBar::WindowManagerX11 *gWindowManagerX11Instance = NULL;

RocketBar::WindowManagerX11 *RocketBar::WindowManagerX11::instance()
{
    if (!gWindowManagerX11Instance) {
        gWindowManagerX11Instance = new WindowManagerX11();
    }
    return gWindowManagerX11Instance;
}

template <class T>
static bool propertyHelper(::Window window, ::Atom atom,
                           ::Atom type, unsigned long &numItems, T** data) {
    ::Atom returnType;
    int returnFormat;

    unsigned long numItemsTemp;
    unsigned long numBytes;

    int ret = XGetWindowProperty(QX11Info::display(),
                                 window, atom,
                                 0, 0x7fffffff,
                                 False, type,
                                 &returnType, &returnFormat,
                                 &numItemsTemp, &numBytes,
                                 reinterpret_cast<unsigned char **>(data));
    if (ret != Success) {
        return false;
    }

    numItems = numItemsTemp;
    if (!numItems) {
        return false;
    }

    return true;
}

::Atom atom(const QString &name) {
    return gWindowManagerX11Instance->data()->atom(name);
}

static QString propertyUTF8String(::Window window, const QString &name) {
    unsigned long nItems;
    char *data;
    QString value;
    if (!propertyHelper(window, atom(name), atom("UTF8_STRING"), nItems, &data)) {
        return value;
    }
    value = QString::fromUtf8(data);
    XFree(data);
    return value;
}

static QString propertyLatin1String(::Window window, const QString &name) {
    unsigned long nItems;
    char *data;
    QString value;
    if (!propertyHelper(window, atom(name), XA_STRING, nItems, &data)) {
        return value;
    }
    value = QString::fromLatin1(data);
    XFree(data);
    return value;
}

static void sendNETWMMessage(::Window window, const QString& name,
                             unsigned long l0 = 0, unsigned long l1 = 0,
                             unsigned long l2 = 0, unsigned long l3 = 0,
                             unsigned long l4 = 0)
{
    XClientMessageEvent event;
    event.type = ClientMessage;
    event.window = window;
    event.message_type = atom(name);
    event.format = 32;
    event.data.l[0] = l0;
    event.data.l[1] = l1;
    event.data.l[2] = l2;
    event.data.l[3] = l3;
    event.data.l[4] = l4;

    ::Display *display = QX11Info::display();
    ::Window root = DefaultRootWindow(display);
    XSendEvent(QX11Info::display(), root, False,
               SubstructureNotifyMask | SubstructureRedirectMask,
               reinterpret_cast<XEvent*>(&event));
}

RocketBar::WindowManagerX11::WindowManagerX11()
    : mWindows(WindowList()),
      mData(new WindowManagerX11::X11WindowManagerData())
{
    FLOG;

    //use :: to access X11 definitons from the global namespace
    ::Display *display = QX11Info::display();
    ::Window root = DefaultRootWindow(display);
    ::Window dummy;

    ::Window *children;
    unsigned int nChildren = 0;
    if (!XQueryTree(display, root, &dummy, &dummy, &children, &nChildren)) {
        return;
    }

    for (unsigned i = 0; i < nChildren; i++) {
        ::XWindowAttributes wa;
        if (!XGetWindowAttributes(display, children[i], &wa)) {
            continue;
        }
        if (wa.map_state != IsViewable) {
            continue;
        }

        Window::X11WindowData *data = new Window::X11WindowData(children[i]);
        mWindows.append(new Window(data));
    }
}

RocketBar::WindowManagerX11::Window::Window(X11WindowData *data)
    : mData(data)
{
    FLOG;
}

RocketBar::WindowManagerX11::Window::~Window()
{
    FLOG;
    delete mData;
}

void RocketBar::WindowManagerX11::Window::activate()
{
    XWindowChanges wc;
    wc.stack_mode = Above;
    XConfigureWindow(QX11Info::display(), mData->mWindow, CWStackMode, &wc);

    sendNETWMMessage(mData->mWindow, "_NET_ACTIVE_WINDOW", 2, CurrentTime);
}

void RocketBar::WindowManagerX11::Window::minimize()
{
    XIconifyWindow(QX11Info::display(), mData->mWindow, QX11Info::appScreen());
}

void RocketBar::WindowManagerX11::Window::map()
{
    XMapWindow(QX11Info::display(), mData->mWindow);
}

void RocketBar::WindowManagerX11::Window::close()
{
    sendNETWMMessage(mData->mWindow, "_NET_CLOSE_WINDOW", CurrentTime, 2);
}

void RocketBar::WindowManagerX11::Window::kill()
{
    XKillClient(QX11Info::display(), mData->mWindow);
}

void RocketBar::WindowManagerX11::Window::destroy()
{
    XDestroyWindow(QX11Info::display(), mData->mWindow);
}

void RocketBar::WindowManagerX11::Window::setParent(RocketBar::WindowManager::Window *parent)
{
    FLOG;
}

QString RocketBar::WindowManagerX11::Window::getTitle()
{
    ::Window wnd = mData->mWindow;
    QString result = propertyUTF8String(wnd, "_NET_WM_VISIBLE_NAME");
    if (!result.isEmpty()) {
        return result;
    }

    result = propertyUTF8String(wnd, "_NET_WM_NAME");
    if (!result.isEmpty()) {
        return result;
    }

    result = propertyLatin1String(wnd, "WM_NAME");
    if (!result.isEmpty()) {
        return result;
    }

    return QString("<Unknown>");
}

QImage RocketBar::WindowManagerX11::Window::getIcon()
{
    unsigned long nItems;
    ::Atom *data = 0;
    QImage image;
    if (!propertyHelper(mData->mWindow, atom("_NET_WM_ICON"), XA_CARDINAL,
                        nItems, &data)) {
        return image;
    }

    ::Atom *_data = data;
    long long _nItems = nItems;
    while (_data && _nItems > 0) {
        unsigned width = static_cast<unsigned>(data[0]);
        unsigned height = static_cast<unsigned>(data[1]);
        if (!width || !height) {
            break;
        }
        QImage _image(width, height, QImage::Format_ARGB32);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
               image.setPixel(j, i,
                    static_cast<unsigned int>(_data[i * width + j]));
            }
        }
        _data += width * height;
        _nItems -= (2 + width * height);
        if (_image.width() > image.width()) {
            image = _image;
        }
    }

    if (data) {
        XFree(data);
    }
    return image;
}

RocketBar::WindowManager::WindowList &RocketBar::WindowManagerX11::getWindows()
{
    FLOG;
    return mWindows;
}

RocketBar::WindowManagerX11::X11WindowManagerData *RocketBar::WindowManagerX11::data() const
{
    return mData;
}

RocketBar::WindowManagerX11::~WindowManagerX11()
{
    FLOG;
}
