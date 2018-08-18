import QtQuick 2.0
import QtQuick.Controls 1.0 as QtControls
import org.kde.plasma.configuration 2.0
// import QtQuick.Layouts 1.0 as Layouts
import org.kde.plasma.components 2.0 as PlasmaComponent
import QtQuick.Layouts 1.3
Rectangle {
	id: root
	color: syspal.window
// 	width: units.gridUnit * 40
// 	height: units.gridUnit * 30
	anchors.fill:parent
	
	property alias cfg_konquerorpath :konquerorpath.text
	property alias cfg_okularpath: okularpath.text
	property alias cfg_chromepath: chromepath.text
	
	ColumnLayout{
		anchors.fill:parent
		PlasmaComponent.Label{
			text:i18n("okular bookmarks")
			color:syspal.text
		}
		PlasmaComponent.TextField{
			id:okularpath
			width:parent.width
			text:plasmoid.configuration.okularpath
			clearButtonShown:true
			anchors{
				left:parent.left 
				right:parent.right
			}
		}
		PlasmaComponent.Label{
			text:i18n("KDE bookmarks")
			color:syspal.text
		}
		PlasmaComponent.TextField{
			id:konquerorpath
			width:parent.width
			text:plasmoid.configuration.konquerorpath
			clearButtonShown:true
			anchors{
				left:parent.left 
				right:parent.right
			}
		}
		PlasmaComponent.Label{
			text:i18n("Google Chrome bookmarks")
			color:syspal.text
		}
		PlasmaComponent.TextField{
			id:chromepath
			width:parent.width
			text:plasmoid.configuration.chromepath
			clearButtonShown:true
			anchors{
				left:parent.left 
				right:parent.right
			}
		}
		Item{
			id: space
			Layout.fillHeight:true
			Layout.fillWidth:true
		}
	}
}
