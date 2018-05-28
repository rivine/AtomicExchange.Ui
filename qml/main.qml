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

         RowLayout {
            Layout.leftMargin: 70
            Layout.bottomMargin: 20
            width: parent.width
            visible: false;

            Label {
                text: "Output :"
                Layout.preferredWidth: 100
            }
            Text {
                id: outputMessages
                objectName: "outputMessages"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            Layout.leftMargin: 70
            Layout.bottomMargin: 20
            width: parent.width
            

            ProgressBar {
                width: parent.width
                id: progressBar
                objectName: "progressBar"
                value: 0
                visible: false
            }

        }
        RowLayout {
            id: step1Box
            objectName: "step1box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step1CheckBox
                objectName: "step1CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step1ExtraInfo
                objectName: "step1ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step2Box
            objectName: "step2box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step2CheckBox
                objectName: "step2CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step2ExtraInfo
                objectName: "step2ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step3Box
            objectName: "step3box"
            Layout.leftMargin: 70
            width: parent.width
             visible: false

            CheckBox {
                id: step3CheckBox
                objectName: "step3CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step3ExtraInfo
                objectName: "step3ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step4Box
            objectName: "step4box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step4CheckBox
                objectName: "step4CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step4ExtraInfo
                objectName: "step4ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step5Box
            objectName: "step5box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step5CheckBox
                objectName: "step5CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step5ExtraInfo
                objectName: "step5ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step6Box
            objectName: "step6box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step6CheckBox
                objectName: "step6CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step6ExtraInfo
                objectName: "step6ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step7Box
            objectName: "step7box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step7CheckBox
                objectName: "step7CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step7ExtraInfo
                objectName: "step7ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step8Box
            objectName: "step8box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step8CheckBox
                objectName: "step8CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step8ExtraInfo
                objectName: "step8ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
        RowLayout {
            id: step9Box
            objectName: "step9box"
            Layout.leftMargin: 70
            width: parent.width
            visible: false

            CheckBox {
                id: step9CheckBox
                objectName: "step9CheckBox"
                checked: false
                enabled: false;
            }
            Text {
                id: step9ExtraInfo
                objectName: "step9ExtraInfo"
                Layout.preferredWidth: 100
            }
        }
    }
}
