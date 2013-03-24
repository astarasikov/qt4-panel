#include "application.h"

#include <QApplication>
#include <QDeclarativeItem>
#include <QDeclarativeView>

#include "global_defines.h"
#include "mainwidget.h"
#include "panelbutton.h"

RocketBar::Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
{
    //move to a separate function
    qmlRegisterType<RocketBar::PanelButton>("ru.rosalab.rocketbar",
                                            2, 0, "PanelButton");

    setOrganizationName(RocketBar::OrganizationName);
    setOrganizationDomain(RocketBar::OrganizationDomain);
    setApplicationName(RocketBar::ApplicationName);
    setApplicationVersion(RocketBar::ApplicationVersion);

    mContext = new RocketBar::Context(this);
}

RocketBar::Application::~Application() {
    delete mContext;
}

int RocketBar::Application::run()
{
    mWidget = new RocketBar::MainWidget(mContext);
    mWidget->show();
    return exec();
}

#ifdef ROCKETBAR_WM_X11
#include "windowmanagerx11.h"

bool RocketBar::Application::x11EventFilter(XEvent *event)
{
    if (mContext->mWindowManager) {
        WindowManagerX11 *x11;
        x11 = reinterpret_cast<WindowManagerX11*>(mContext->mWindowManager);
        x11->event(event);
    }

    return false;
}
#endif


