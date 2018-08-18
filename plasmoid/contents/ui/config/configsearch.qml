import QtQuick 2.0
import QtQuick.Controls 1.0 as QtControls
import org.kde.plasma.configuration 2.0
import org.kde.plasma.components 2.0 as PlasmaComponent
import QtQuick.Layouts 1.3
Rectangle{
	id: root
	anchors.fill:parent
	color:syspal.window
	ColumnLayout{
		anchors.fill:parent
		PlasmaComponent.CheckBoxStyle{
			id: searchflat
			text:i18n("Display search result as a flat collection")
			checked: true
			
		}		
		Item{
			id:space
			Layout.fillHeight:true
			Layout.fillWidth:true
		}		
	}
}
