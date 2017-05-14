import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.XmlListModel 2.0
import org.kde.plasma.plasmoid 2.0 //needed to give the Plasmoid attached properties
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import MyPlugins 1.0 as MyPlugins

PlasmaComponents.Button {
	id: mainbutton
	Plasmoid.title: "Bookmarks plasmoid"
	anchors.bottom: parent.bottom
	anchors.horizontalCenter: parent.horizontalCenter
	//             anchors.horizontalCenter: rectangleLayout.horizontalCenter
	Layout.alignment: Qt.AlignTop
	Layout.preferredWidth: 80
	Layout.preferredHeight: 40
	
	iconName: "favorites"
	text: "Bookmarks"
	activeFocusOnPress: true
	onClicked: view.focusChanged(false)
	
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
	
	ListView{
		id: view 
		anchors.bottom: parent.top
		anchors.bottomMargin: 10			//TODO this is probably not the proper way to have the bottom of List view sitting on top of the button		
		height: 24*view.count
		
		visible:false
		model:itemmodel
// 		highlight: highlightBar;
		focus:true
		highlightFollowsCurrentItem: true
		onCountChanged: {
			/* calculate ListView dimensions based on content */

			// get QQuickItem which is a root element which hosts delegate items
			var root = view.visibleChildren[0]
			var listViewHeight = 0
			var listViewWidth = 0

			// iterate over each delegate item to get their sizes
			for (var i = 0; i < root.visibleChildren.length; i++) {
				listViewHeight += root.visibleChildren[i].height
				listViewWidth  = Math.max(listViewWidth, root.visibleChildren[i].width)
			}

			view.height = listViewHeight
			view.width = listViewWidth
		}
		
		delegate: PlasmaComponents.Button{
			iconSource :icon
			height: 24
			width: 200
			text: display
			tooltip: tooltip
			minimumWidth: view.width
			onClicked:{
				console.log(icon+"clicked")
				
			}
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
				target: view;visible: true;currentItem:0}
			},
		State{
			name:"displaced"
			PropertyChanges{
			target: view ;x: 400;y: 400;visible:true}
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
	
	
	Connections{
		target:mainbutton
		onClicked:{
			if (view.state=="invisible"){
			view.state="visible"
			}
			else
			{
			view.state="invisible"
			}
		}
	}
	
}
