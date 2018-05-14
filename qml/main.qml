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
        }
        OoList {
            //anchors.centerIn: parent
        }
        NewOrder {
            //anchors.centerIn: parent
        }
    }

}
