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
    
    
    ColumnLayout {
       
            Text {
                color : "#2b2b2b"
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
            RowLayout {
                id: step1Box
                objectName: "step1Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step1CheckBox
                    objectName: "step1CheckBox"
                    checked: false
                    enabled: false
                }

            }
            RowLayout {
                id: step2Box
                objectName: "step2Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step2CheckBox
                    objectName: "step2CheckBox"
                    checked: false
                    enabled: false;
                }
            }
        }
        RowLayout {
            RowLayout {
                id: step3Box
                objectName: "step3Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step3CheckBox
                    objectName: "step3CheckBox"
                    checked: false
                    enabled: false;
                }

            }
            RowLayout {
                id: step4Box
                objectName: "step4Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step4CheckBox
                    objectName: "step4CheckBox"
                    checked: false
                    enabled: false;
                }
            }
        }
        RowLayout {
            RowLayout {
                id: step5Box
                objectName: "step5Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step5CheckBox
                    objectName: "step5CheckBox"
                    checked: false
                    enabled: false;
                }
            }
            RowLayout {
                id: step6Box
                objectName: "step6Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step6CheckBox
                    objectName: "step6CheckBox"
                    checked: false
                    enabled: false;
                }
            }
        }
        RowLayout {
            RowLayout {
                id: step7Box
                objectName: "step7Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step7CheckBox
                    objectName: "step7CheckBox"
                    checked: false
                    enabled: false;
                }
            }
            RowLayout {
                id: step8Box
                objectName: "step8Box"
                Layout.leftMargin: 70
                Layout.preferredWidth: 250
                visible: false

                CheckBox {
                    id: step8CheckBox
                    objectName: "step8CheckBox"
                    checked: false
                    enabled: false;
                }
            }
        }
        RowLayout {
            id: step9Box
            objectName: "step9Box"
            Layout.leftMargin: 70
            Layout.preferredWidth: 250
            visible: false

            CheckBox {
                id: step9CheckBox
                objectName: "step9CheckBox"
                checked: false
                enabled: false;
            }
        }
        RowLayout {
            id: outputLog
            objectName: "ouputLog"
            Layout.leftMargin: 70
            width: parent.width
            property bool textVisible: false;


            Button {
                font.bold: true
                Material.background: Material.LightBlue
                Material.foreground: "white"
                id: outputLogButton
                objectName: "ouputLogButton"
                text: "Show log"
                onClicked: {
                    parent.textVisible = !parent.textVisible
                    ooList.showOutputLog();
                }
            }
            Text {
                id: outputLogText
                objectName: "outputLogText"
                Layout.preferredWidth: 100
                visible: parent.textVisible
            }

        }

         
    }

    
}
