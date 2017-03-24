import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.XmlListModel 2.0
import org.kde.plasma.plasmoid 2.0 //needed to give the Plasmoid attached properties
import org.kde.plasma.components 2.0 as PlasmaComponents
// import DelegateBar.qml
Item{
	id: root
	Plasmoid.title: "Bookmarks plasmoid"
	PlasmaComponents.Button {
	id: mainbutton
	anchors.bottom: parent.bottom
	anchors.horizontalCenter: parent.horizontalCenter
	//             anchors.horizontalCenter: rectangleLayout.horizontalCenter
	Layout.alignment: Qt.AlignTop
	Layout.preferredWidth: 80
	Layout.preferredHeight: 20
	iconName: "bookmarks"
	text: "start"
	activeFocusOnPress: true
	onClicked: mainlistview.focusChanged(false)
	XmlListModel {
		id: xmlModel
		source: "/home/max/.local/share/konqueror/bookmarks.xml"
		query: "/xbel/(bookmark|folder)"
	// 	namespaceDeclarations:"declare namespace bookmark"
		XmlRole { name: "name"; query: "title/string()" }
	// 	XmlRole { name: "icon"; query: "info/metadata/icon@name/string()" }
		XmlRole { name: "href"; query: "@href/string()"}
	}
	XmlListModel {
		id: fodlerModel
		source: "/home/max/.local/share/konqueror/bookmarks.xml"
		query: "/xbel/(bookmark|folder)"
	// 	namespaceDeclarations:"declare namespace bookmark"
		XmlRole { name: "name"; query: "title/string()" }
	// 	XmlRole { name: "icon"; query: "info/metadata/icon@name/string()" }
		XmlRole { name: "href"; query: "@href/string()"}
	}

	Component {
		id: highlightBar
		Rectangle {
		width: mainlistview.width; height: 30
		color: "#FFFF88"
		y: mainlistview.currentItem.y;
		Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
		}
	}
	Rectangle{
		id: pagerectangle
		visible: false
		width: mainlistview.width
		height: 200
		states: [
		State{
			name: "invisible"
			PropertyChanges {
			target: pagerectangle
			visible: false
			}
			},
		State{
			name: "visible"
			PropertyChanges{
				target: pagerectangle
				visible: true
			}
			},
		State{
			name:"displaced"
			PropertyChanges{
			target: pagerectangle
			x: 400
			y: 400
			visible:true
			}
		}
		]
		transitions: [
		Transition {
			NumberAnimation {
			target: pagerectangle
			property: "x,y"
			duration: 200
			easing.type: Easing.InOutQuad
			}

		}
		]
	}
	ColumnLayout{
		spacing: 2 
		Item{
		id: mainitem
		Layout.alignment: Qt.AlignTop
		Layout.preferredWidth: 80
		Layout.preferredHeight: 20
		state: "hided"
		states: [
			State {
			name: "normal"
			PropertyChanges {
				target: mainlistview;visible:true}
			},
			State {
			name: "hided"
			PropertyChanges {
				target: mainlistview;visible:false}
			}
		]
		ListView{
			id: mainlistview
			width: 300
			height: 1000
			spacing: 0
	//                 model: ContactModel{} 
			model:  xmlModel
			currentIndex: 4
			focus:true
// 			delegate: PlasmaComponents.Button {
// 				onClicked: {console.log("clicked",name)
// 					pagerectangle.x=200
// 					pagerectangle.width=500
// 					pagerectangle.y=500
// 					if (pagerectangle.state=="invisible"){
// 					pagerectangle.state="displaced"
// 					}
// 					else
// 					{
// 					pagerectangle.state="invisible"
// 					}
// 
// 				}
// 				//                         iconName: icon
// 				width: mainlistview.width
// 				height: 30
// 				text: name + " " + href
// 				tooltip: href                    
// 			}
			delegate: DelegateBar{
				width: mainlistview.width 
				iconSize:16
				bookmarkname: name			
			}
			
			visible: true
			highlight: highlightBar
			highlightFollowsCurrentItem: true
		}
		}
		Connections{
		target:mainbutton
		onClicked:{
			if (mainitem.state=="normal"){
			mainitem.state="hided"
			}
			else
			{
			mainitem.state="normal"
			}
		}
		}
	}
	}
}
