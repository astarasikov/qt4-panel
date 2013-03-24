#include "trashbinapplet.h"

RocketBar::TrashBinApplet::TrashBinApplet()
    : RocketBar::StackFolderApplet::StackFolderApplet
      (trashPath() + "/files"),
      mFsWatcher(new QFileSystemWatcher()),
      mAppletImage(QImage()), mMenu(new QMenu())
{
    mFsWatcher->addPath(mDirPath);
    connect(mFsWatcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(directoryChanged(QString)));
    connect(mFsWatcher, SIGNAL(fileChanged(QString)),
            this, SLOT(directoryChanged(QString)));
    directoryChanged(mDirPath);

    trashButton = new QPushButton(tr("Trash"));
    trashButton->connect(trashButton, SIGNAL(clicked()),
                         this, SLOT(clearTrash()));
    mLayout->addWidget(trashButton, 0, 2);

    QAction *aRemove = new QAction(QIcon::fromTheme("remove"),
                                  tr("Clear Trash"), this);
    connect(aRemove, SIGNAL(triggered()), this, SLOT(clearTrash()));
    mMenu->addAction(aRemove);
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
        mAppletImage = QIcon::fromTheme("user-trash").pixmap(32, 32).toImage();
    }
    else {
        mAppletImage = QIcon::fromTheme("user-trash-full").pixmap(32, 32).toImage();
    }
    emit imageChanged();
}


void RocketBar::TrashBinApplet::initApplet(QString path){
    trashButton->setText(tr("Trash"));
    StackFolderApplet::initApplet(path);
}

void RocketBar::TrashBinApplet::clearTrash()
{
    clearDir(trashPath() + "/files");
    clearDir(trashPath() + "/info");
    directoryChanged(mDirPath);
}

void RocketBar::TrashBinApplet::handleContextMenu(int x, int y)
{
    mMenu->popup(QPoint(x, y));
}

QString RocketBar::TrashBinApplet::trashPath()
{
    //TODO: check XDG trash path here
    return QDir::homePath() + "/.local/share/Trash";
}

void RocketBar::TrashBinApplet::clearDir(QString str)
{
    QDir d(str);
    if (!d.exists()) {
        return;
    }
    Q_FOREACH(QFileInfo info,
              d.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
    {
        if (info.isDir()) {
            clearDir(info.absoluteFilePath());
        }
        else {
            QFile::remove(info.absoluteFilePath());
        }
    }
}
