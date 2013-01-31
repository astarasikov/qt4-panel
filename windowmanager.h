#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtGui/QImage>
#include <QtCore/QVector>

namespace RocketBar {

class WindowManager
{
public:
    class Window {
    public:
        virtual void activate(void) = 0;
        virtual void minimize(void) = 0;
        virtual void map(void) = 0;
        virtual void close(void) = 0;
        virtual void destroy(void) = 0;
        virtual void kill(void) = 0;
        virtual void setParent(Window *parent) = 0;

        virtual QString getTitle(void) = 0;
        virtual QImage getIcon(void) = 0;
    };

    typedef QVector<RocketBar::WindowManager::Window*> WindowList;

    virtual WindowList &getWindows(void) = 0;
    WindowManager() {}
    virtual ~WindowManager() {}
};

WindowManager *getWindowManager(void);

} //namespace RocketBar

#endif // WINDOWMANAGER_H
