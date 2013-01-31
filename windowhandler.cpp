#include "windowhandler.h"

RocketBar::WindowHandler::WindowHandler(RocketBar::WindowManager::Window* window)
    :mWindow(window) {}

QString RocketBar::WindowHandler::title() const
{
    return mWindow->getTitle();
}

void RocketBar::WindowHandler::handle()
{
    mWindow->close();
}
