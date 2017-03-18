import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import org.kde.plasma.components 2.0 as PlasmaComponents

PlasmaComponents.Label {
//     text: "Hello world in Plasma 5 ";
    ColumnLayout{
        spacing: 2        
        Button{
            id: mainbutton
            Layout.alignment: Qt.AlignBottom
            Layout.preferredWidth: 80
            Layout.preferredHeight: 20
            iconName: "bookmarks"
            text: "start"
            onClicked: mainlistview.focusChanged(false)
        }
        Item{
            id: mainitem
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: 80
            Layout.preferredHeight: 20
            state: "normal"
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
                width: 100
                height: 400
                spacing: 10
                model: ContactModel {}
                delegate: Text {
                    Button{
                        iconName: icon
                        width: mainlistview.width
                        text: name + ": " + href
                    }
                }
                visible: true
                
            }
        }
        Connections{
            target:mainbutton
            onClicked:{
//                 mainitem.state="hided"
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
        
//     Rectangle{
//         id: mainbutton
//         width: 30
//         height: 30
//         color: "#00B000"
//         
//         
//     }
//     
    
}
