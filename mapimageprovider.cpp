#include "mapimageprovider.h"

RocketBar::MapImageProvider::MapImageProvider()
    : QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
{
}

QImage RocketBar::MapImageProvider::requestImage(const QString &id,
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

void RocketBar::MapImageProvider::invalidate()
{
    mImageMap.clear();
}


void RocketBar::MapImageProvider::update(QString name, QImage image)
{
    mImageMap[name] = image;
}

void RocketBar::MapImageProvider::remove(QString name)
{
    mImageMap.remove(name);
}
