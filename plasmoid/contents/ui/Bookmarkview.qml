import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import org.kde.plasma.extras 2.0 as PlasmaExtras
import MyPlugins 1.0 as MyPlugins

PlasmaExtras.ScrollArea {
	id: scrollView
	width:childrenRect.width
	anchors.fill:parent
	focus: true
	ListView{
		id: view 
		height:24*view.count 
		width:200
		focus:true
		visible:true
		model:visualModel
		highlightFollowsCurrentItem: true
		VisualDataModel {
			id: visualModel
			model: itemmodel	
			delegate: Button{
				iconSource :icon
				height: 24
				width: view.width
				text: display
				tooltip: ttp
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
		header: RowLayout{
			id: head 
			height:30
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
				iconName:"bookmark-add-folder"
				text:qsTr("Add a source")
				tooltip: qsTr("Add a source of bookmarks")
				height: 24
				Layout.fillWidth: true
				onClicked:{
					mainrepresentation.state="editsourceview"
				}
			}
		}
		onCountChanged: {
			mainrepresentation.Layout.minimumHeight=24*view.count+view.headerItem.height
		}
	}
}
