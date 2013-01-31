#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <QObject>
#include <QMenu>

#include "windowmanager.h"

namespace RocketBar {

class WindowHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QImage icon READ icon NOTIFY iconChanged)

protected:
    WindowManager::Window *mWindow;
    QMenu *mMenu;

public:
    WindowHandler(WindowManager::Window* window);
    ~WindowHandler();

    QString title() const;
    QImage icon() const;

signals:
    void titleChanged();
    void iconChanged();

public slots:
    void handleClick();
    void close();
    void destroy();
    void kill();
    void map();
    void activate();
    void minimize();
};

} //namespace RocketBar

#endif // WINDOWHANDLER_H
