#include "launcherhandler.h"

#include <QtCore/QProcess>

QString RocketBar::LauncherHandler::title() const
{
    return mTitle;
}

QString RocketBar::LauncherHandler::imagePath() const
{
    return mImagePath;
}

void RocketBar::LauncherHandler::handleClick()
{
    QProcess::startDetached(mCommand);
}



RocketBar::LauncherHandler::LauncherHandler(QString _title,
                                            QString _imagePath,
                                            QString _command)
    : mTitle(_title), mImagePath(_imagePath), mCommand(_command)
{
}
