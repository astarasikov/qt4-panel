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

    qDebug() << "icon[ " << id ;

    QIcon *icon = new QIcon(id);
    return icon->pixmap(requestedSize);

    QPixmap p = QPixmap::fromImage(QImage("/usr/share/icons/gnome/32x32/apps/gnome-terminal.png"));
    *size = p.size();

    return p;
}
