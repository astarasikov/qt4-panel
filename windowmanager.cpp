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
    : mTaskImageProvider(TaskImageProvider())
{
}

RocketBar::WindowManager::~WindowManager()
{
}

RocketBar::TaskImageProvider *RocketBar::WindowManager::taskImageProvider()
{
    return &mTaskImageProvider;
}

void RocketBar::Window::handleClick()
{
    mMenu->show();
}


RocketBar::TaskImageProvider::TaskImageProvider()
    : QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
{
}

QImage RocketBar::TaskImageProvider::requestImage(const QString &id,
                                                  QSize *size,
                                                  const QSize &requestedSize)
{
    if (mImageMap.contains(id)) {
        QImage img = mImageMap[id];
        *size = img.size();
        return img;
    }
    return QImage();
}

void RocketBar::TaskImageProvider::invalidate()
{
    mImageMap.clear();
}

void RocketBar::TaskImageProvider::update(QString name, QImage image)
{
    mImageMap[name] = image;
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
