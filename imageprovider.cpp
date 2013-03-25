#include <QDebug>
#include <QIcon>
#include <QFile>

#include "imageprovider.h"
#include "global_defines.h"

RocketBar::ImageProvider::ImageProvider(
        QDeclarativeImageProvider::ImageType type)
    : QDeclarativeImageProvider(type)
{
}

QPixmap RocketBar::ImageProvider::requestPixmap(const QString &id,
    QSize *size, const QSize &requestedSize)
{
    int sz = RocketBar::DefaultIconSize;
    QIcon icon;
    if (QFile(id).exists()) {
        icon = QIcon(id);
    }
    else {
        icon = QIcon::fromTheme(id);
    }
    QPixmap pixmap = icon.pixmap(sz, sz);
    foreach (QSize s, icon.availableSizes()) {
        if (s.width() == requestedSize.width() || s.height() == requestedSize.height()) {
            pixmap = icon.pixmap(s);
        }
    }
    *size = pixmap.size();
    return pixmap;
}
