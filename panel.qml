import QtQuick 1.1

import ru.rosalab.rocketbar 2.0

Rectangle {
    id:panelRoot
    width: 1600
    height: 30

    gradient: Gradient {
        GradientStop {
            position: 0.18
            color: "#00787878"
        }
        GradientStop {
            position: 0.2
            color: "#e0707090"
        }
        GradientStop {
            position: 1.0
            color: "#FF101040"
        }
    }

    // блик
    Rectangle {
        width: parent.width;
        height: parent.height/1.6;

        x: 0;
        y: parent.height * 0.2;
        color: "#00000000";
        clip: true;

        Rectangle {
            radius: parent.width/2;
            smooth: true;

            width: parent.width;
            height: parent.height;


            x: 0;
            y: -parent.height/2;
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#90FFFFFF"
                }
                GradientStop {
                    position: 1.0
                    color: "#50FFFFFF"
                }
            }
        }
    }

    Row {
        anchors.centerIn: parent
        spacing: 2

        Row {
            objectName: "launcherArea"
            spacing: 2
            opacity: 0.6

            MouseArea {
                id:icon1
                width: 20
                height: 20

                Rectangle {
                    anchors.fill: parent
                    radius: 10
                    color: "yellow"
                }

                onClicked: {
                    icon1.opacity = icon1.opacity < 0.9 ? icon1.opacity + 0.1 : 0.5
                }
            }

            Rectangle {
                width:20
                height:20
                radius:10
                color: "red"
            }
            Rectangle {
                width:20
                height:20
                radius:10
                color: "green"
            }

            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
            Rectangle {width:20;height:20;radius:10;color: "blue"}
        }

        Row {
            objectName: "tasksArea"
            spacing: 2
        }
        Row {
            objectName: "trayArea"
            spacing: 2

            Item {
                Text {
                    anchors.top:panelRoot.top;
                    y: -15;
                    id:rb_clock
                    text:"00:00"
                    font.pointSize: 24
                    color: "white"
                    smooth: true
                    style: Text.Outline; styleColor: "black"
                }
                Text {
                    id:rb_date
                    text:"date"
                    font.pointSize: 8
                    color: "white"
                    smooth: true
                    anchors.top: rb_clock.bottom;
                    anchors.horizontalCenter: rb_clock.horizontalCenter;
                }
            }

            Timer {
                interval: 500
                running: true
                repeat: true
                onTriggered: rb_clock.text = Qt.formatDateTime(new Date(), "hh:mm"),rb_date.text = Qt.formatDateTime(new Date(), "d.m.yyyy")
            }
        }
    }
}
