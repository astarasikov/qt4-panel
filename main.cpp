#include <QApplication>
#include <QDeclarativeItem>
#include <QDeclarativeView>

#include "global_defines.h"
#include "context.h"
#include "mainwidget.h"
#include "panelbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //move to a separate function
    qmlRegisterType<RocketBar::PanelButton>("ru.rosalab.rocketbar",
                                            2, 0, "PanelButton");

    a.setOrganizationName(RocketBar::OrganizationName);
    a.setOrganizationDomain(RocketBar::OrganizationDomain);
    a.setApplicationName(RocketBar::ApplicationName);
    a.setApplicationVersion(RocketBar::ApplicationVersion);

    RocketBar::Context context(&a);
    RocketBar::MainWidget w(&context);
    w.show();

    return a.exec();
}
