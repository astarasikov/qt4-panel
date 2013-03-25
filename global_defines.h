#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#include <QString>

namespace RocketBar {
static const QString OrganizationName("ROSA Lab");
static const QString OrganizationDomain("rosalab.ru");
static const QString ApplicationName("RocketBar");
static const QString ApplicationVersion("2.0");

/* these really should be static inline methods
 * which will calculate values based on DPI */
static const int DefaultPanelHeight = 50;
static const int DefaultPanelWidth = 50;
static const int DefaultIconSize = 32;
}

#endif // GLOBAL_DEFINES_H
