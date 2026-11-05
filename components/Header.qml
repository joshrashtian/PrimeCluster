import QtQuick
import Cluster

Item {
    id: header
    required property ClusterData cluster

    property string fontFamily
    property string rangeFontFamily
    property string iconFontFamily
    property color dimColor: "#555555"
    property color textColor: "black"

    QtObject {
        id: bluetooth
        property string state: "off"
    }

    Text {
        anchors.left: parent.left
        font.family: header.iconFontFamily
        font.pixelSize: 30
        text: bluetooth.state === "connected" ? "\ue1b8" : bluetooth.state === "searching" ? "\ue1ba" : "\ue1b9"
        color: header.textColor
    }

    Text {
        id: clock
        font.family: header.fontFamily
        font.pixelSize: 30

        anchors.horizontalCenter: parent.horizontalCenter

        function update() {
            text = Qt.formatTime(new Date(), "h:mm AP");
        }

        Component.onCompleted: update()

        Timer {
            interval: 1000        // check every second, so minutes flip on time
            running: true
            repeat: true
            onTriggered: clock.update()
        }

        color: header.textColor
    }

    
    Text {
        anchors.right: parent.right

        text: header.cluster.miles + "mi"
        font.family: header.rangeFontFamily
        font.pixelSize: 30
        font.variableAxes: {
            "wght": 900
        }
        color: header.textColor
    }
}
