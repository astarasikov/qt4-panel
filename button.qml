import QtQuick 1.1
import ru.rosalab.rocketbar 2.0

Rectangle {
    width: 100
    height: 20
    radius: 10
    color: "#0f0"

    PanelButton {
        width: 20
        height: 20
        id: button
        objectName: "button"
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            radius: 5
            color: "blue"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    button.clicked()
                }
            }
        }

        Text {
            id: title
            anchors.centerIn: parent
            text: button.text
            color: "white"
        }
    }
}
