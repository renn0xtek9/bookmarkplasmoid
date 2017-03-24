import QtQuick.Layouts 1.3
import QtQuick 2.0
//DelegateBar.qml
//This file provides that components that constitute the "bar" in the List view that represent element from bookmarks.
Rectangle{
	id: delegatebar
	property alias bookmarkname: textfield.text
	
	
	RowLayout{
		id:	internlayout	
		anchors.left: parent.left
		Rectangle{	//The container of the text	
			id: textcontainer
			Layout.maximumHeight: 32
			Layout.maximumWidth: 400
			anchors.left: iconcontainer.right
			Text{
				id: textfield
// 				anchors.right: textcontainer.right
				text: "start"				
			}
		}
		Rectangle{	//The container of the icon
			id: iconcontainer
			anchors.left: parent.left
			Layout.minimumWidth: 16
			Layout.minimumHeight: 16
			Layout.preferredWidth: 32
			Layout.maximumWidth: 32
			Layout.maximumHeight: 32
			Image{
				anchors.left: parent.left
// 				anchors.ho
				height: parent.height
				width: parent.height
				source: "/home/max/Pictures/icone/Png/1371178312_linux.png"
			}
		}
		
	}
}
