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
    : mTaskImageProvider(MapImageProvider())
{
}

RocketBar::WindowManager::~WindowManager()
{
}

RocketBar::MapImageProvider *RocketBar::WindowManager::taskImageProvider()
{
    return &mTaskImageProvider;
}

RocketBar::Window::Window() : mMenu(new QMenu())
{
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

RocketBar::Window::~Window()
{
    delete mMenu;
}

void RocketBar::Window::handleClick(int x, int y)
{
    mMenu->popup(QPoint(x, y));
}
