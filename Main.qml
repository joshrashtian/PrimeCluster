import QtQuick

Window {
    id: root
    width: 1080
    height: 640
    visible: true
    color: theme.bgBottom
    title: "Prius Cluster"

    required property ClusterData cluster
    property bool darkMode: true
    property int index: 0

    QtObject {
        id: theme
        readonly property color bgTop: root.darkMode ? "#14171c" : "#ffffff"
        readonly property color bgMid: root.darkMode ? "#0b0d10" : "#cccccc"
        readonly property color bgBottom: root.darkMode ? "darkblue" : "#ccdddd"
        readonly property color text: root.darkMode ? "#f2f4f7" : "black"
        readonly property color textDim: root.darkMode ? "#5c6470" : "#555555"
        readonly property color speed: root.darkMode ? "#e6e9ee" : "gray"
        readonly property color accent: root.darkMode ? "#5b8cff" : "royalblue"
    }

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
    FontLoader {
        id: lucide
        source: "./assets/fonts/lucide.ttf"
    }

    Shortcut {
        sequence: "N"
        onActivated: root.darkMode = !root.darkMode
    }

    Background {
        anchors.fill: parent
        topColor: theme.bgTop
        midColor: theme.bgMid
        bottomColor: theme.bgBottom
    }

    Header {
        cluster: root.cluster
        fontFamily: nippo.font.family
        rangeFontFamily: clash.font.family
        iconFontFamily: lucide.font.family
        textColor: theme.text
        dimColor: theme.textDim
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 30
        }
    }

    // all the different pages
    Loader {
        active: root.index === 0
        anchors.centerIn: parent
        sourceComponent: Speedometer {
          fontFamily: dmsans.font.family
          inCircleFontFamily: nippo.font.family
            cluster: root.cluster
            textColor: theme.speed
            unitColor: theme.textDim
            turnSignalFamily: lucide.font.family
        }
    }

    Loader {
        active: root.index === 1
        sourceComponent: Music {}
    }
/*
    Gears {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 80
        cluster: root.cluster
        fontFamily: dmsans.font.family
        textColor: theme.text
        
        dimColor: theme.textDim
    }
    */

    ButtonSelect {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        tabs: ["Drive", "Music"]
        tabIcons: ["\ue4fd", "\ue34a"]
        iconFontFamily: lucide.font.family
        fontFamily: dmsans.font.family

        activeColor: theme.text
        inactiveColor: theme.textDim
        accentColor: theme.accent
        currentIndex: root.index
        onSelected: i => root.index = i
    }
}
