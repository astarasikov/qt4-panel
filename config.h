#ifndef CONFIG_H
#define CONFIG_H

#include <QApplication>
#include <QSettings>

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

protected:
    QSettings *mSettings;
};

} //namespace RocketBar

#endif // CONFIG_H
