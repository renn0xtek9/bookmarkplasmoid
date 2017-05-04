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
// 	onClicked: mainlistview.focusChanged(false)
	
	MyPlugins.Bookmarkmodel{
		id: itemmodel
	}
	ListView{
		id: view 
		height: 400
		visible:true
		model:itemmodel
		delegate: Rectangle {
              height: 30;
              width: 100;
              Text {
                 id: itemText
                 text: display;
			}
		}
		footer: Rectangle {
			width: parent.width; height: 30;
			Text{
				id: footertext
				text: "Footer"
			}
		}
	}
	
}
