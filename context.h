#ifndef CONTEXT_H
#define CONTEXT_H

#include <QApplication>
#include <QSettings>

#include "layout.h"
#include "qdebug.h"

#include "windowmanager.h"
#include "thememanager.h"

namespace RocketBar {

class Context
{
protected:
    QSettings *mSettings;
    ThemeManager *mThemeManager;

public:
    WindowManager *mWindowManager;

    Context(QApplication *parent = 0)
        : mSettings(new QSettings(parent)),
          mWindowManager(getWindowManager()),
          mThemeManager(new ThemeManager(*mSettings))
    {
    }

    ~Context() {
        mSettings->sync();

        delete mWindowManager;
        delete mThemeManager;
        delete mSettings;
    }

    ThemeManager &themeManager(void) const {
        return *mThemeManager;
    }

    bool debugEnabled(void) {
        QVariant v = mSettings->value("debugEnabled", false);
        return v.toBool();
    }

    //XXX: remove this
    void toggleDebug(void) {
        QVariant v(!debugEnabled());
        mSettings->setValue("debugEnabled", v);
    }

    enum RocketBar::ScreenEdge screenEdge(void) {
        QVariant v = mSettings->value("screenEdge",
                                      static_cast<int>(Screen_Top));
        return static_cast<RocketBar::ScreenEdge>(v.toInt(0));
    }

    void setScreenEdge(enum RocketBar::ScreenEdge e) {
        mSettings->setValue("screenEdge", static_cast<int>(e));
    }
};

} //namespace RocketBar

#endif // CONTEXT_H
