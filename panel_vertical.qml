import QtQuick 1.1

import ru.rosalab.rocketbar 2.0

Rectangle {
    id:panelRoot
    width: 1600
    height: 30

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#1a4"
        }
        GradientStop {
            position: 1.0
            color: "#171"
        }
    }

    Grid {
        spacing: 2
        columns: 1

        Grid {
            objectName: "launcherArea"
            spacing: 2
            opacity: 0.6
            columns: 1

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

            PanelButton {
                width: 20
                height: 20
                id: button

                Rectangle {
                    anchors.fill: parent
                    radius: 5
                    color: "magenta"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            button.clicked()
                        }
                    }
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

        Grid {
            objectName: "tasksArea"
            spacing: 2
            columns: 1
        }
        Grid {
            objectName: "trayArea"
            spacing: 2
            columns: 1

            Text {
                id:label
                text:"test label"
            }

            Timer {
                interval: 500
                running: true
                repeat: true
                onTriggered: label.text = Date().toLocaleString()
            }
        }
    }
}
