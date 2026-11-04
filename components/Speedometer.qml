import QtQuick
import QtQuick.Shapes
import Cluster

Item {
    id: speedometer

    required property ClusterData cluster
property string fontFamily
    property color textColor: "white"
    property color unitColor: "gray"
    property color trackColor: "#2a2f38"
    property color arcColor: "#5b8cff"
    property int maxSpeed: 100
    property real displaySpeed: speedometer.cluster.speed

    Behavior on displaySpeed {
        NumberAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }

    width: 400
    height: 400

    Shape {
        anchors.fill: parent
        preferredRendererType: Shape.CurveRenderer

        ShapePath {
            strokeColor: speedometer.trackColor
            strokeWidth: 10
            fillColor: "transparent"
            capStyle: ShapePath.RoundCap

            PathAngleArc {
                centerX: speedometer.width / 2
                centerY: speedometer.height / 2
                radiusX: speedometer.width / 2 - 10
                radiusY: speedometer.height / 2 - 10
                startAngle: 135
                sweepAngle: 270
            }
        }

        ShapePath {
            strokeColor: speedometer.arcColor
            strokeWidth: 10
            fillColor: "transparent"
            capStyle: ShapePath.RoundCap

            PathAngleArc {
                centerX: speedometer.width / 2
                centerY: speedometer.height / 2
                radiusX: speedometer.width / 2 - 10
                radiusY: speedometer.height / 2 - 10
                startAngle: 135
                sweepAngle: 270 * Math.min(speedometer.displaySpeed / speedometer.maxSpeed, 1)
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: -40

        Text {
            id: speedText
            anchors.horizontalCenter: parent.horizontalCenter
            text: speedometer.cluster.speed
            font.family: speedometer.fontFamily
            font.pixelSize: 170
            font.variableAxes: {
                "wght": 700
            }
            font.features: {
                "tnum": 1
            }
            color: speedometer.textColor
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "mph"
            font.family: speedometer.fontFamily
            font.pixelSize: 32
            font.italic: true
            font.variableAxes: {
                "wght": 300
            }
            color: speedometer.unitColor
        }
    }
}
