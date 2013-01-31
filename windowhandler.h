#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <QObject>

#include "windowmanager.h"

namespace RocketBar {

class WindowHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)

protected:
    WindowManager::Window *mWindow;

public:
    WindowHandler(WindowManager::Window* window);

    QString title() const;

signals:
    void titleChanged();

public slots:
    void handle();
};

}

#endif // WINDOWHANDLER_H
