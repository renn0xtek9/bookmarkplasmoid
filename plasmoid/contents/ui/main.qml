import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.XmlListModel 2.0
import QtQml 2.2
import org.kde.plasma.plasmoid 2.0 //needed to give the Plasmoid attached properties
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import MyPlugins 1.0 as MyPlugins
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import org.kde.plasma.extras 2.0 as PlasmaExtras
PlasmaComponents.Button {
	id: mainbutton
	Plasmoid.title: "Bookmarks plasmoid"
	anchors.bottom: parent.bottom
	anchors.horizontalCenter: parent.horizontalCenter
	Layout.alignment: Qt.AlignTop
	Layout.preferredWidth: 80
	Layout.preferredHeight: 40
	iconName: "favorites"
	text: "Bookmarks"
	activeFocusOnPress: true
	onClicked: view.focusChanged(false)
	MouseArea{
		anchors.fill: mainbutton
		acceptedButtons: Qt.LeftButton | Qt.RightButton
		onClicked:{
			if (mouse.button == Qt.LeftButton)
			{
				ctextview.state="invisible"
				if (view.state=="invisible"){
					view.state="visible"
				}
				else{
					view.state="invisible"
				}
			}
			else if (mouse.button == Qt.RightButton)
			{
				view.state="invisible"
				if (ctextview.state=="invisible"){
					ctextview.state="visible"
				}
				else{
					ctextview.state="invisible"
				}
			}
		}
	}	
	MyPlugins.Bookmarkmodel{
		id: itemmodel
	}
	Component {
		id: highlightBar
		Rectangle {
		width: view.width; height: 30
		color: "#FFFF88"
		y: view.currentItem.y;
		Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
		}
	}	
	VisualDataModel {
		id: visualModel
		model: itemmodel	
// 		delegate: PlasmaComponents.Button{
		delegate: Button{
			iconSource :icon
			height: 24
			width: 200
			text: display
			tooltip: ttp
// 			minimumWidth: view.width
			MouseArea{
				anchors.fill: parent
				acceptedButtons: Qt.LeftButton | Qt.RightButton
				onClicked:{
					 if(mouse.button & Qt.LeftButton) {
						if (!isFolder)
						{
							Qt.openUrlExternally(tooltip)
						}
						else
						{
							visualModel.rootIndex=view.model.modelIndex(index)
						}
					 }
					 if(mouse.button & Qt.RightButton)
					 {
						 visualModel.rootIndex=visualModel.parentModelIndex()						 
					 }
				}
			}
		}
	}

	ListView{
		id: view 
		state:"invisible"
		height:24*view.count 
		focus:true
		anchors.bottom: mainbutton.top
		visible:false
		model:visualModel
		highlightFollowsCurrentItem: true
		onCountChanged: {
					view.height=24*view.count
				}
		states: [
			State{
				name: "invisible"
				PropertyChanges {
				target: view;visible: false}
				},
			State{
				name: "visible"
				PropertyChanges{
					target: view;visible: true}
				}
			]
			transitions: [
				Transition {
					NumberAnimation {
					target: view
					property: "x,y"
					duration: 200
					easing.type: Easing.InOutQuad
					}
				}
			]
	}
	ListView{
		id: ctextview
		anchors.bottom:mainbutton.top 
		height: 24*ctextview.count 
		visible:false 
		focus:true 
		state: "invisible"
		highlightFollowsCurrentItem:true 
		onCountChanged:{
			ctextview.height=24*ctextview.count
		}
		states: [
		State{
			name: "invisible"
			PropertyChanges {
				target: ctextview;visible: false}
		},
		State{
			name: "visible"
			PropertyChanges{
				target: ctextview;visible: true}
		}
		]
		model:
		ListModel {
			ListElement {
				iconTxt: qsTr("Edit Bookmarks")
				iconSrc: qsTr("bookmarks-organize.png")
				iconTip: qsTr("Organize KDE Bookmarks")
				iconAct: "editbookmarks"
			}
			ListElement {
				iconTxt: qsTr("Add a source")
				iconSrc: qsTr("bookmark-add-folder")
				iconTip: qsTr("Add a source of bookmarks")
				iconAct: "addasource"
			}
		}
		delegate:Button{
			iconName:iconSrc
			text:iconTxt
			tooltip: iconTip
			height: 24
			width: 200
			action:iconAct
			onClicked:{
				console.log(text+" "+action+" clicked")
				if (action=="editbookmarks"){
					openUrlExternally("keditbookmarks")
				}
			}
		}
	}	
}
