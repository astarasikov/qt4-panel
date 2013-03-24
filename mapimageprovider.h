#ifndef MAPIMAGEPROVIDER_H
#define MAPIMAGEPROVIDER_H

#include <QDeclarativeImageProvider>
#include <QMap>
#include <QImage>

namespace RocketBar {

class MapImageProvider : public QDeclarativeImageProvider {
public:
    MapImageProvider();

    QImage requestImage(const QString &id, QSize *size,
                        const QSize &requestedSize);

public slots:
    void invalidate(void);
    void update(QString name, QImage image);
    void remove(QString name);
protected:
    QMap<QString, QImage> mImageMap;
};

}

#endif // MAPIMAGEPROVIDER_H
