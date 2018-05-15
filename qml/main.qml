import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 1024
    height: 800
    title: qsTr("Jimber Atomic Swap")

    ColumnLayout {
        
        ToDoList {
            //anchors.centerIn: parent
            visible: false;
        }
        OoList {
            //anchors.centerIn: parent
            objectName: "openOrder"
        }
        NewOrder {
            objectName: "newOrder"
            visible: false;
            //anchors.centerIn: parent
        }
    }

}
