import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQml 2.2
import org.kde.plasma.plasmoid 2.0 //needed to give the Plasmoid attached properties
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras
import MyPlugins 1.0 as MyPlugins
import Qt.labs.settings 1.0

Item {
	id: mainWindow
	Plasmoid.toolTipMainText: i18n("Bookmarks")
	Plasmoid.icon: connectionIconProvider.connectionTooltipIcon
	Plasmoid.switchWidth: units.gridUnit * 10
	Plasmoid.switchHeight: units.gridUnit * 10	
	/*
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
							scrollView.state="invisible"
							editsourceview.state="visible"
						}
					}
				}
			}
			states: [
			State{
				name: "invisible"
				PropertyChanges {
					target: scrollView;visible: false}
			},
			State{
				name: "visible"
				PropertyChanges{
					target: scrollView;visible: true}
			}
			]
			
			
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
	}*/
	ColumnLayout{
		id:editsourceview
		spacing:2
		width:300
		height:600
		state:"visible"
		anchors.fill: parent
		Selectpathbar{
			id: okularselect 
			iconName :"bookmark-new-list"
			text: "Okular"
			tooltip: "Choose path for okular bookmarks"
			textfield: plasmoid.configuration.okularpath
		}
		Selectpathbar{
			id: konquerorselect 
			iconName :"bookmark-new-list"
			text: "KDE"
			tooltip: "Choose path for Konqueror (KDE) bookmarks"
			textfield: plasmoid.configuration.konquerorpath
		}
		Selectpathbar{
			id: firefoxselect 
			iconName :"bookmark-new-list"
			text: "Firefox"
			tooltip: "Choose path for firefox bookmarks"
			textfield: plasmoid.configuration.firefoxpath
		}
		Selectpathbar{
			id: chromeselect 
			iconName :"bookmark-new-list"
			text: "Chrome"
			tooltip: "Choose path for Chrome bookmarks"
			textfield: plasmoid.configuration.chromepath
		}
		
		states: [
		State{
			name: "invisible"
			PropertyChanges {
				target: editsourceview;visible: false}
		},
		State{
			name: "visible"
			PropertyChanges{
				target: editsourceview;visible: true}
		}
		]		
		
	}
}


