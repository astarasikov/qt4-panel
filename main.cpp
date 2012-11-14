#include <QApplication>

#include "mainwidget.h"
#include "global_defines.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName(RocketBar::OrganizationName);
    a.setOrganizationDomain(RocketBar::OrganizationDomain);
    a.setApplicationName(RocketBar::ApplicationName);
    a.setApplicationVersion(RocketBar::ApplicationVersion);

    RocketBar::Config config(&a);
    RocketBar::MainWidget w(&config, 0);
    w.show();

    return a.exec();
}
