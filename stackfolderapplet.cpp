#include "stackfolderapplet.h"
#include "trashbinapplet.h"
#include <QDesktopWidget>


RocketBar::StackFolderApplet::StackFolderApplet(QString path)
    :mDirPath(path), mMenu(new QMenu())
{
    mWidget = new QWidget();
    mWidget->setStyleSheet("background: black; ");
    mWidget->setWindowOpacity(0.9);

    folderStack = new QStack<QFileInfo>();
    listItem = new QListWidget(mWidget);
    listItem->connect(listItem, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(openFile(QListWidgetItem*)));
    layout = new QGridLayout();
    backButton = new QPushButton(tr("Go back"));
    backButton->connect(backButton, SIGNAL(clicked()), this, SLOT(goBack()));
    openDolphin = new QPushButton(tr("Open..."));
    openDolphin->connect(openDolphin, SIGNAL(clicked()), this, SLOT(openFolder()));
    layout->addWidget(backButton,0,0);
    layout->addWidget(openDolphin,0,1);
    layout->addWidget(listItem,1,0,1,2);
    mWidget->setLayout(layout);
    mWidget->setFixedSize(Width, Height);

    mMenu->addMenu(tr("SubMenu"));
    mMenu->addSeparator();
    QAction *action = new QAction(tr("Simulate Click"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(handleClick()));
    mMenu->addAction(action);

    mWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(handleContextMenu(QPoint)));
}

RocketBar::StackFolderApplet::~StackFolderApplet() {
    delete folderStack;
    delete layout;
    delete backButton;
    delete openDolphin;
    delete listItem;
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

void RocketBar::StackFolderApplet::showMenu()
{
    mMenu->show();
}

void RocketBar::StackFolderApplet::openFile(QListWidgetItem* item){
    QString path = folder.path().append("/"+item->text());
    QFileInfo file(path);
    if (file.isDir()){
        folderStack->push(file);
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
    listItem->clear();
    for (int i=0; i<list.size(); i++){
        QString name = list.at(i);
        if (name.compare(".") == 0 || name.compare("..") == 0) {
            continue;
        }
        QFileInfo info(folder.absolutePath().append("/"+name));
        QFileIconProvider ip;
        QIcon icon=ip.icon(info);
        QListWidgetItem *item = new QListWidgetItem(icon, name);
        listItem->addItem(item);
    }

}

void RocketBar::StackFolderApplet::goBack(){
    if (!folderStack->isEmpty()){
        QFileInfo file = folderStack->pop();
        initApplet(file.absolutePath());
    }
}

void RocketBar::StackFolderApplet::handleContextMenu(int x, int y) {
    mMenu->popup(QPoint(x, y - 2*mMenu->height()));
}

