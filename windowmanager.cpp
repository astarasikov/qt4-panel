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
