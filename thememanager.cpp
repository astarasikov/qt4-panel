#include "thememanager.h"

#define KEY_THEME_NAME "ThemeManager::themeName"

RocketBar::ThemeManager::ThemeManager(QSettings &settings)
    : mSettings(settings),
      mThemeFiles(QMap<QString, QDir>()),
      mThemeDirs(QList<QDir>()),
      mCustomThemeName(mSettings.value(KEY_THEME_NAME).toString())
{
    mThemeDirs.append(QDir::fromNativeSeparators(QDir::homePath()
                                                 + "/.themes"));
    mThemeDirs.append(QDir::fromNativeSeparators(QDir::rootPath()
                                                 + "/usr/share/themes"));
    update();
}

RocketBar::ThemeManager::~ThemeManager()
{
    mSettings.setValue(KEY_THEME_NAME, mCustomThemeName);
}

QUrl RocketBar::ThemeManager::qml(QMLtypes type) {
    QString fileName;

    switch (type) {
    case PANEL:
        fileName = "panel.qml";
        break;
    case PANEL_VERTICAL:
        fileName = "panel_vertical.qml";
        break;
    }

    if (mCustomThemeName.length() && mThemeFiles.contains(mCustomThemeName)) {
        QDir themeDir = mThemeFiles[mCustomThemeName];
        QString path = themeDir.filePath(fileName);
        if (QFileInfo(path).exists()) {
            return QUrl::fromLocalFile(path);
        }
    }

    return QUrl("qrc:/" + fileName);
}

void RocketBar::ThemeManager::setTheme(QString name) {
    mCustomThemeName = name;
}

void RocketBar::ThemeManager::update()
{
    mThemeFiles.clear();

    foreach(QDir d, mThemeDirs) {
        addFilesFromDirectory(d);
    }
}

void RocketBar::ThemeManager::addFilesFromDirectory(QDir &dir)
{
    foreach(QFileInfo f, dir.entryInfoList()) {
        if (!f.isDir()) {
            continue;
        }

        QFileInfo tempFile(f.absoluteFilePath(), "rocketbar");
        if (tempFile.exists() && tempFile.isDir()) {
            mThemeFiles[f.fileName()] = QDir(tempFile.absoluteFilePath());
        }
    }
}
