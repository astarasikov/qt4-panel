#include "windowhandler.h"

#include <QMenu>

RocketBar::WindowHandler::WindowHandler(RocketBar::WindowManager::Window* window)
    :mWindow(window)
{
    mMenu = new QMenu();

#define MENU_ACTION(name, slot) do {\
    QAction *a ## slot = new QAction(tr(name), this); \
    connect(a ## slot, SIGNAL(triggered()), this, SLOT(slot())); \
    mMenu->addAction(a ## slot); \
} while (0)

    MENU_ACTION("&Close", close);
    MENU_ACTION("&Destroy", destroy);
    MENU_ACTION("&Kill", kill);
    MENU_ACTION("&Map", map);
    MENU_ACTION("&Activate", activate);
    MENU_ACTION("&Minimize", minimize);
}

RocketBar::WindowHandler::~WindowHandler()
{
    delete mMenu;
}

QString RocketBar::WindowHandler::title() const
{
    return mWindow->getTitle();
}

QImage RocketBar::WindowHandler::icon() const
{
    return mWindow->getIcon();
}

void RocketBar::WindowHandler::handleClick()
{
    mMenu->show();
}

void RocketBar::WindowHandler::close()
{
    mWindow->close();
}

void RocketBar::WindowHandler::destroy()
{
    mWindow->destroy();
}

void RocketBar::WindowHandler::kill()
{
    mWindow->kill();
}

void RocketBar::WindowHandler::map()
{
    mWindow->map();
}

void RocketBar::WindowHandler::activate()
{
    mWindow->activate();
}

void RocketBar::WindowHandler::minimize()
{
    mWindow->minimize();
}
