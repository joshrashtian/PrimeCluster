import QtQuick
import Cluster

Item {
    id: header
    required property ClusterData cluster

    property string fontFamily
    property string rangeFontFamily

    height: gears.height

    Row {
        id: gears
        anchors.left: parent.left
        spacing: 1

        Repeater {
            model: [
                { label: "P", gear: ClusterData.GearParking },
                { label: "R", gear: ClusterData.GearReverse },
                { label: "N", gear: ClusterData.GearNeutral },
                { label: "D", gear: ClusterData.GearDrive },
                { label: "B", gear: ClusterData.GearB }
            ]

            Text {
                required property var modelData
                readonly property bool active: header.cluster.gear === modelData.gear

                text: modelData.label
                color: active ? "black" : "#555555"
                font.family: header.fontFamily
                font.pixelSize: 30
                font.italic: true
                font.variableAxes: { "wght": active ? 900 : 500 }
            }
        }
    }

    Text {
        anchors.right: parent.right
        anchors.verticalCenter: gears.verticalCenter

        text: header.cluster.miles + "mi"
        font.family: header.rangeFontFamily
        font.pixelSize: 30
        font.variableAxes: { "wght": 900 }
    }
}
