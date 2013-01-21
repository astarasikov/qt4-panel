#include "windowmanagerstub.h"

#include <QDebug>

#define FLOG do { qDebug() << "[WindowManagerStub]: " << __func__; } while (0)

RocketBar::WindowManagerStub::WindowManagerStub()
    : mWindows(WindowList())
{
    FLOG;
#define MK_WINDOW(x) \
    mWindows.append(new WindowManagerStub::Window(QString(x), QIcon()));

    MK_WINDOW("test1");
    MK_WINDOW("Foo");
    MK_WINDOW("Bar");
    MK_WINDOW("Cool Stuff");
}

RocketBar::WindowManagerStub::Window::Window(QString name, QIcon icon)
    : mName(name),
      mIcon(icon),
      mIsAlive(true),
      mIsActivated(false),
      mIsMapped(false)
{
    FLOG;
}

void RocketBar::WindowManagerStub::Window::activate()
{
    FLOG;
    mIsActivated = true;
}

void RocketBar::WindowManagerStub::Window::minimize()
{
    FLOG;
    mIsMapped = false;
}

void RocketBar::WindowManagerStub::Window::map()
{
    FLOG;
    mIsMapped = true;
}

void RocketBar::WindowManagerStub::Window::close()
{
    FLOG;
    mIsActivated = false;
}

void RocketBar::WindowManagerStub::Window::kill()
{
    FLOG;
    mIsAlive = false;
}

void RocketBar::WindowManagerStub::Window::destroy()
{
    FLOG;
    mIsAlive = false;
}

void RocketBar::WindowManagerStub::Window::setParent(RocketBar::WindowManager::Window *parent)
{
    FLOG;
}

QString RocketBar::WindowManagerStub::Window::getTitle()
{
    FLOG;
    return mName;
}

QIcon RocketBar::WindowManagerStub::Window::getIcon()
{
    FLOG;
    return mIcon;
}

RocketBar::WindowManager::WindowList &RocketBar::WindowManagerStub::getWindows()
{
    FLOG;
    return mWindows;
}


RocketBar::WindowManagerStub::~WindowManagerStub()
{
    FLOG;
}
