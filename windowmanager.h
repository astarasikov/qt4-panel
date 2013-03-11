#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtCore>
#include <QtGui/QImage>
#include <QList>

namespace RocketBar {

class Window : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QImage icon READ icon NOTIFY iconChanged)

public:
    virtual void setParent(Window *parent) = 0;

    virtual QString title(void) = 0;
    virtual QImage icon(void) = 0;

signals:
    void titleChanged();
    void iconChanged();

public slots:
    virtual void handleClick() = 0;
    virtual void close() = 0;
    virtual void destroy() = 0;
    virtual void kill() = 0;
    virtual void map() = 0;
    virtual void activate() = 0;
    virtual void minimize() = 0;
};

class WindowManager : public QObject
{
    Q_OBJECT

public:
    typedef QList<QObject*> WindowList;

    virtual WindowList &getWindows(void) = 0;
    WindowManager();
    virtual ~WindowManager();

signals:
    void windowsChanged(WindowManager::WindowList &list);
};

WindowManager *getWindowManager(void);

} //namespace RocketBar

#endif // WINDOWMANAGER_H
