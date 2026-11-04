import QtQuick
import Cluster

Item {
    id: header
    required property ClusterData cluster

    property string fontFamily
    property string rangeFontFamily

    property color dimColor: "#555555"
    property color textColor: "black"

    height: gears.height

    Row {
        id: gears
        anchors.left: parent.left
        spacing: 1

        Repeater {
            model: [
                {
                    label: "P",
                    gear: ClusterData.GearParking
                },
                {
                    label: "R",
                    gear: ClusterData.GearReverse
                },
                {
                    label: "N",
                    gear: ClusterData.GearNeutral
                },
                {
                    label: "D",
                    gear: ClusterData.GearDrive
                },
                {
                    label: "B",
                    gear: ClusterData.GearB
                }
            ]

            Text {
                required property var modelData
                readonly property bool active: header.cluster.gear === modelData.gear

                text: modelData.label
                color: active ? header.textColr : header.dimColor
                font.family: header.fontFamily
                font.pixelSize: 30
                font.italic: true
                font.variableAxes: {
                    "wght": active ? 900 : 500
                }
            }
        }
    }

    Text {
        id: clock
        font.family: header.fontFamily
        font.pixelSize: 30

         anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: gears.verticalCenter
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
        anchors.verticalCenter: gears.verticalCenter

        text: header.cluster.miles + "mi"
        font.family: header.rangeFontFamily
        font.pixelSize: 30
        font.variableAxes: {
            "wght": 900
          }
          color: header.textColor
    }
}
