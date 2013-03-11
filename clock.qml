import QtQuick 1.1

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
