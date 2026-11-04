import QtQuick
import Cluster

Item {
    id: gears
    required property ClusterData cluster
    property string fontFamily

    property string textColor
    property string dimColor

    implicitWidth: row.implicitWidth
    implicitHeight: row.implicitHeight

    Rectangle {
        anchors.fill: parent
        color: "gray"
        border.color: "#66000000"

        border.width: 2
        radius: 10
        opacity: 0.5
    }
    Row {
        id: row
        spacing: 1
        leftPadding: 16
        rightPadding: 16
        topPadding: 6
        bottomPadding: 6

        anchors.verticalCenter: parent.verticalCenter
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
                readonly property bool active: gears.cluster.gear === modelData.gear

                text: modelData.label
                color: active ? gears.textColor : gears.dimColor
                font.family: gears.fontFamily
                font.pixelSize: 30
                font.italic: true
                font.variableAxes: {
                    "wght": active ? 900 : 500
                }
            }
        }
    }
}
