import QtQuick

Item {
    id: music

    required property MediaData media
    property color textColor: "#f2f4f7"
    property color dimColor: "#5c6470"
    property color accentColor: "#5b8cff"
    property string fontFamily: ""

    function formatTime(seconds) {
        const s = Math.max(0, Math.floor(seconds))
        const m = Math.floor(s / 60)
        const r = s % 60
        return m + ":" + (r < 10 ? "0" : "") + r
    }

    Column {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.8, 360)
        spacing: 12

        Rectangle {
            width: 220
            height: 220
            radius: 16
            color: "#1a1d22"
            clip: true
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                anchors.fill: parent
                source: music.media.art.url
                fillMode: Image.PreserveAspectCrop
                asynchronous: true
                visible: status === Image.Ready
            }

            Text {
                anchors.centerIn: parent
                text: "\ue122"
                font.family: "lucide"
                font.pixelSize: 64
                color: music.dimColor
                visible: music.media.art.url.toString() === ""
            }
        }

        Text {
            width: parent.width
            text: music.media.title || "Not Playing"
            color: music.textColor
            font.family: music.fontFamily
            font.pixelSize: 28
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }

        Text {
            width: parent.width
            text: music.media.artist
            color: music.textColor
            opacity: 0.8
            font.family: music.fontFamily
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
            visible: text !== ""
        }

        Text {
            width: parent.width
            text: music.media.album
            color: music.dimColor
            font.family: music.fontFamily
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
            visible: text !== ""
        }

        Rectangle {
            width: parent.width
            height: 4
            radius: 2
            color: music.dimColor
            opacity: 0.4

            Rectangle {
                height: parent.height
                radius: parent.radius
                color: music.accentColor
                width: music.media.duration > 0
                       ? parent.width * Math.min(music.media.elapsed / music.media.duration, 1)
                       : 0
                Behavior on width { NumberAnimation { duration: 250 } }
            }
        }

        Item {
            width: parent.width
            height: elapsedText.height

            Text {
                id: elapsedText
                anchors.left: parent.left
                text: music.formatTime(music.media.elapsed)
                color: music.dimColor
                font.pixelSize: 14
                font.features: { "tnum": 1 }
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: music.media.playing ? "Playing" : "Paused"
                color: music.dimColor
                font.pixelSize: 14
                visible: music.media.title !== ""
            }

            Text {
                anchors.right: parent.right
                text: music.formatTime(music.media.duration)
                color: music.dimColor
                font.pixelSize: 14
                font.features: { "tnum": 1 }
            }
        }

        Text {
            width: parent.width
            text: music.media.appName
            color: music.dimColor
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            visible: text !== ""
        }
    }
}
