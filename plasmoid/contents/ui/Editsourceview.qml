import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import org.kde.plasma.extras 2.0 as PlasmaExtras
ColumnLayout{
	id:editsourceview
	spacing:2
	property alias viewHeight:editsourceview.height
	width:300
	height:300
	visible:false
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
	RowLayout {
		id: okcanclelbuttons
		height:30
		anchors{
			left:parent.left 
			right:parent.right
			bottom:parent.bottom
		}
		Button{
			id: okbutton
			iconName:"dialog-ok.png"
			text:qsTr("Ok")
			tooltip: qsTr("Validate changes")
			height: 24
			Layout.fillWidth: true
			onClicked:{
				itemmodel.konquerorBookmarks=konquerorselect.textfield
				itemmodel.okularBookmarks=okularselect.textfield
				itemmodel.firefoxBookmarks=firefoxselect.textfield
				itemmodel.chromeBookmarks=chromeselect.textfield
				plasmoid.configuration.firefoxpath=firefoxselect.textfield
				plasmoid.configuration.okularpath=okularselect.textfield
				plasmoid.configuration.konquerorpath=konquerorselect.textfield
				plasmoid.configuration.chromepath=chromeselect.textfield
				itemmodel.ReadAllSources()
				mainrepresentation.state="bookmarkview"
			}
		}
		Button{
			id: cancelbutton
			iconName:"dialog-cancel"
			text:qsTr("Cancel")
			tooltip: qsTr("Discard changes")
			height: 24
			Layout.fillWidth: true
			onClicked:{
				console.log("Changes Validated")
				mainrepresentation.state="bookmarkview"
			}
		}

	}
}
