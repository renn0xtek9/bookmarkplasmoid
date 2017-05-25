import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item{
	height:30
	width:parent.width
	property alias iconName: button.iconName
	property alias text: button.text
	property alias tooltip: button.tooltip
	property alias textfield:field.text
	anchors{
		right:parent.right
		left:parent.left
	}
	RowLayout{
		anchors{
			right:parent.right
			left:parent.left
		}
		Button{
			id:button
			iconName:"bookmark-new-list"
			text:qsTr("Choose")
			tooltip: qsTr("Select bookmarks Source")
			anchors{
				right:parent.right
			}
			onClicked:{
// 				fileDialog.visible=true;				
			}
		}
		TextField{
			id:field
			width:parent.width
			text:""
			anchors{
				left:parent.left 
				right:button.left
			}
		}
	}	
}
