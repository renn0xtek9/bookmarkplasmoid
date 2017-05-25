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
import QtQuick.Dialogs 1.2
Item {
	id: mainWindow
	Plasmoid.toolTipMainText: i18n("Bookmarks")
	Plasmoid.icon: connectionIconProvider.connectionTooltipIcon
	Plasmoid.switchWidth: units.gridUnit * 10
	Plasmoid.switchHeight: units.gridUnit * 10	
	Plasmoid.fullRepresentation:  Item{
		id: mainrepresentation
		
		Layout.minimumWidth:300
		MyPlugins.Bookmarkmodel{
			id: itemmodel
			konquerorBookmarks: plasmoid.configuration.firefoxpath
			okularBookmarks: plasmoid.configuration.okularpath
			firefoxBookmarks: plasmoid.configuration.konquerorpath
			chromeBookmarks: plasmoid.configuration.chromepath
		}	
		state:"editsourceview"
		Bookmarkview{
			id:bookmarkview
		}
		Editsourceview{
			id:editsourceview 
		}
		states: [
			State{
				name: "editsourceview"
				PropertyChanges {
					target: bookmarkview;visible: false}
				PropertyChanges{
					target: mainrepresentation;Layout.maximumHeight: 300}
				PropertyChanges{
					target: editsourceview;visible:true}
			},
			State{
				name: "bookmarkview"
				PropertyChanges{
					target: bookmarkview;visible: true}
				PropertyChanges{
					target: editsourceview;visible:false}
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
	}
	
		
// 		FileDialog{
// 			id: fileDialog
// 			modality: Qt.NonModal
// 			title: "Please choose a file"
// 			
// // 			visible: "hidden"
// 			folder: shortcuts.home
// 			onAccepted: {
// 				console.log("You chose: " + fileDialog.fileUrls)
// // 				Qt.quit()
// 				visible=false
// 			}
// 			onRejected: {
// 				console.log("Canceled")
// // 				Qt.quit()
// 				visible=false
// 			}
// 			Component.onCompleted: visible = true
// 		}
	
}


