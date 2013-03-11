#ifndef CONTEXT_H
#define CONTEXT_H

#include <QApplication>
#include <QSettings>

#include "layout.h"
#include "qdebug.h"

#include "windowmanager.h"
#include "thememanager.h"
#include "imageprovider.h"

namespace RocketBar {

class Context
{
protected:
    QSettings *mSettings;
    ThemeManager *mThemeManager;

public:
    ImageProvider *mImageProvider;
    WindowManager *mWindowManager;

    Context(QApplication *parent = 0)
        : mSettings(new QSettings(parent)),
          mThemeManager(new ThemeManager(*mSettings)),
          mImageProvider(new ImageProvider(ImageProvider::Pixmap)),
          mWindowManager(getWindowManager())
    {
    }

    ~Context() {
        mSettings->sync();

        delete mWindowManager;
        delete mImageProvider;
        delete mThemeManager;
        delete mSettings;
    }

    ThemeManager &themeManager(void) const {
        return *mThemeManager;
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
