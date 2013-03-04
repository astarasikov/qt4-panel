#include "launcherhandler.h"

#include <QtCore/QProcess>

QString RocketBar::LauncherHandler::title() const
{
    return mTitle;
}

void RocketBar::LauncherHandler::handleClick()
{
    QProcess::startDetached(mCommand);
}

RocketBar::LauncherHandler::LauncherHandler(QString _title,
                                            QString _command)
    : mTitle(_title), mCommand(_command)
{
}
