import QtQuick.Layouts 1.3
import QtQuick 2.0
import QtQuick.XmlListModel 2.0

//DelegateBar.qml
//This file provides that components that constitute the "bar" in the List view that represent element from bookmarks.
Rectangle{
	id: delegatebar
	height: iconcontainer.iconSize
	width: 100
	border.color: Qt.lighter(color)
	focus: true
	Keys.onEnterPressed: clicked()
	Keys.onLeftPressed: clicked()
	Keys.onRightPressed: clicked()
	//Propertys and signals
	property alias bookmarkname: textfield.text
	property alias iconSize:iconcontainer.iconSize
	property alias iconSource:icon.source
	signal clicked
	onClicked:{
		console.log("clicked:" +bookmarkname)
		plasmoid.runCommand("xdg-open", [bookmarkpath])	 //TODO define bookmarkpath in the role of the model
	}
	MouseArea {
				anchors.fill: parent
				onClicked: delegatebar.clicked()
	}
	//TODO define a tooltip
	
// 	ToolTip{
// 		id: tooltip
// 	}
	//Get the system palette
	SystemPalette { id: syspalette ; colorGroup: SystemPalette.Active }
	RowLayout{
		id:	internlayout	
		anchors.bottom: parent.bottom
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		Layout.preferredHeight: iconcontainer.iconSize
		Layout.minimumWidth: 100
		Layout.preferredWidth: 100
		Layout.maximumWidth: 400
		Rectangle{	//The container of the text	
			id: textcontainer
			color: syspalette.window
			Layout.minimumWidth: 100
			Layout.minimumHeight: 16
			Layout.preferredWidth: 200
			Layout.preferredHeight: iconcontainer.iconSize
			anchors.left: iconcontainer.right
// 			anchors.right: parent.right
			Text{
				id: textfield
				anchors.left: textcontainer.left
				anchors.leftMargin: 10
				text: "Bookmark"
				elide: Text.ElideMiddle	
				color: syspalette.buttonText
			}
		}
		Rectangle{	//The container of the icon
			id: iconcontainer
			color: syspalette.window
			anchors.left: parent.left
			anchors.bottom: parent.bottom
			Layout.minimumWidth: iconSize
			Layout.minimumHeight: iconSize
			property int iconSize:16
			Image{
				id: icon
				anchors.left: parent.left
				anchors.right: parent.right
				height: parent.iconSize
				width: parent.iconSize
				source: "/home/max/Pictures/icone/Png/1371178312_linux.png"		//TODO remove this fucking default icon
			}
		}
	}
}
