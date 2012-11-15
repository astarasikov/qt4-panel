#ifndef CONFIG_H
#define CONFIG_H

#include <QApplication>
#include <QSettings>

#include "layout.h"
#include "qdebug.h"

namespace RocketBar {

class Config
{
public:
    Config(QApplication *parent = 0) : mSettings(new QSettings(parent)) {
    }

    ~Config() {
        delete mSettings;
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

protected:
    QSettings *mSettings;
};

} //namespace RocketBar

#endif // CONFIG_H
