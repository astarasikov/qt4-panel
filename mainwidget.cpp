#include "mainwidget.h"
#include "global_defines.h"
#include "panelbutton.h"

#include <QGraphicsObject>
#include <QDesktopWidget>

#include <QDeclarativeComponent>
#include <QDeclarativeItem>

#include <QContextMenuEvent>

RocketBar::MainWidget::MainWidget(
        RocketBar::Config *config, QWidget *parent)
    : QDeclarativeView(parent), mConfig(config)
{
    /* initialize a borderless panel window */
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("border-style: none;background:transparent;");
    buildMenu();

    updateWindow();
}

RocketBar::MainWidget::~MainWidget() {

}

void RocketBar::MainWidget::addButton(QString &name) {
    QDeclarativeComponent component(engine(), QUrl("qrc:/button.qml"));
    QDeclarativeItem *it = qobject_cast<QDeclarativeItem*>(component.create());
    QDeclarativeItem *launcherArea =
            rootObject()->findChild<QDeclarativeItem*>("tasksArea");
    //container.push_front(it);
    it->setParentItem(launcherArea);

    PanelButton *button = it->findChild<PanelButton*>("button");
    if (button) {
        button->setText(name);
    }
}

void RocketBar::MainWidget::updateWindow() {
    QRect screenRect = QApplication::desktop()->screenGeometry();

    int x(0), y(0), w(0), h(0);
    RocketBar::ScreenEdge o = mConfig->screenEdge();
    RocketBar::PanelLayout l = RocketBar::Panel_Horizontal;
    switch (o) {
    case RocketBar::Screen_Bottom:
        h = RocketBar::DefaultPanelHeight;
        y = screenRect.height() - h;
        w = screenRect.width();
        break;
    case RocketBar::Screen_Top:
        h = RocketBar::DefaultPanelHeight;
        w = screenRect.width();
        break;
    case RocketBar::Screen_Left:
        w = RocketBar::DefaultPanelWidth;
        h = screenRect.height();
        l = RocketBar::Panel_Vertical;
        break;
    case RocketBar::Screen_Right:
        w = RocketBar::DefaultPanelWidth;
        x = screenRect.width() - w;
        h = screenRect.height();
        l = RocketBar::Panel_Vertical;
        break;
    }

    if (l == RocketBar::Panel_Horizontal) {
        setSource(QUrl("qrc:/panel.qml"));
    }
    else {
        setSource(QUrl("qrc:/panel_vertical.qml"));
    }

    QGraphicsObject *root = rootObject();
    root->setProperty("width", w);
    root->setProperty("height", h);
    move(x, y);

    if (!mConfig->mWindowManager) {
        return;
    }

    foreach(WindowManager::Window* wnd, mConfig->mWindowManager->getWindows()) {
        QString title = wnd->getTitle();
        qDebug() << "Adding " << title;
        addButton(title);
    }
}

void RocketBar::MainWidget::contextMenuEvent(QContextMenuEvent *evt) {
    QPoint p(this->x() + evt->x(), this->y() + evt->y());
    evt->accept();
    mContextMenu->popup(p);
}

void RocketBar::MainWidget::buildMenu(void) {
    mContextMenu = new QMenu(this);

    QAction *aQuit = new QAction(tr("&Quit"), this);
    connect(aQuit, SIGNAL(triggered()), this, SLOT(close()));

    QAction *aToggleDebug = new QAction(tr("Toggle &Debug"), this);
    connect(aToggleDebug, SIGNAL(triggered()), this, SLOT(toggleDebug()));

    QAction *aAddButton = new QAction(tr("Add &Button"), this);
    connect(aAddButton, SIGNAL(triggered()), this, SLOT(addButton()));

    mContextMenu->addAction(aToggleDebug);
    mContextMenu->addAction(aAddButton);
    mContextMenu->addSeparator();
    mContextMenu->addAction(aQuit);
}
