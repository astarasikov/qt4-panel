#include "thememanager.h"
#include <QDir>

QMap<QString,QString> RocketBar::ThemeManager::mThemeFiles;
static QString catalogues[]={
    "/usr/share/themes",
    "~/.themes"
};

RocketBar::ThemeManager::ThemeManager()
{
}

void RocketBar::ThemeManager::update()
{
    mThemeFiles.clear();
    for(int i=0;i<sizeof(catalogues)/sizeof(catalogues[0]);i++){
        addFilesFromDirectory(catalogues[i]);
    }
}

void RocketBar::ThemeManager::addFilesFromDirectory(QString directory)
{
    QDir dir(directory);
    foreach(QFileInfo f, dir.entryInfoList()) {
        if (!f.isDir()) {
            continue;
        }

        QFileInfo tempFile(f.absoluteFilePath()+"/rocketbar");
        if (tempFile.exists() && tempFile.isDir()) {
            mThemeFiles[f.fileName()] = tempFile.absoluteFilePath();
        }
    }
}
