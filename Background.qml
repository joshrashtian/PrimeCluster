import QtQuick

Rectangle {
    id: root

    property color topColor: "#ff7e5f"
    property color midColor: "#ffffff"
    property color bottomColor: "#ff7e5f"

    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop {
            position: 0.0
            color: root.topColor
        }
        GradientStop {
            position: 0.5
            color: root.midColor
        }
        GradientStop {
            position: 1.0
            color: root.bottomColor
        }
    }

    Behavior on topColor {
        ColorAnimation {
            duration: 400
        }
    }
    Behavior on midColor {
        ColorAnimation {
            duration: 400
        }
    }
    Behavior on bottomColor {
        ColorAnimation {
            duration: 400
        }
    }
}
