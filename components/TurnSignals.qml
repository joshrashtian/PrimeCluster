import QtQuick
import Cluster

Item {
    id: turnsignals
    required property ClusterData cluster
    property string iconFamily
    property color onColor: "#3ddc84"
    property int iconSize: 72

    implicitHeight: leftArrow.implicitHeight

    Text {
        id: leftArrow
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text: "\ue41e"
        font.family: turnsignals.iconFamily
        font.pixelSize: turnsignals.iconSize
        color: turnsignals.onColor
        visible: turnsignals.cluster.turnSignals.left
    }

    Text {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: "\ue41f"
        font.family: turnsignals.iconFamily
        font.pixelSize: turnsignals.iconSize
        color: turnsignals.onColor
        visible: turnsignals.cluster.turnSignals.right
    }
}
