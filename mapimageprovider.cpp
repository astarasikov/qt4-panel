#include "mapimageprovider.h"

#include <QDebug>

RocketBar::MapImageProvider::MapImageProvider()
    : QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
{
}

QImage RocketBar::MapImageProvider::requestImage(const QString &id,
                                                 QSize *size,
                                                 const QSize &requestedSize)
{
    Q_UNUSED(requestedSize);
    QString name = id;
    int timeIdx = name.indexOf("|");
    if (timeIdx >= 0) {
        name = name.left(timeIdx);
    }

    if (mImageMap.contains(name)) {
        QImage img = mImageMap[name];
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
