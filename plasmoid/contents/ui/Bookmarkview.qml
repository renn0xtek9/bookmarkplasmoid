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
	visible:true
	focus: true
	anchors.fill:parent
	Layout.fillHeight: true
	ListView{
		id: bookmarklist 
		anchors.fill: parent
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
				id: buttonrefresh
				anchors{
					right:parent.right
				}
				iconName:"view-refresh"
				text:qsTr("Refresh")
				tooltip: qsTr("Re-read sources")
				height: 24
				Layout.fillWidth: true
				onClicked:{
					itemmodel.ReadAllSources(true);
				}
			}
		}
		footer: PlasmaComponents.ToolButton{
			width:bookmarklist.width
			height:32
			focus:false
			iconSource: "go-previous-view"
			text: "Go back"
			visible:false 
			onClicked:{
				visualModel.rootIndex=visualModel.parentModelIndex();
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
				if (!(bookmarklist.currentIndex<bookmarklist.count)&&!(bookmarklist.currentIndex>0))
				{
					bookmarklist.currentIndex=bookmarklist.count-1
				}
				bookmarklist.currentIndex = bookmarklist.currentIndex-1 >0 ? bookmarklist.currentIndex-1 :0
				event.accepted = true;
			}
			if (event.key == Qt.Key_Down) {
				if (!(bookmarklist.currentIndex<bookmarklist.count)&&!(bookmarklist.currentIndex>0))
				{
					bookmarklist.currentIndex=0
				}
				bookmarklist.currentIndex = bookmarklist.currentIndex +1 < bookmarklist.count ? bookmarklist.currentIndex+1 : bookmarklist.count
				event.accepted = true;
			}
		}	
		onCountChanged: {
			mainrepresentation.Layout.minimumHeight=(bookmarklist.count*(32+units.smallSpacing)+bookmarklist.headerItem.height);  //TODO instead of silly 32 guess! , fixed it in the delegate and thake same height as delegate
// 			mainrepresentation.Layout.maximumHeight=(bookmarklist.count*(32+units.smallSpacing)+bookmarklist.headerItem.height);
			mainrepresentation.Layout.maximumHeight=mainrepresentation.Layout.minimumHeight;
			if(bookmarklist.count==0)
			{
				bookmarklist.footerItem.visible=true;
				bookmarklist.footerItem.focus=true;
				mainrepresentation.Layout.minimumHeight=bookmarklist.headerItem.height+bookmarklist.footerItem.height;
				mainrepresentation.Layout.maximumHeight=mainrepresentation.Layout.minimumHeight;
			}
		}
		onVisibleChanged:{
			if(visible)
			{
				itemmodel.konquerorBookmarks=plasmoid.configuration.konquerorpath
				itemmodel.okularBookmarks=plasmoid.configuration.okularpath
				itemmodel.firefoxBookmarks=plasmoid.configuration.firefoxpath
				itemmodel.chromeBookmarks=plasmoid.configuration.chromepath
				itemmodel.ReadAllSources(false);
			}
		}
	}	
}
