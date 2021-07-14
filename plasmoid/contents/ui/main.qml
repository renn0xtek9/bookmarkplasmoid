import Bookmarkmodelplugin 1.0 as Bookmarkmodelplugin
import Qt.labs.settings 1.0
import QtQml 2.2
import QtQml.Models 2.2
import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.plasmoid 2.0

Item {
    id: mainWindow

    Plasmoid.toolTipMainText: i18n("Bookmarks")
    Plasmoid.switchWidth: units.gridUnit * 10
    Plasmoid.switchHeight: units.gridUnit * 10
    Plasmoid.activationTogglesExpanded: true

    Bookmarkmodelplugin.Bookmarkmodel {
        id: itemmodel

        konquerorBookmarks: plasmoid.configuration.konquerorpath
        okularBookmarks: plasmoid.configuration.okularpath
        firefoxBookmarks: plasmoid.configuration.firefoxpath
        chromeBookmarks: plasmoid.configuration.chromepath
        filterItemsOnly: plasmoid.configuration.showonlyitem
    }

    PlasmaCore.DataSource {
        id: executable

        signal exited(int exitCode, int exitStatus, string stdout, string stderr)

        function exec(cmd) {
            connectSource(cmd);
        }

        engine: "executable"
        connectedSources: []
        onNewData: {
            var exitCode = data["exit code"];
            var exitStatus = data["exit status"];
            var stdout = data["stdout"];
            var stderr = data["stderr"];
            exited(exitCode, exitStatus, stdout, stderr);
            disconnectSource(sourceName);
        }
    }

    Plasmoid.fullRepresentation: Item {
        id: mainrepresentation

        Layout.minimumWidth: 300
        state: "bookmarkview"
        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Escape:
                plasmoid.expanded = false;
                break;
            default:
            }
        }
        onActiveFocusChanged: {
            bookmarkview.focus = true;
        }
        Component.onCompleted: {
            mainrepresentation.state = "bookmarkview";
        }
        states: [
            State {
                name: "bookmarkview"

                PropertyChanges {
                    target: bookmarkview
                    visible: true
                    focus: true
                }

            }
        ]

        Bookmarkview {
            id: bookmarkview

            itemheight: 32
        }

    }

}
