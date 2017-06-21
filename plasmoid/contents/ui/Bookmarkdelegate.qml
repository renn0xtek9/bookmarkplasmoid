/********************************************************************
This file is part of the KDE project.

Copyright (C) 2014 Joseph Wenninger <jowenn@kde.org>

Based on the clipboard applet:
Copyright (C) 2014 Martin Gräßlin <mgraesslin@kde.org>
Copyright     2014 Sebastian Kügler <sebas@kde.org>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.kquickcontrolsaddons 2.0 as KQuickControlsAddons
import org.kde.plasma.core 2.0 as PlasmaCore


PlasmaComponents.ListItem {
	id: menuItem
	signal itemSelected(string uuid)
	signal newSession(string sessionname)
	signal remove(string uuid)
	property int itemheight 
	property bool showInput: false
	property string iconSource: ""
	property string bookmarktext: "No bookmark"
	property string tooltip: ""
	property bool isAFolder: true
	width: parent.width - units.gridUnit * 2
	height: itemheight
	MouseArea {
		anchors.fill: parent
		hoverEnabled: true
		acceptedButtons: Qt.LeftButton | Qt.RightButton
		onClicked: {
			if(mouse.button & Qt.LeftButton) {
				if (!isFolder)
				{
					Qt.openUrlExternally(tooltip)
				}
				else
				{
					visualModel.rootIndex=bookmarklist.model.modelIndex(index)
				}
			}
			if(mouse.button & Qt.RightButton)
			{
				visualModel.rootIndex=visualModel.parentModelIndex()						 
			}
			if (TypeRole!=1)
				menuItem.itemSelected(UuidRole);
			else {
				showInput=true; 
			}
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
// 				top:parent.top
// 				bottom:parent.bottom
			}
			PlasmaComponents.Label {
				height: implicitHeight
				anchors {
					left: parent.left
					right: parent.right
					top:parent.top
					bottom:parent.bottom
					rightMargin: units.gridUnit * 2
					leftMargin: units.gridUnit * 2
				}
				maximumLineCount: 1
				text: bookmarktext
				visible: !showInput // TypeRole: 0: Text, 1: Image, 2: Url
				elide: Text.ElideRight
				wrapMode: Text.Wrap
			}
			PlasmaCore.IconItem {
				width: units.iconSizes.small
				height: width
				anchors{
					top:parent.top
					bottom:parent.bottom
				}
				z: 900
				source: iconSource
				enabled: true
				visible: true
			}
		}
		RowLayout {
			id:sessionnameditlayout
			visible:showInput
			height: implicitHeight
			anchors {
				left: parent.left
				right: parent.right
				rightMargin: 0
				leftMargin: units.gridUnit * 2
			}
			/*Layout.fillWidth: true*/
			Item {
				width: units.gridUnit / 2 - parent.spacing
				height: 1
			}
			PlasmaComponents.ToolButton {
				iconSource: "dialog-cancel"
				tooltip: i18n("Cancel session creation")
				onClicked: showInput=false
			}
		}
		RowLayout { //This is the toolButton on the right side that shows a blue arrow depending on wether it is  a folder or not
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
