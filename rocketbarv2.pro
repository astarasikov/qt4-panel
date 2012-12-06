#-------------------------------------------------
#
# Project created by QtCreator 2012-11-11T20:26:34
#
#-------------------------------------------------

QT += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rocketbarv2
TEMPLATE = app


SOURCES += main.cpp \
    mainwidget.cpp \
    panelbutton.cpp

HEADERS  += \
    config.h \
    global_defines.h \
    layout.h \
    mainwidget.h \
    panelbutton.h

FORMS    +=

RESOURCES += \
    rocketbar.qrc

OTHER_FILES += \
    panel.qml \
    panel_vertical.qml \
    button.qml
