#-------------------------------------------------
#
# Project created by QtCreator 2012-11-11T20:26:34
#
#-------------------------------------------------

QT += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rocketbarv2
TEMPLATE = app

!win32:!embedded:!qpa:!mac:!symbian:CONFIG += x11

x11 {
    LIBS += -lX11 -lXcomposite -lXdamage
    SOURCES += windowmanagerx11.cpp
    HEADERS += windowmanagerx11.h
    DEFINES += ROCKETBAR_WM_X11
}

!x11 {
    SOURCES += windowmanagerstub.cpp
    HEADERS += windowmanagerstub.h
    DEFINES += ROCKETBAR_WM_STUB
}

SOURCES += main.cpp \
    mainwidget.cpp \
    panelbutton.cpp \
    windowmanager.cpp \
    launcherhandler.cpp \
    thememanager.cpp \
    xdgimageprovider.cpp \
    applet.cpp \
    application.cpp

HEADERS  += \
    global_defines.h \
    layout.h \
    mainwidget.h \
    panelbutton.h \
    windowmanager.h \
    context.h \
    launcherhandler.h \
    thememanager.h \
    xdgimageprovider.h \
    applet.h \
    application.h

FORMS    +=

RESOURCES += \
    rocketbar.qrc

OTHER_FILES += \
    panel.qml \
    panel_vertical.qml \
    clock.qml
