import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.XmlListModel 2.0
// import QtQuick.Controls 2.1
import org.kde.plasma.components 2.0 as PlasmaComponents



PlasmaComponents.Button {
     id: mainbutton
     anchors.bottom: parent.bottom
     anchors.horizontalCenter: parent.horizontalCenter
//             anchors.horizontalCenter: rectangleLayout.horizontalCenter
     Layout.alignment: Qt.AlignTop
     Layout.preferredWidth: 80
     Layout.preferredHeight: 20
     iconName: "bookmarks"
     text: "start"
     activeFocusOnPress: true
     onClicked: mainlistview.focusChanged(false)
    XmlListModel {
	id: xmlModel
	source: "/home/max/.local/share/konqueror/bookmarks.xml"
	query: "/xbel/(bookmark|folder)"
	XmlRole { name: "name"; query: "title/string()" }
	XmlRole { name: "icon"; query: "info/metadata//*[name()='bookmark:icon']@name/string()" }
	XmlRole { name: "href"; query: "@href/string()"}
    }
    Component {
        id: highlightBar
        Rectangle {
            width: mainlistview.width; height: 30
            color: "#FFFF88"
            y: mainlistview.currentItem.y;
            Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
        }
    }
    ColumnLayout{
        spacing: 2 
        Item{
            id: mainitem
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: 80
            Layout.preferredHeight: 20
            state: "hided"
            states: [
                State {
                    name: "normal"
                    PropertyChanges {
                        target: mainlistview;visible:true}
                },
                State {
                    name: "hided"
                    PropertyChanges {
                        target: mainlistview;visible:false}
                }
            ]
            ListView{
                id: mainlistview
                width: 300
                height: 1000
                spacing: 10
//                 model: ContactModel{} 
                model:  xmlModel
                currentIndex: 4
                focus:true
                delegate: PlasmaComponents.Button {
			onClicked: console.log("clicked",name)
                        //                         iconName: icon
                        width: mainlistview.width
                        height: 30
                        text: name + ": " + href
                        tooltip: href
                       /* state: "nothighlighted"
                        states: [
                        State{
                            name: "nothighlighted"
//                                     color: "stellblue"
                        },
                        State{
                            name: "highlighted"
//                             color: "red"
                        }                */                                   
//                         ]
                        
                    
                }
                visible: true
                highlight: highlightBar
                highlightFollowsCurrentItem: false
            }
        }
        Connections{
            target:mainbutton
            onClicked:{
                if (mainitem.state=="normal"){
                    mainitem.state="hided"
                }
                else
                {
                    mainitem.state="normal"
                }
            }
        }
        
    }




    
}
