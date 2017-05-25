import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import org.kde.plasma.extras 2.0 as PlasmaExtras
import MyPlugins 1.0 as MyPlugins

PlasmaExtras.ScrollArea {
	id: scrollView
	width:view.width
	height:view.height
	anchors {
		bottom: parent.bottom
	} 
	focus: true
	ListView{
		id: view 
		anchors.fill: parent
		anchors.bottom: parent.bottom
		height:24*view.count 
		width:200
		focus:true
		visible:true
		model:visualModel
		highlightFollowsCurrentItem: true
		MyPlugins.Bookmarkmodel{
			id: itemmodel
			konquerorBookmarks: plasmoid.configuration.firefoxpath
			okularBookmarks: plasmoid.configuration.okularpath
			firefoxBookmarks: plasmoid.configuration.konquerorpath
		}	
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
		onCountChanged: {
			view.height=24*view.count
			scrollView.height=24*view.count
		}
		header: RowLayout{
			id: head 
			height:100
			anchors{
				left:parent.left 
				right:parent.right
				top:parent.top						
			}
			Button{
				id: buttonorganize
				iconName:"bookmarks-organize.png"
				text:qsTr("Edit bookmarks")
				tooltip: qsTr("Organize KDE Bookmarks")
				height: 24
				anchors{
					left:parent.left
					right:buttonadd.left
				}
				onClicked:{
					executable.exec("keditbookmarks")
				}
			}
			Button{
				id: buttonadd
				anchors{
					left:buttonorganize.right
					right:parent.right
				}
				iconName:"bookmark-add-folder"
				text:qsTr("Add a source")
				tooltip: qsTr("Add a source of bookmarks")
				height: 24
				onClicked:{
					mainWindow.height=1200;
					scrollView.visible=false
					editsourceview.visible=true
					scrollView.state="invisible"
					editsourceview.state="visible" //TODO fix it !!
				}
			}
		}
	}
}
