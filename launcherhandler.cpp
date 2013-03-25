#include "launcherhandler.h"

#include <QtCore/QProcess>
#include <QDir>
#include <QSettings>
#include <QDebug>

QString RocketBar::LauncherHandler::title() const
{
    return mTitle;
}

QString RocketBar::LauncherHandler::command() const
{
    return mCommand;
}

QString RocketBar::LauncherHandler::icon() const
{
    return mIcon;
}

static void addAppsFromDir(QDir &dir, QList<QObject*> &lst) {
    QFileInfoList files = dir.entryInfoList(QStringList() << "*.desktop",
                                            QDir::Files | QDir::NoDotAndDotDot);
    foreach (QFileInfo f, files) {
        qDebug() << f.absoluteFilePath();
        QString appDesc;
        QString appPath;
        QString appIcon;

        QSettings s(f.absoluteFilePath(), QSettings::IniFormat);
        s.beginGroup("Desktop Entry");

        appDesc = s.value("Name").toString();
        if (!appDesc.length()) {
            appDesc = s.value("GenericName").toString();
        }
        if (!appDesc.length()) {
            appDesc = s.value("Comment").toString();
        }

        appPath = s.value("Exec").toString();
        if (!appPath.length()) {
            appPath = s.value("TryExec").toString();
        }

        appIcon = s.value("Icon").toString();
        if (!appIcon.length()) {
            appIcon = "applications-other";
        }

        if (appPath.length()) {
            lst.append(new RocketBar::LauncherHandler(appPath, appIcon, appDesc));
        }

        s.endGroup();
    }
}

QList<QObject *> RocketBar::LauncherHandler::availableApps()
{
    QList<QDir> appDirs;
    appDirs.append(QDir::fromNativeSeparators(QDir::homePath() + "/.applications"));
    appDirs.append(QDir::fromNativeSeparators(QDir::rootPath() + "/usr/share/applications"));
    QList<QObject *> ret;

    foreach(QDir d, appDirs) {
        addAppsFromDir(d, ret);
    }

    return ret;
}

void RocketBar::LauncherHandler::handleClick()
{
    QProcess::startDetached(mCommand);
}

RocketBar::LauncherHandler::LauncherHandler(QString _command,
                                            QString _icon,
                                            QString _title)
    : mCommand(_command), mIcon(_icon), mTitle(_title)
{
}
