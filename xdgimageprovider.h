#ifndef XDGIMAGEPROVIDER_H
#define XDGIMAGEPROVIDER_H

#include <QDeclarativeImageProvider>

namespace RocketBar {

class XdgImageProvider : public QDeclarativeImageProvider
{
public:
    XdgImageProvider(QDeclarativeImageProvider::ImageType type);

    QPixmap requestPixmap(const QString &id, QSize *size,
                          const QSize &requestedSize);
};

} //namespace RocketBar

#endif // XDGIMAGEPROVIDER_H
