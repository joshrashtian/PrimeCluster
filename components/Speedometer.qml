import QtQuick
import QtQuick.Shapes
import Cluster

Item {
    id: speedometer

    required property ClusterData cluster

    property string fontFamily
    property string inCircleFontFamily
    property string turnSignalFamily
    property color textColor: "white"
    property color unitColor: "gray"
    property color trackColor: "#2a2f38"
    property color arcColor: "#50ffffff"
    property int maxSpeed: 100
    property real displaySpeed: speedometer.cluster.speed

    Behavior on displaySpeed {
        NumberAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }

    width: 460
    height: 460

    property real startAngle: 135
    property real sweepAngle: 270
    property real centerX: width / 2
    property real centerY: height / 2
    property real arcRadius: width / 2 - 10
    property real labelRadius: arcRadius - 40

    Shape {
        anchors.fill: parent
        preferredRendererType: Shape.CurveRenderer

        ShapePath {
            strokeColor: speedometer.trackColor
            strokeWidth: 10
            fillColor: "transparent"
            capStyle: ShapePath.RoundCap

            PathAngleArc {
                centerX: speedometer.centerX
                centerY: speedometer.centerY
                radiusX: speedometer.arcRadius
                radiusY: speedometer.arcRadius
                startAngle: speedometer.startAngle
                sweepAngle: speedometer.sweepAngle
            }
        }

        ShapePath {
            strokeColor: speedometer.arcColor
            strokeWidth: 10
            fillColor: "transparent"
            capStyle: ShapePath.RoundCap

            PathAngleArc {
                centerX: speedometer.centerX
                centerY: speedometer.centerY
                radiusX: speedometer.arcRadius
                radiusY: speedometer.arcRadius
                startAngle: speedometer.startAngle
                sweepAngle: speedometer.sweepAngle * Math.min(speedometer.displaySpeed / speedometer.maxSpeed, 1)
            }
        }
    }

    Repeater {
        model: speedometer.maxSpeed / 20 + 1

        Text {
            required property int index
            readonly property int value: index * 20
            readonly property real rad: (speedometer.startAngle + speedometer.sweepAngle * value / speedometer.maxSpeed) * Math.PI / 180

            x: speedometer.centerX + speedometer.labelRadius * Math.cos(rad) - width / 2
            y: speedometer.centerY + speedometer.labelRadius * Math.sin(rad) - height / 2
            font.family: speedometer.inCircleFontFamily
            text: value
            color: value <= speedometer.displaySpeed ? speedometer.textColor : speedometer.trackColor
            font.pixelSize: value <= speedometer.displaySpeed ? 25 : 20
            font.features: {
                "tnum": 1
            }

            Behavior on color {
                ColorAnimation {
                    duration: 200
                }
            }
            Behavior on font.pixelSize {
                NumberAnimation {
                    duration: 50
                }
            }
        }
      }

      property real currentAngle: startAngle + sweepAngle * Math.min(displaySpeed / maxSpeed, 1)

Item {
    anchors.fill: parent
    rotation: speedometer.currentAngle

    Rectangle {
        x: speedometer.centerX + speedometer.arcRadius - 50
        y: speedometer.centerY - height / 2 + 4
        width: 60
        height: 5
        radius: 1.5
        color: "#ffffff"
        antialiasing: true
    }
}
    Column {
        id: readout
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
    TurnSignals {
        cluster: speedometer.cluster
        iconFamily: speedometer.turnSignalFamily
        anchors.centerIn: parent
        width: speedometer.width + 150
    }
}
