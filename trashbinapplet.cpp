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

    confirmDeleting = false;
    trashButton = new QPushButton(tr("Trash"));
    trashButton->connect(trashButton, SIGNAL(clicked()), this, SLOT(trash()));
    delete layout;
    layout = new QGridLayout();
    layout->addWidget(backButton,0,0);
    layout->addWidget(trashButton,0,1);
    layout->addWidget(openDolphin,0,2);
    layout->addWidget(listItem,1,0,1,3);
    mWidget->setLayout(layout);
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


void RocketBar::TrashBinApplet::initApplet(QString path){
    trashButton->setText(tr("Trash"));
    confirmDeleting=false;
    StackFolderApplet::initApplet(path);
}

void RocketBar::TrashBinApplet::trash(){
    if (!confirmDeleting){
        confirmDeleting = true;
        trashButton->setText(tr("Click once again to trash"));
        mWidget->update();
    }
    else{
        confirmDeleting = false;
        trashButton->setText(tr("Trash"));
        mWidget->update();

        QStringList list = folder.entryList();
        for (int i=0; i<list.size(); i++){
            QString name = list.at(i);

            if (name.compare(".") == 0 || name.compare("..") == 0) {
                continue;
            }
            QString path = folder.path().append("/"+name);
            bool res;
            if (QFileInfo(path).isDir()){
                res = removeDir(path);
            }
            else
                QFile::remove(path);

        }
        initApplet(folder.path());
    }
}

bool RocketBar::TrashBinApplet::removeDir(const QString &dirName)
    {
        bool result = true;
        QDir dir(dirName);

        if (dir.exists(dirName)) {
            Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
                if (info.isDir()) {
                    result = removeDir(info.absoluteFilePath());
                }
                else {
                    result = QFile::remove(info.absoluteFilePath());
                }

                if (!result) {
                    return result;
                }
            }
            result = dir.rmdir(dirName);
        }

        return result;
    }
