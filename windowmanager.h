#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtCore>
#include <QtGui/QImage>
#include <QList>
#include <QMap>
#include <QMenu>

#include <QDeclarativeImageProvider>

namespace RocketBar {

class TaskImageProvider : public QDeclarativeImageProvider {
public:
    TaskImageProvider();

    QImage requestImage(const QString &id, QSize *size,
                        const QSize &requestedSize);

    void invalidate(void);
    void update(QString name, QImage image);
protected:
    QMap<QString, QImage> mImageMap;
};

class Window : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY iconNameChanged)
protected:
    QMenu *mMenu;

public:
    Window();
    virtual ~Window();
    virtual void setParent(Window *parent) = 0;
    virtual QString title(void) = 0;
    virtual QString iconName(void) = 0;
    virtual QImage icon(void) = 0;

signals:
    void titleChanged();
    void iconNameChanged();

public slots:
    virtual void handleClick();

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
protected:
    TaskImageProvider mTaskImageProvider;

public:
    typedef QList<QObject*> WindowList;
    WindowManager();
    virtual ~WindowManager();

    virtual WindowList &getWindows(void) = 0;
    virtual TaskImageProvider *taskImageProvider();

signals:
    void windowsChanged(WindowManager::WindowList &list);
};

WindowManager *getWindowManager(void);

} //namespace RocketBar

#endif // WINDOWMANAGER_H
