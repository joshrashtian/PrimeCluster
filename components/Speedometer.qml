import QtQuick
import Cluster

Row {
  id: speedometer
    required property ClusterData cluster
    property string fontFamily
    property string textColor

    Text {
        id: speedText
        text: speedometer.cluster.speed
        font.family: fontFamily
        font.pixelSize: 192
        font.italic: true
        font.variableAxes: {
            "wght": 900
        }
        color: speedometer.textColor
    }
    Text {
        text: "mph"
        anchors.baseline: speedText.baseline
        font.family: fontFamily
        font.pixelSize: 72
        font.italic: true
        color: "gray"
    }
}
