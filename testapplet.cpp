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

void RocketBar::TestApplet::handleClick(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    mWidget->setVisible(!mWidget->isVisible());
}

void RocketBar::TestApplet::handleContextMenu(int x, int y)
{
    mMenu->popup(QPoint(x, y));
}
