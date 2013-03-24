#include "trashbinapplet.h"

RocketBar::TrashBinApplet::TrashBinApplet()
    : RocketBar::StackFolderApplet::StackFolderApplet
      (QDir::homePath() + "/.local/share/Trash"),
      mFsWatcher(new QFileSystemWatcher()),
      mAppletImage(QImage())
{
    mFsWatcher->addPath(mDirPath);
    connect(mFsWatcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(directoryChanged(QString)));
    connect(mFsWatcher, SIGNAL(fileChanged(QString)),
            this, SLOT(directoryChanged(QString)));
    directoryChanged(mDirPath);
}

RocketBar::TrashBinApplet::~TrashBinApplet(){
    delete mFsWatcher;
}

QImage RocketBar::TrashBinApplet::image()
{
    return mAppletImage;
}

QString RocketBar::TrashBinApplet::name()
{
    return "TrashBinApplet";
}

void RocketBar::TrashBinApplet::directoryChanged(QString str)
{
    Q_UNUSED(str);
    QDir dir(mDirPath);
    if (dir.count() < 3) {
        mAppletImage = QImage(":/trash.png");
    }
    else {
        mAppletImage = QImage(":/trash-full.png");
    }
    emit imageChanged();
}
