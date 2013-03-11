#include "windowmanager.h"

#if defined(ROCKETBAR_WM_X11)
#include "windowmanagerx11.h"
#elif defined(ROCKETBAR_WM_STUB)
#include "windowmanagerstub.h"
#endif

RocketBar::WindowManager* RocketBar::getWindowManager(void)
{
#if defined(ROCKETBAR_WM_X11)
    return RocketBar::WindowManagerX11::instance();
#elif defined(ROCKETBAR_WM_STUB)
    return new RocketBar::WindowManagerStub();
#endif
    return NULL;
}


RocketBar::WindowManager::WindowManager()
{
}

RocketBar::WindowManager::~WindowManager()
{
}

