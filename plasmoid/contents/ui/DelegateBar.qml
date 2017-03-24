import QtQuick.Layouts 1.3
import QtQuick 2.0
//DelegateBar.qml
//This file provides that components that constitute the "bar" in the List view that represent element from bookmarks.
Rectangle{
	id: delegatebar
	property alias bookmarkname: textfield.text
	property alias iconSize:iconcontainer.iconSize
	height: iconcontainer.iconSize
	RowLayout{
		id:	internlayout	
		anchors.left: parent.left
		
		Layout.minimumHeight: 16
		Layout.minimumWidth: 100
		Layout.preferredWidth: 200
		Layout.maximumWidth: 400
		
		Rectangle{	//The container of the text	
			id: textcontainer
			Layout.minimumWidth: 16
			Layout.minimumHeight: 16
			Layout.preferredWidth: 16
			Layout.preferredHeight: 16
			anchors.left: iconcontainer.right
			anchors.right: parent.right
			Text{
				id: textfield
// 				anchors.right: textcontainer.right
				text: "Bookmark"				
			}
		}
		Rectangle{	//The container of the icon
			id: iconcontainer
			anchors.left: parent.left
			Layout.minimumWidth: iconSize
			Layout.minimumHeight: iconSize
			property int iconSize:16
// 			Layout.preferredWidth: 50
// 			Layout.preferredHeight: 16
			Image{
				id: icon
				anchors.left: parent.left
				anchors.right: parent.right
// 				anchors.ho
				height: parent.iconSize
				width: parent.iconSize
				source: "/home/max/Pictures/icone/Png/1371178312_linux.png"
			}
		}
		
	}
}
