import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800
    title: qsTr("Atomic exchange")
    
    ColumnLayout {
            Text {
                Layout.leftMargin: 50
                Layout.topMargin: 20
                Layout.bottomMargin: 20
                text: "Atomic exchange"
                font.pixelSize: 24
                font.bold: true
            }/*
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
*/

            NewOrder {
                Layout.leftMargin: 70
                Layout.bottomMargin: 20
                objectName: "newOrder"
                visible: true;
            }
    }
}
