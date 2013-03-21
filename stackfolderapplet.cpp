#include "stackfolderapplet.h"

RocketBar::StackFolderApplet::StackFolderApplet()
    :mMenu(new QMenu())
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
    if (!mWidget->isVisible()) {
        mWidget->move(x - Width / 2, y);
        initApplet(QDir::homePath());
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
    QString path = folder.absolutePath().append("/"+item->text());
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
    QString path = folder.absolutePath();
    QStringList commandLineParameters;
    commandLineParameters<<"file:"+path;
    QProcess::startDetached("xdg-open", commandLineParameters);
}

void RocketBar::StackFolderApplet::initApplet(QString path){
    folder = QDir(path);
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

    mWidget->setWindowTitle(folder.dirName());
    mWidget->setVisible(true);
}

void RocketBar::StackFolderApplet::goBack(){
    if (!folderStack->isEmpty()){
        QFileInfo file = folderStack->pop();
        initApplet(file.absolutePath());
    }
}
