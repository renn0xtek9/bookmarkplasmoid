import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.kquickcontrolsaddons 2.0 as KQuickControlsAddons
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras
import MyPlugins 1.0 as MyPlugins

PlasmaExtras.ScrollArea {
	id: scrollView
	width:childrenRect.width
	anchors.fill:parent
// 	focus: true
	
	ListView{
		id: view 
		height:24*view.count 
		width:200
		focus:true
		visible:true
		model:visualModel
// 		highlightFollowsCurrentItem: true
// 		highlight: Component { 
// 			Button {
// 				id: high
// 				text: "PUTAAAAAINNNN"
// 			}
// 		}	
		highlight: PlasmaComponents.Highlight {
// 			anchors.bottomMargin: -listMargins.bottom
			y: 1
		}
		VisualDataModel {
			id: visualModel
			model: itemmodel
			delegate: Bookmarkdelegate{
				bookmarktext: display
				iconSource: icon
				tooltip: ttp
			}
			
			
			
			
			
// 			Button{
// 				iconSource :icon
// 				height: 24
// 				width: view.width
// // 				text: ListView.isCurrentItem? "merde":display
// 				tooltip: ttp
// 				
// 				MouseArea{
// 					anchors.fill: parent
// 					acceptedButtons: Qt.LeftButton | Qt.RightButton
// 					onClicked:{
// 						if(mouse.button & Qt.LeftButton) {
// 							if (!isFolder)
// 							{
// 								Qt.openUrlExternally(tooltip)
// 							}
// 							else
// 							{
// 								visualModel.rootIndex=view.model.modelIndex(index)
// 							}
// 						}
// 						if(mouse.button & Qt.RightButton)
// 						{
// 							visualModel.rootIndex=visualModel.parentModelIndex()						 
// 						}
// 					}
// 				}
// 			}
		}
		Keys.onDownPressed: {
			console.log("Uppressed")
			if (view.currentIndex + 2 < view.count - 1)
				view.currentIndex += 2;
		}
		Keys.onUpPressed: {
			if (view.currentIndex - 2 >= 0)
				view.currentIndex -= 2;
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
		onCountChanged: {
// 			mainrepresentation.Layout.preferredHeight=24*view.count+view.headerItem.height
			mainrepresentation.Layout.minimumHeight=24*view.count+view.headerItem.height
// 			mainrepresentation.Layout.maximumHeight=24*view.count+view.headerItem.height
// 			mainrepresentation.Layout.height=24*view.count
			console.log("Layout preferred set at" +24*view.count)
		}
	}
}
