import QtQuick 2.0
import QtQuick.Controls 1.0 as QtControls
import org.kde.plasma.configuration 2.0
import QtQuick.Layouts 1.0 as Layouts
Rectangle {
	id: root
	color: syspal.window
	width: units.gridUnit * 40
	height: units.gridUnit * 30
	Layouts.GridLayout {
		columns: 2
		QtControls.Label {
			text: i18n("Display Text:")
			Layouts.Layout.alignment: Qt.AlignVCenter|Qt.AlignRight
		}
		QtControls.Label {
			text: i18n("Putain de merde:")
			Layouts.Layout.alignment: Qt.AlignVCenter|Qt.AlignRight
		}
	}
}
