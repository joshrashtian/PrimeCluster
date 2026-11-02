import QtQuick

Window {
    id: root
    width: 1080
    height: 640
    visible: true
    color: "white"
    title: "Prius Cluster"

    required property ClusterData cluster

    FontLoader {
        id: geist_bold
        source: "./assets/fonts/GeistMonoBold.otf"
    }
    FontLoader {
        id: clash
        source: "./assets/fonts/ClashDisplay-Variable.ttf"
    }
    FontLoader {
        id: nippo
        source: "./assets/fonts/Nippo.ttf"
    }
    FontLoader {
        id: dmsans
        source: "./assets/fonts/DMSans.ttf"
    }

    Background {
        anchors.fill: parent
        topColor: "#ffffff"
        midColor: "#cccccc"
        bottomColor: "#ccdddd"
    }

    Header {
        cluster: root.cluster
        fontFamily: nippo.font.family
        rangeFontFamily: clash.font.family
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 30
        }
    }

    property int index: 0

    // all the different pages
    Loader {
        active: index === 0
        sourceComponent: Speedometer {
            fontFamily: nippo.font.family
            cluster: root.cluster
        }

        anchors.centerIn: parent
    }

    Loader {
        active: index === 1
        sourceComponent: Music {}
    }

    Rectangle {
        id: bottomSpeed
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
        width: 840
        height: 5
        color: "royalblue"
      }

      ButtonSelect {
        
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        tabs: ["Drive", "Music"]
        currentIndex: root.index
        fontFamily: dmsans.font.family
        onSelected: (i) => root.index = i
      }
}
