import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.kquickcontrolsaddons 2.0 as KQuickControlsAddons
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore

PlasmaComponents.ListItem {
    id: menuItem

    property int itemheight
    property bool showInput: false
    property string iconSource: ""
    property string bookmarktext: "No bookmark"
    property string tooltip: ""
    property bool isAFolder: true

    signal itemSelected(string uuid)
    signal newSession(string sessionname)
    signal remove(string uuid)

    width: parent.width - units.gridUnit * 2
    height: itemheight

    Helper {
        id: helper
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button & Qt.LeftButton) {
                if (!isFolder)
                    helper.openURL(tooltip);
                else
                    visualModel.rootIndex = bookmarklist.model.modelIndex(index);
            }
            if (mouse.button & Qt.RightButton)
                visualModel.rootIndex = visualModel.parentModelIndex();

            if (TypeRole != 1)
                menuItem.itemSelected(UuidRole);
            else
                showInput = true;
        }
        onEntered: bookmarklist.currentIndex = index
        onExited: bookmarklist.currentIndex = -1

        Item {
            id: label

            height: itemheight

            anchors {
                left: parent.left
                leftMargin: units.gridUnit / 2
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            PlasmaComponents.Label {
                height: implicitHeight
                maximumLineCount: 1
                text: bookmarktext
                visible: !showInput // TypeRole: 0: Text, 1: Image, 2: Url
                elide: Text.ElideRight
                wrapMode: Text.Wrap

                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                    rightMargin: units.gridUnit * 2
                    leftMargin: units.gridUnit * 2
                }

            }

            PlasmaCore.IconItem {
                width: units.iconSizes.small
                height: width
                z: 900
                source: iconSource
                enabled: true
                visible: true

                anchors {
                    top: parent.top
                    bottom: parent.bottom
                }

            }

        }

        RowLayout {
            id: sessionnameditlayout

            visible: showInput
            height: implicitHeight

            anchors {
                left: parent.left
                right: parent.right
                rightMargin: 0
                leftMargin: units.gridUnit * 2
            }

            Item {
                width: units.gridUnit / 2 - parent.spacing
                height: 1
            }

            PlasmaComponents.ToolButton {
                iconSource: "dialog-cancel"
                tooltip: i18n("Cancel session creation")
                onClicked: showInput = false
            }

        }

        RowLayout {
            //The toolButton on the right side that shows an arrow depending on wether it is  a folder or not
            id: toolButtonsLayout

            anchors {
                right: label.right
                verticalCenter: parent.verticalCenter
            }

            PlasmaComponents.ToolButton {
                iconSource: isFolder ? "go-next-view" : ""
                tooltip: i18n("View content")
            }

        }

    }

}
