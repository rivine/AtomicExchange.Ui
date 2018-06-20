import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: window
    visible: true
    width: 1440
    height: 900
    title: qsTr("Atomic exchange")
    readonly property int maxWidthPhone: 479
    readonly property int maxWidthTablet: 767
    
    
    onActiveChanged: {
        if(active){
            //console.log("woop")
            //masterColumnLayout.visible = false
        }
    }

    header: 
        ToolBar {
            Material.elevation: 10
            Material.primary: Material.Blue
            Layout.leftMargin: 70
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
    ScrollView {
        id: scrollviewLogin
        objectName: "scrollViewLogin"
        anchors.fill: parent

        clip: true
        visible: true
            ColumnLayout {
                Layout.leftMargin: 70
                Login {
                    Layout.topMargin: 40    
                    Layout.leftMargin: 70
                    id: login
                    objectName: "login"
                    visible: true;
                }
            }
    }
   
    ScrollView {
        id: scrollView
        objectName: "scrollView"
        anchors.fill: parent
        clip: true
        visible: false
        anchors.top: parent.top
        //anchors.horizontalCenter: parent.horizontalCenter
        

        states: [
            State {
                when: window.width <= maxWidthPhone
                PropertyChanges { target: masterColumnLayout; width: 300 }
                PropertyChanges { target: newOrder; Layout.leftMargin: 10 }
                PropertyChanges { target: masterColumnLayout; width: window.width - 10 }
                
            },
            State {
                when: window.width > maxWidthPhone && window.width <= maxWidthTablet
                PropertyChanges { target: newOrder; Layout.leftMargin: 10 }
                PropertyChanges { target: masterColumnLayout; width: window.width - 10 }
            },
            State {
                when: window.width > maxWidthTablet
                //PropertyChanges { target: newOrder; anchors.centerIn: parent }
                //PropertyChanges { target: newOrder; anchors.horizontalCenter: parent.horizontalCenter }
            }
        ]
        // ColumnLayout {
        //     visible: true
        //     id: loginColumnLayout
        //     objectName: "loginColumnLayout"
        //     Layout.leftMargin: 70

        //     Login {
        //         Layout.topMargin: 40    
        //         Layout.leftMargin: 70
        //         id: login
        //         objectName: "login"
        //         visible: true;
        //     }

        // }
        ColumnLayout {
            id: masterColumnLayout
            objectName: "masterColumnLayout"
            NewOrder {
                //anchors.top: parent.top + 40
                //Layout.preferredWidth: 750
                Layout.leftMargin: 70
                id: newOrder
                objectName: "newOrder"
                visible: true
            }
            RowLayout {
                Layout.leftMargin: 70
                Layout.topMargin: 10
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
                Layout.leftMargin: 40
                width: parent.width
                property bool textVisible: false;


                Button {
                    Layout.topMargin: 20
                    font.bold: true
                    Material.background: Material.LightBlue
                    Material.foreground: "white"
                    id: outputLogButton
                    font.capitalization: Font.MixedCase
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
}
