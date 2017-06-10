import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.kquickcontrolsaddons 2.0 as KQuickControlsAddons
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras
import MyPlugins 1.0 as MyPlugins
import QtQml.Models 2.2

PlasmaExtras.ScrollArea {
	id: scrollView
	width:childrenRect.width
	anchors.fill:parent
	focus: true
	ListView{
		id: view 
		height:24*view.count 
		anchors.fill: parent
		width:200
		focus:true
		visible:true
		model:visualModel
		highlightFollowsCurrentItem: true
		
		highlight: PlasmaComponents.Highlight {
			y: 0
		}
		DelegateModel {
			id: visualModel
			model: itemmodel
			delegate: Bookmarkdelegate{
				bookmarktext: display
				iconSource: icon
				tooltip: ttp
			}
		}
		header: RowLayout{
			id: head 
			height:30
			focus:false
			anchors{
				left:parent.left 
				right:parent.right
			}
			Button{
				id: buttonorganize
				iconName:"bookmarks-organize.png"
				text:qsTr("Edit bookmarks")
				tooltip: qsTr("Organize KDE Bookmarks")
				Layout.fillWidth: true
				height: 24
				anchors{
					left:parent.left
				}
				onClicked:{
					executable.exec("keditbookmarks "+itemmodel.konquerorBookmarks)
				}
			}
			Button{
				id: buttonadd
				anchors{
					right:parent.right
				}
				iconName:"bookmark-new-list"
				text:qsTr("Edit sources")
				tooltip: qsTr("Edit the various bookmark sources")
				height: 24
				Layout.fillWidth: true
				onClicked:{
					mainrepresentation.state="editsourceview"
				}
			}
		}
		Keys.onPressed: {
			if (event.key == Qt.Key_Left) {
				console.log("move left");
				event.accepted = true;
			}
			if (event.key == Qt.Key_Right) {
				console.log("move right");
				event.accepted = true;
			}
			if (event.key == Qt.Key_Up) {
				console.log("move up");
				event.accepted = true;
			}
			if (event.key == Qt.Key_Down) {
				console.log("move down");
				event.accepted = true;
			}
		}	
		onCountChanged: {
// 			mainrepresentation.Layout.preferredHeight=24*view.count+view.headerItem.height
			mainrepresentation.Layout.minimumHeight=24*view.count+view.headerItem.height
// 			mainrepresentation.Layout.maximumHeight=24*view.count+view.headerItem.height
// 			mainrepresentation.Layout.height=24*view.count
			console.log("Layout preferred set at" +24*view.count)
		}
	}
}
