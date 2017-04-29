import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.XmlListModel 2.0
// import org.kde.plasma.plasmoid 2.0 //needed to give the Plasmoid attached properties
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import MyPlugins 1.0



PlasmaComponents.Dialog {
	id : plasmoid
	MyPlugins.bookmarkmodel{
		id: model 
	}

	
	

}
