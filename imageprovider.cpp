#include "imageprovider.h"

#include <QDebug>
#include <QIcon>

RocketBar::ImageProvider::ImageProvider(
        QDeclarativeImageProvider::ImageType type)
    : QDeclarativeImageProvider(type)
{
}

QPixmap RocketBar::ImageProvider::requestPixmap(const QString &id,
    QSize *size, const QSize &requestedSize)
{
    QIcon icon = QIcon::fromTheme(id);
    QPixmap pixmap = icon.pixmap(32, 32);
    foreach (QSize s, icon.availableSizes()) {
        if (s.width() == size->width() || s.height() == size->height()) {
            pixmap = icon.pixmap(s);
        }
    }
    *size = pixmap.size();
    return pixmap;
}
