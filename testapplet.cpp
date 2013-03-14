#include "testapplet.h"
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QFileIconProvider>

RocketBar::TestApplet::TestApplet()
    :mMenu(new QMenu())
{
    mWidget = new QWidget();
    mWidget->setStyleSheet("background: black; ");
    mWidget->setWindowOpacity(0.9);

    mMenu->addMenu("SubMenu");
    mMenu->addSeparator();
    QAction *action = new QAction(tr("Simulate Click"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(handleClick()));
    mMenu->addAction(action);
}

RocketBar::TestApplet::~TestApplet() {
    delete mMenu;
    delete mWidget;
}

QImage RocketBar::TestApplet::image()
{
    return QImage(":/folder.png");
}

QString RocketBar::TestApplet::name()
{
    return "TestApplet";
}

void RocketBar::TestApplet::handleClick()
{
    mWidget->setVisible(!mWidget->isVisible());
}

void RocketBar::TestApplet::handleClick(int x,int y)
{
    int height = 400, width = 500;
    mWidget->setGeometry(x-width/2, 600, width, height);
    folder = QDir("/home/alexander/Downloads");
    QStringList list = folder.entryList();
    QListWidget *listItem = new QListWidget();

    for (int i=0; i<list.size(); i++){
        QFileInfo info(folder.absolutePath().append("/"+list.at(i)));
        QFileIconProvider ip;
        QIcon icon=ip.icon(info);
        QListWidgetItem *item = new QListWidgetItem(icon, list.at(i));
        listItem->addItem(item);
    }
    //QListWidgetItem *item;
    //QAction *openAction = new QAction(tr("Open"), listItem);
    listItem->connect(listItem, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(openFile(QListWidgetItem*)));
    //listItem->addAction(openAction);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(listItem);
    mWidget->setLayout(layout);
    mWidget->setWindowTitle(folder.dirName());
    mWidget->setVisible(!mWidget->isVisible());

}

void RocketBar::TestApplet::showMenu()
{
    mMenu->show();
}

void RocketBar::TestApplet::openFile(QListWidgetItem* item){
    QString path = folder.absolutePath().append("/"+item->text());
    QProcess::startDetached("/home/alexander/Downloads/moap.32x32");
    qDebug()<<path;

}
