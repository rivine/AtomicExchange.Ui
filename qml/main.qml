import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800
    title: qsTr("Atomic exchange")
    Material.theme: Material.Light

   header: 
        ToolBar {
            Material.elevation: 10
            Material.primary: Material.Blue
            Layout.leftMargin: 50
            Layout.topMargin: 20

            RowLayout {

                Layout.topMargin: 20

                Text {
                    Layout.leftMargin: 70
                    Layout.topMargin: 20

                    Layout.bottomMargin: 20
                    text: "Atomic Exchange"
                    font.pixelSize: 24
                    color: "white"
                }
            }        
    }

    ColumnLayout {          
            Layout.topMargin: 200

            OoList {
                Layout.topMargin: 40    
                //anchors.centerIn: parent
                Layout.leftMargin: 70
                Layout.bottomMargin: 20
                objectName: "openOrders"
                
            }
            OhList {
                //anchors.centerIn: parent
                Layout.leftMargin: 70
                Layout.bottomMargin: 20
                objectName: "orderHistory"
            }
            ToDoList {
                //anchors.centerIn: parent
                visible: false;
            }

            NewOrder {
                Layout.topMargin: 40    
                Layout.leftMargin: 70
                Layout.bottomMargin: 20
                objectName: "newOrder"
                visible: false;
            }
    }
}
