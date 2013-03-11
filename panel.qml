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
            color: "#a0303030"
        }
        GradientStop {
            position: 1.0
            color: "#FF101010"
        }
    }

    // background
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
        width: panelRoot.width
        height: panelRoot.height * 0.8
        //anchors.verticalCenter: parent.verticalCenter

        /*********************************************************************
         * Launcher
         ********************************************************************/
        ListView {
            orientation: ListView.Horizontal
            id: launcherArea
            width: panelRoot.width / 5
            height: parent.height

            spacing: 5
            clip: true

            model: launcherListModel

            delegate: Rectangle {
                id: frame
                width: parent.height
                height: parent.height
                color: "#303030"


                Rectangle {
                    id: buttonRect
                    anchors.centerIn: parent
                    width: parent.width - 4
                    height: parent.height - 4
                    color: "black"

                    Image {
                        width: parent.width - 4
                        height: parent.height - 4
                        anchors.centerIn: parent
                        source: "image://xdg/" + title
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onHoveredChanged: {
                        if (containsMouse) {
                            buttonRect.color = "#303030"
                            frame.color = "lime"
                        }
                        else {
                            buttonRect.color = "black"
                            frame.color = "#303030"
                        }
                    }
                    onClicked: {
                        handleClick()
                    }
                }
            }
        }

        /*********************************************************************
         * Task Bar
         ********************************************************************/
        ListView {
            orientation: ListView.Horizontal
            id: tasksArea
            anchors.left: launcherArea.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            width: 3 * panelRoot.width / 5
            height: parent.height

            spacing: 5
            clip: true

            model: tasksListModel

            delegate: Rectangle {
                id: iconFrame
                width: 150
                height: parent.height
                color: "#303030"


                Rectangle {
                    id: iconRect
                    anchors.centerIn: parent
                    width: parent.width - 4
                    height: parent.height - 4
                    color: "black"

                    Row {
                        spacing: 4
                        width: parent.width
                        height: parent.height

                        Image {
                            id: taskIcon
                            width: parent.height
                            height: parent.height
                            anchors.verticalCenter: parent.verticalCenter

                            source: "image://task/" + iconName
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter

                            text: title
                            color: "white"
                            width: parent.width - 10 - taskIcon.width
                            elide: Text.ElideRight
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onHoveredChanged: {
                        if (containsMouse) {
                            iconRect.color = "#303030"
                            iconFrame.color = "lime"
                        }
                        else {
                            iconRect.color = "black"
                            iconFrame.color = "#303030"
                        }
                    }
                    onClicked: {
                        handleClick()
                    }
                }
            }
        }

        /*********************************************************************
         * Applet Area
         ********************************************************************/
        Row {
            id: trayArea
            objectName: "appletArea"
            spacing: 2
            width: panelRoot.width / 5

            /*******************************************************************
             * Clock
             ******************************************************************/
            Item {
                id:clockItem
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
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
                interval: 1000
                running: true
                repeat: true
                onTriggered: {
                    var d = new Date();
                    rb_clock.text = Qt.formatDateTime(d, "hh:mm")
                    rb_date.text = Qt.formatDateTime(d, "dd.MM.yyyy")
                }
            }
        }
    }
}
