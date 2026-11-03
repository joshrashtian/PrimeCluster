import QtQuick

Item {
    id: nav

    property var tabs: ["Drive", "Media"]
    property var tabIcons: ["\ue4fd", "\ue34a"]
    property int currentIndex: 0
    property string fontFamily
    property string iconFontFamily
    property color activeColor: "black"
    property color inactiveColor: "#555555"
    property color accentColor: "royalblue"
    focus: true
    signal selected(int index)

    implicitWidth: content.implicitWidth
    implicitHeight: content.implicitHeight

    function select(i) {
        if (i >= 0 && i < tabs.length && i !== currentIndex)
            selected(i);
    }

    Keys.onPressed: event => {
        if (event.key === Qt.Key_Right) {
            select(nav.currentIndex + 1);
            event.accepted = true;
        } else if (event.key === Qt.Key_Left) {
            select(nav.currentIndex - 1);
            event.accepted = true;
        }
    }

    Row {
        id: content
        spacing: 32

        Text {
            text: "‹"
            font.pixelSize: 28
            color: nav.activeColor
            opacity: nav.currentIndex > 0 ? 1 : 0.3
            anchors.verticalCenter: tabsRow.verticalCenter
            TapHandler {
                onTapped: nav.select(nav.currentIndex - 1)
            }
        }

        Row {
            id: tabsRow
            spacing: 28

            Repeater {
                id: tabRepeater
                model: nav.tabs

                Row {
                    required property string modelData
                    required property int index
                    readonly property bool active: index === nav.currentIndex
                    spacing: 8
                    bottomPadding: 12

                    Text {
                        text: nav.tabIcons[index]
                        font.family: nav.iconFontFamily
                        font.pixelSize: 18
                        color: active ? nav.activeColor : nav.inactiveColor
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: modelData
                        font.family: nav.fontFamily
                        font.pixelSize: 16
                        font.weight: active ? Font.Black : Font.DemiBold
                        color: active ? nav.activeColor : nav.inactiveColor
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    TapHandler {
                        onTapped: nav.select(index)
                    }
                }
            }
        }

        Text {
            text: "›"
            font.pixelSize: 28
            color: nav.activeColor
            opacity: nav.currentIndex < nav.tabs.length - 1 ? 1 : 0.3
            anchors.verticalCenter: tabsRow.verticalCenter
            TapHandler {
                onTapped: nav.select(nav.currentIndex + 1)
            }
        }
    }   // ← content closes here now

    // Underline: a sibling of content, so the Row doesn't lay it out
    Rectangle {
        readonly property Item target: tabRepeater.count > nav.currentIndex
                                       ? tabRepeater.itemAt(nav.currentIndex) : null

        visible: target !== null
        x: content.x + tabsRow.x + (target ? target.x : 0)
        y: content.y + tabsRow.y + tabsRow.height - height
        width: target ? target.width : 0
        height: 3
        radius: 1.5
        color: nav.accentColor

        Behavior on x {
            NumberAnimation { duration: 220; easing.type: Easing.OutCubic }
        }
        Behavior on width {
            NumberAnimation { duration: 220; easing.type: Easing.OutCubic }
        }
    }
}
