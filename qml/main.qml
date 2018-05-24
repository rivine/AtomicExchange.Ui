import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800
    title: qsTr("Atomic exchange - New order")
    Material.theme: Material.Light

    ColumnLayout {
            

            Text {
                Layout.leftMargin: 50
                Layout.topMargin: 20
                Layout.bottomMargin: 20
                text: "Atomic Exchange - New order"
                font.pixelSize: 24

            }
            OoList {
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
                Layout.leftMargin: 70
                Layout.bottomMargin: 20
                objectName: "newOrder"
                visible: false;
            }
    }
}
