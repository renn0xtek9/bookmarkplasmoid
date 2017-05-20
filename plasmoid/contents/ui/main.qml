import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQml 2.2
import org.kde.plasma.plasmoid 2.0 //needed to give the Plasmoid attached properties
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras
import MyPlugins 1.0 as MyPlugins

Item {
	id: mainWindow
	Plasmoid.toolTipMainText: i18n("Bookmarks")
	Plasmoid.icon: connectionIconProvider.connectionTooltipIcon
	Plasmoid.switchWidth: units.gridUnit * 10
	Plasmoid.switchHeight: units.gridUnit * 10
	Plasmoid.fullRepresentation:  PlasmaExtras.ScrollArea {
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
						opacity:0.5   //TODO remove me once implemented
						anchors{
							left:buttonorganize.right
							right:parent.right
						}
						iconName:"bookmark-add-folder"
						text:qsTr("Add a source")
						tooltip: qsTr("Add a source of bookmarks")
						height: 24
						onClicked:{
							Qt.openUrlExternally(" keditbookmarks") //TODO call a dialog to selct other source (Firefox etc)
						}
					}
				}
			}
	}
	PlasmaCore.DataSource {
		id: executable
		engine: "executable"
		connectedSources: []
		onNewData: {
			var exitCode = data["exit code"]
			var exitStatus = data["exit status"]
			var stdout = data["stdout"]
			var stderr = data["stderr"]
			exited(exitCode, exitStatus, stdout, stderr)
			disconnectSource(sourceName) // cmd finished
		}
		function exec(cmd) {
			connectSource(cmd)
		}
		signal exited(int exitCode, int exitStatus, string stdout, string stderr)
	}
}


