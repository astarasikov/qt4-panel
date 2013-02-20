#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H
#include <QMap>

namespace RocketBar{

class ThemeManager
{
public:
    ThemeManager();
    enum QMLtypes {
        BUTTON, PANEL,
    };

    static void update();
protected:
    static QMap<QString,QString> mThemeFiles;
    static void addFilesFromDirectory(QString directory);

};

} //namespace RocketBar


#endif // THEMEMANAGER_H
