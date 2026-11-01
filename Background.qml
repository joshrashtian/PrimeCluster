import QtQuick

Rectangle {
    id: root

    property color topColor: "#ff7e5f"
    property color midColor: "#feb47b"
    property color bottomColor: "#87a8e7"

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
}
