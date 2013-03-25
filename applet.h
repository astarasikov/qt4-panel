#ifndef APPLET_H
#define APPLET_H

#include <QObject>
#include <QImage>

#include "context.h"

namespace RocketBar {

class Applet : public QObject {
    Q_OBJECT

    Q_PROPERTY(QImage image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
public:
    Applet();
    virtual ~Applet();
    virtual QImage image(void) = 0;
    virtual QString name(void) = 0;

public slots:
    virtual void handleClick(int x, int y);
    virtual void handleContextMenu(int x, int y);

signals:
    void imageChanged();
    void nameChanged();
};

} //namespace RocketBar

#endif // APPLET_H
