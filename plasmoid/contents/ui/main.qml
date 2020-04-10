import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQml 2.2
import org.kde.plasma.plasmoid 2.0 //needd to give the Plasmoid attached properties
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras
import MyPlugins 1.0 as MyPlugins
import Qt.labs.settings 1.0
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2

Item {
	id: mainWindow
	Plasmoid.toolTipMainText: i18n("Bookmarks")
	Plasmoid.switchWidth: units.gridUnit * 10
	Plasmoid.switchHeight: units.gridUnit * 10	
	Plasmoid.activationTogglesExpanded: true
	MyPlugins.Bookmarkmodel{
		id: itemmodel
		konquerorBookmarks: plasmoid.configuration.konquerorpath
		okularBookmarks: plasmoid.configuration.okularpath
		firefoxBookmarks: plasmoid.configuration.firefoxpath
		chromeBookmarks: plasmoid.configuration.chromepath
	}
	Plasmoid.fullRepresentation:  Item{
		id: mainrepresentation
		Layout.minimumWidth:300
		state:"bookmarkview"
		Bookmarkview{
            id:bookmarkview
			itemheight: 32
		}
		states: [
			State{
				name: "bookmarkview"
				PropertyChanges{
					target: bookmarkview;visible: true}
				PropertyChanges{
					target: bookmarkview;focus: true}
			}
        ]
        Keys.onPressed: {
            switch(event.key){
            case Qt.Key_Escape:{
                console.log("Escape");
                plasmoid.expanded=false
            }
            case Qt.Key_L:{
                if (event.modifiers=== Qt.ControlModifier){
                    console.log("Ctrl+L")
                    bookmarkview.state="searchhasfocus"
                    bookmarkview.searchfieldhasactivefocus=true
                }
            }
            default:{
                console.log("key evnt: "+event.key)
            }
            }
        }
        function controlleft(){
            console.log("CTRL")
        }

        onActiveFocusChanged: {
            bookmarkview.focus=true
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


