import QtQuick

Window {
    width: 1080
    height: 640
    visible: true
    color: "white"
    title: "Prius Cluster"
    FontLoader {
        id: geist_bold
        source: "./assets/fonts/GeistMonoBold.otf"
    }
    FontLoader {
        id: clash
        source: "./assets/fonts/ClashDisplay-Variable.ttf"
    }

    property int speed: 20
    property string gear: "D"

    Row {
        spacing: 32
        anchors.centerIn: parent
        Column {
            spacing: 32
            Row {
                height: 128
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    text: speed
                    font.family: clash.font.family
                    font.pixelSize: 128
                    font.italic: true
                    color: "royalblue"
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    text: "mph"
                    font.family: clash.font.family
                    font.pixelSize: 48
                    font.italic: true
                    color: "royalblue"
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Text {
                text: gear === "P" ? "Parked" : "Driving"
                color: gear === "P" ? "green" : "black"
                font.pixelSize: 48
                font.family: clash.font.family
                font.variableAxes: {
                    "wght": 650
                }
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Rectangle {
        id: bottomSpeed
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        width: 300
        height: 5
        anchors.bottomMargin: 100
        color: "royalblue"
    }
}
