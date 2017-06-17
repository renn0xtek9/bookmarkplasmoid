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
	ColumnLayout{
		anchors.fill:parent
		PlasmaComponent.Label{
			text:"okular bookmarks"
			color:syspal.text
		}
		PlasmaComponent.TextField{
			id:okularpathfield
			width:parent.width
			text:"okular bookmarks"
			clearButtonShown:true
			anchors{
				left:parent.left 
				right:parent.right
			}
		}
		PlasmaComponent.Label{
			text:"KDE bookmarks"
			color:syspal.text
		}
		PlasmaComponent.TextField{
			id:kde
			width:parent.width
			text:"kde bookmarks"
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
