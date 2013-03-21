#include "launcherhandler.h"

#include <QtCore/QProcess>

QString RocketBar::LauncherHandler::title() const
{
    return mTitle;
}

QString RocketBar::LauncherHandler::description() const
{
    return mDescription;
}

void RocketBar::LauncherHandler::handleClick()
{
    QProcess::startDetached(mCommand);
}

RocketBar::LauncherHandler::LauncherHandler(QString _title,
                                            QString _command,
                                            QString _description)
    : mTitle(_title), mCommand(_command), mDescription(_description)
{
}
