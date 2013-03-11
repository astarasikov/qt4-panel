#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QMap>
#include <QList>
#include <QDir>
#include <QUrl>
#include <QSettings>

namespace RocketBar{

class ThemeManager
{
protected:
    QSettings &mSettings;
    QMap<QString, QDir> mThemeFiles;
    QList<QDir> mThemeDirs;
    QString mCustomThemeName;

    void addFilesFromDirectory(QDir &directory);

public:
    enum QMLtypes {
        PANEL, PANEL_VERTICAL
    };

    ThemeManager(QSettings &settings);
    ~ThemeManager();

    void update();
    void setTheme(QString name);

    QUrl qml(enum QMLtypes type);
    QList<QString> themes(void);
};

} //namespace RocketBar


#endif // THEMEMANAGER_H
