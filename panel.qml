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
        width: panelRoot.width
        height: panelRoot.height * 0.8
        anchors.verticalCenter: parent.verticalCenter

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
                    Text {
                        anchors.centerIn: parent
                        text: title
                        color: "white"
                        width: parent.width - 10
                        elide: Text.ElideRight
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


        Row {
            id: trayArea
            objectName: "trayArea"
            spacing: 2
            anchors.left: tasksArea.right
            width: panelRoot.width / 5

            Item {
                id:clockItem
                anchors.centerIn: parent
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
                property bool tick: false
                onTriggered: {
                    if (tick){
                        tick = false
                        rb_clock.text = Qt.formatDateTime(new Date(), "hh:mm")
                    }
                    else{
                        rb_clock.text = Qt.formatDateTime(new Date(), "hh;mm")
                        tick = true
                    }
                    rb_date.text = Qt.formatDateTime(new Date(), "dd.MM.yyyy")
                }
            }
        }
    }
}
