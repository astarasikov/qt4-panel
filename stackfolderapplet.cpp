#include "stackfolderapplet.h"
#include "trashbinapplet.h"
#include <QDesktopWidget>


RocketBar::StackFolderApplet::StackFolderApplet(QString path)
    :mDirPath(path)
{
    mWidget = new QWidget();
    mWidget->setStyleSheet("background: black; ");
    mWidget->setWindowOpacity(0.9);

    mFolderStack = new QStack<QFileInfo>();
    mListItem = new QListWidget(mWidget);
    mListItem->connect(mListItem, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(openFile(QListWidgetItem*)));
    mLayout = new QGridLayout();
    mBackButton = new QPushButton(tr("Go back"));
    mBackButton->connect(mBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    mOpenFile = new QPushButton(tr("Open..."));
    mOpenFile->connect(mOpenFile, SIGNAL(clicked()), this, SLOT(openFolder()));
    mLayout->addWidget(mBackButton,0,0);
    mLayout->addWidget(mOpenFile,0,1);
    mLayout->addWidget(mListItem,1,0,1,2);
    mWidget->setLayout(mLayout);
    mWidget->setFixedSize(Width, Height);
    mWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(mWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
    //    this, SLOT(handleContextMenu(QPoint)));
}

RocketBar::StackFolderApplet::~StackFolderApplet() {
    delete mFolderStack;
    delete mLayout;
    delete mBackButton;
    delete mOpenFile;
    delete mListItem;
    delete mWidget;
}

QImage RocketBar::StackFolderApplet::image()
{
    return QImage(":/folder.png");
}

QString RocketBar::StackFolderApplet::name()
{
    return "StackFolderApplet";
}

void RocketBar::StackFolderApplet::handleClick(int x,int y)
{
    if (!mWidget->isVisible()) {
        mWidget->move(x - Width / 2, y - Height);
        initApplet(mDirPath);
    }
    else {
        mWidget->setVisible(false);
    }
}

void RocketBar::StackFolderApplet::openFile(QListWidgetItem* item){
    QString path = folder.path().append("/"+item->text());
    QFileInfo file(path);
    if (file.isDir()){
        mFolderStack->push(file);
        initApplet(path);
    }
    else
    {
        QStringList parameters;
        parameters<<"file:"+path;
        QProcess::startDetached("xdg-open", parameters);
    }
}

void RocketBar::StackFolderApplet::openFolder(){
    QString path = folder.path();
    QStringList commandLineParameters;
    commandLineParameters<<"file:"+path;
    QProcess::startDetached("xdg-open", commandLineParameters);
}

void RocketBar::StackFolderApplet::initApplet(QString path){
    folder = QDir(path);
    initFileList();
    mWidget->setWindowTitle(folder.dirName());
    mWidget->setVisible(true);
}

void RocketBar::StackFolderApplet::initFileList(){
    QStringList list = folder.entryList();
    mListItem->clear();
    for (int i=0; i<list.size(); i++){
        QString name = list.at(i);
        if (name.compare(".") == 0 || name.compare("..") == 0) {
            continue;
        }
        QFileInfo info(folder.absolutePath().append("/"+name));
        QFileIconProvider ip;
        QIcon icon=ip.icon(info);
        QListWidgetItem *item = new QListWidgetItem(icon, name);
        mListItem->addItem(item);
    }
}

void RocketBar::StackFolderApplet::goBack(){
    if (!mFolderStack->isEmpty()){
        QFileInfo file = mFolderStack->pop();
        initApplet(file.absolutePath());
    }
}
