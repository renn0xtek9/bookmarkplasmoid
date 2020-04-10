import org.kde.plasma.components 2.0 as PlasmaComponents
import QtQuick.Layouts 1.3
RowLayout{
            id: head
            property searcfocus searcfield: activeFocus
            height:itemheight
            width:bookmarklist.width
            PlasmaComponents.ToolButton{
                id: buttonorganize
                iconName:"bookmarks-organize.png"
                text:i18n("Edit")
                tooltip: i18n("Organize KDE Bookmarks")
                width:parent.width/3
                //width: 50
                // 				Layout.fillWidth: true
                Layout.fillHeight: true
                //anchors{
//                    left:parent.left
//                }
                onClicked:{
                    executable.exec("keditbookmarks "+itemmodel.konquerorBookmarks)
                }
            }
            PlasmaComponents.TextField{
                id: searchfield
                width:parent.width/3
                clearButtonShown:true
//                 Layout.fillWidth:true
                Layout.fillHeight:true
                onTextChanged:{
                    itemmodel.setSearchField(text)
                }
            }
            PlasmaComponents.ToolButton{
                id: buttonrefresh
                width:parent.width/3
//                 width: 30
//                anchors{
//                    right:parent.right
//                }
                iconName:"view-refresh"
                text:i18n("Refresh")
                tooltip: i18n("Re-read sources")
// 				Layout.fillHeight: true
//                 Layout.fillWidth: true
                onClicked:{
                    itemmodel.ReadAllSources(true);
                }
            }
}
