#include "testapplet.h"

RocketBar::TestApplet::TestApplet()
    :mMenu(new QMenu())
{
    mWidget = new QWidget();
    mWidget->setStyleSheet("background: #f08080; ");

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

void RocketBar::TestApplet::showMenu()
{
    mMenu->show();
}
