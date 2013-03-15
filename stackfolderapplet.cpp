#include "stackfolderapplet.h"

RocketBar::StackFolderApplet::StackFolderApplet()
    :mMenu(new QMenu())
{
    mWidget = new QWidget();
    mWidget->setStyleSheet("background: black; ");
    mWidget->setWindowOpacity(0.9);
    visibility = mWidget->isVisible();

    folderStack = new QStack<QFileInfo>();
    listItem = new QListWidget();
    listItem->connect(listItem, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(openFile(QListWidgetItem*)));
    layout = new QGridLayout();
    backButton = new QPushButton("Go back");
    backButton->connect(backButton, SIGNAL(clicked()), this, SLOT(goBack()));
    openDolphin = new QPushButton("Open in Dolphin");
    openDolphin->connect(openDolphin, SIGNAL(clicked()), this, SLOT(openFolderInDolphin()));
    layout->addWidget(backButton,0,0);
    layout->addWidget(openDolphin,0,1);
    layout->addWidget(listItem,1,0,1,2);
    mWidget->setLayout(layout);

    mMenu->addMenu("SubMenu");
    mMenu->addSeparator();
    QAction *action = new QAction(tr("Simulate Click"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(handleClick(int, int)));
    mMenu->addAction(action);
}

RocketBar::StackFolderApplet::~StackFolderApplet() {
    delete mMenu;
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

void RocketBar::StackFolderApplet::handleClick()
{
    mWidget->setVisible(!mWidget->isVisible());
}

void RocketBar::StackFolderApplet::handleClick(int x,int y)
{
    int height = 400, width = 500;
    mWidget->setGeometry(x-width/2, y, width, height);
    initApplet("/home/");
}

void RocketBar::StackFolderApplet::showMenu()
{
    mMenu->show();
}

void RocketBar::StackFolderApplet::openFile(QListWidgetItem* item){
    QString path = folder.absolutePath().append("/"+item->text());
    QFileInfo *file = new QFileInfo(path);
    if (file->isDir()){
        folderStack->push(*file);
        initApplet(path);
    }
    else
    {
        //is shit, but works
        QStringList parameters;
        qDebug()<<path;
        parameters<<"file:"+path;
        QProcess::startDetached("dolphin", parameters);
    }
}

void RocketBar::StackFolderApplet::openFolderInDolphin(){
    QString path = folder.absolutePath();
    QStringList commandLineParameters;
    commandLineParameters<<"file:"+path;
    QProcess::startDetached("dolphin", commandLineParameters);
}

void RocketBar::StackFolderApplet::initApplet(QString path){
    folder = QDir(path);
    QStringList list = folder.entryList();
    listItem->clear();
    for (int i=2; i<list.size(); i++){
        QFileInfo info(folder.absolutePath().append("/"+list.at(i)));
        QFileIconProvider ip;
        QIcon icon=ip.icon(info);
        QListWidgetItem *item = new QListWidgetItem(icon, list.at(i));
        listItem->addItem(item);
    }

    mWidget->setWindowTitle(folder.dirName());
    mWidget->setVisible(!visibility);
}

void RocketBar::StackFolderApplet::goBack(){
    if (!folderStack->isEmpty()){
        QFileInfo file = folderStack->pop();
        initApplet(file.absolutePath());
        visibility = false;
    }

}
