#include "xdgimageprovider.h"

#include <QDebug>

RocketBar::XdgImageProvider::XdgImageProvider(
        QDeclarativeImageProvider::ImageType type)
    : QDeclarativeImageProvider(type)
{
}

QPixmap RocketBar::XdgImageProvider::requestPixmap(const QString &id,
    QSize *size, const QSize &requestedSize)
{
    QPixmap p = QPixmap::fromImage(QImage("/usr/share/icons/gnome/32x32/apps/gnome-terminal.png"));
    *size = p.size();

    return p;
}
