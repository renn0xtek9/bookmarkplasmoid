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
		id: bookmarklist 
		height:24*bookmarklist.count 
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
				isAFolder: isFolder
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
				visualModel.rootIndex=visualModel.parentModelIndex();
				event.accepted = true;
			}
			if (event.key == Qt.Key_Right || event.key==Qt.Key_Enter || event.key==Qt.Key_Return) {
				if (!bookmarklist.currentItem.isAFolder)
				{
					Qt.openUrlExternally(bookmarklist.currentItem.tooltip)
				}
				else
				{
					visualModel.rootIndex=bookmarklist.model.modelIndex(bookmarklist.currentIndex);
				}
				event.accepted = true;
			}
			if (event.key == Qt.Key_Up) {
				bookmarklist.currentIndex = bookmarklist.currentIndex-1 >0 ? bookmarklist.currentIndex-1 :0
				event.accepted = true;
			}
			if (event.key == Qt.Key_Down) {
				bookmarklist.currentIndex = bookmarklist.currentIndex +1 < bookmarklist.count ? bookmarklist.currentIndex+1 : bookmarklist.count-1
				event.accepted = true;
			}
		}	
		onCountChanged: {
// 			mainrepresentation.Layout.preferredHeight=24*bookmarklist.count+bookmarklist.headerItem.height
			mainrepresentation.Layout.minimumHeight=24*bookmarklist.count+bookmarklist.headerItem.height
// 			mainrepresentation.Layout.maximumHeight=24*bookmarklist.count+bookmarklist.headerItem.height
// 			mainrepresentation.Layout.height=24*bookmarklist.count
			console.log("Layout preferred set at" +24*bookmarklist.count)
		}
	}
}
