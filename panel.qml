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

    Rectangle {
        height: 20
        anchors.verticalCenter: parent.verticalCenter

        Rectangle{
            id:first
            x:0
            height: parent.parent.height+5
            width: 5
            color: "green"
        }

        Row {
            id: launcherArea
            objectName: "launcherArea"
            spacing: 2
            opacity: 0.6
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.left: first.right
            anchors.right: spacer1.left

            MouseArea {
                id:icon1
                width: 30
                height: 30

                Rectangle {
                    id: one
                    anchors.fill: parent
                    radius: 10
                    color: "yellow"
                }

                onClicked: {
                    icon1.opacity = icon1.opacity < 0.9 ? icon1.opacity + 0.1 : 0.5
                }
                onDoubleClicked: {
                    if (mouse.button === Qt.LeftButton)
                        icon1.destroy();
                }
            }

            Rectangle {
                width:30
                height:30
                radius:10
                color: "red"
            }
            Rectangle {
                width: 30
                height: 30
                radius:10
                color: "green"
            }

            //for testing
            Flickable {
                width: 100
                height: 30
                contentWidth: 30
                contentHeight: 30
                boundsBehavior: Flickable.DragOverBounds
                Row {
                    spacing: 2
                    Repeater {
                        model: 10
                        Rectangle {width:30;height:30;radius:10;color: "blue"}
                    }
                }
            }
        }

        Rectangle{
            id:spacer1
            x:500
            height: parent.parent.height
            width: 10
            color: "red"

//            MouseArea{
//                height: parent.height
//                width: parent.width
//                drag.target: spacer1
//                drag.axis: Drag.XAxis
//            }
        }

        Row {
            id: tasksArea
            objectName: "tasksArea"
            spacing: 2
            anchors.leftMargin: 10
            anchors.left: spacer1.right
            anchors.right: spacer2.left
        }

        Rectangle{
            id:spacer2
            x:1300
            height: parent.parent.height
            width: 10
            color: "red"
            MouseArea{
                height: parent.height
                width: parent.width
                drag.target: spacer2
                drag.axis: Drag.XAxis
            }
        }

        Row {
            id: trayArea
            objectName: "trayArea"
            spacing: 2
            anchors.left: spacer2.right
            anchors.right: last.left

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
                    else{//just for lulz
                        rb_clock.text = Qt.formatDateTime(new Date(), "hh;mm")
                        tick = true
                    }
                    rb_date.text = Qt.formatDateTime(new Date(), "dd.MM.yyyy")
                }
            }
        }

        Rectangle{
            id:last
            height:parent.parent.height
            width: 10
            x:parent.parent.width-width
            color: "green"

        }
    }
}
