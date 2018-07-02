import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtQuick.Shapes 1.11
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1440
    height: 900
    title: qsTr("Atomic exchange")
    readonly property int maxWidthPhone: 479
    readonly property int maxWidthTablet: 767
    
    
    onActiveChanged: {
        loginService.signOut()
    }

    header: 
        ToolBar {
            Material.elevation: 10
            Material.primary: Material.Blue
            Layout.leftMargin: 70
            Layout.topMargin: 20
            states: [
                State {
                    when: window.width <= maxWidthPhone
                    PropertyChanges { target: userNameHeader; visible: false }

                },
                State {
                    when: window.width > maxWidthPhone && window.width <= maxWidthTablet
                    PropertyChanges { target: userNameHeader; visible: true }
                },
                State {
                    when: window.width > maxWidthTablet
                    PropertyChanges { target: userNameHeader; visible: true }
                }
            ]

            RowLayout {
                anchors.fill: parent
                Layout.topMargin: 20

                Text {
                    Layout.leftMargin: 70
                    Layout.topMargin: 20

                    Layout.bottomMargin: 20
                    text: "Atomic Exchange"
                    font.pixelSize: 24
                    color: "white"
                }
                Text {
                    id: userNameHeader
                    objectName: "userNameHeader"
                    visible: false
                    anchors.right: parent.right
                    anchors.rightMargin: 60
                    font.pixelSize: 16
                    color: "white"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: menu.open()
                    }
                    
                }  
                
                Image {
                    id: userImage
                    objectName: "userImage"
                    visible: false
                    width: 35; height: 35
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    source: "../img/user.png"
                    sourceSize: Qt.size(35, 35)

                    MouseArea {
                        anchors.fill: parent
                        onClicked: menu.open()
                    }

                    Menu {
                        id: menu
                        y: userImage.height
                        MenuItem{
                            text: 'Show log'
                            onClicked: {
                                footerPane.outputLogTextVisible = !footerPane.outputLogTextVisible
                                //newOrderService.showOutputLog();
                            }
                        }
                        MenuItem{
                            text: 'Sign out'
                            onClicked: {
                                loginService.signOut()
                            }
                        }
                        Timer {
                            id: outputLogTimer
                            interval: 3000; running: footerPane.outputLogTextVisible; repeat: true
                            onTriggered: newOrderService.showOutputLog();
                        }
                    }
                }
            }      
    }
    ScrollView {
        id: scrollviewLogin
        objectName: "scrollViewLogin"
        anchors.fill: parent
        clip: true
        visible: true

        states: [
            State {
                when: window.width <= maxWidthPhone
                PropertyChanges { target: loginColumnLayout; width: 300 }
                //PropertyChanges { target: loginBox; Layout.leftMargin: 10 }
                PropertyChanges { target: loginColumnLayout; width: window.width - 10 }
                
            },
            State {
                when: window.width > maxWidthPhone && window.width <= maxWidthTablet
                //PropertyChanges { target: loginBox; Layout.leftMargin: 10 }
                PropertyChanges { target: loginColumnLayout; width: window.width - 10 }
            },
            State {
                when: window.width > maxWidthTablet
                //PropertyChanges { target: newOrder; anchors.centerIn: parent }
                //PropertyChanges { target: newOrder; anchors.horizontalCenter: parent.horizontalCenter }
            }
        ]

        ColumnLayout {
            id: loginColumnLayout
            objectName: "loginColumnLayout"
            width: window.width

            Login { 
                Layout.leftMargin: window.width / 2 - 175
                id: loginBox
                objectName: "login"
                visible: true;
            }
            Text {
                Layout.leftMargin: window.width / 2 - 175
                id: getCommitVersion
                objectName: "getCommitVersion"
                text: newOrderService.getCommitVersion()
                color: "#d3d3d3"
            }
        }
    }
   
    ScrollView {
        id: scrollView
        objectName: "scrollView"
        anchors.fill: parent
        clip: true
        visible: false
        //anchors.top: parent.top

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
        ColumnLayout {
            id: masterColumnLayout
            objectName: "masterColumnLayout"
            width: window.width

            NewOrder {
                Layout.topMargin: 20
                Layout.leftMargin: window.width / 2 - 334
                //Layout.preferredWidth: 750
                //Layout.leftMargin: 70
                id: newOrder
                objectName: "newOrder"
                visible: true
            }
            RowLayout {
                Layout.topMargin: 20
                Layout.leftMargin: window.width / 2 - 175
                
                ProgressBar {
                    id: progressBar
                    objectName: "progressBar"
                    visible: false
                    anchors.centerIn: parent
                    value: 0
                    height: 20
                    clip: true
                    background: Rectangle {
                        implicitWidth: 350
                        implicitHeight: 6
                        border.color: "#999999"
                        radius: 5
                    }
                    contentItem: Item {
                        implicitWidth: 200
                        implicitHeight: 4

                        Rectangle {
                            id: bar
                            width: progressBar.visualPosition * parent.width
                            height: parent.height
                            radius: 5
                        }

                        LinearGradient {
                            anchors.fill: bar
                            start: Qt.point(0, 0)
                            end: Qt.point(bar.width, 0)
                            source: bar
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: "#17a81a" }
                                GradientStop { id: grad; position: 0.5; color: Qt.lighter("#17a81a", 2) }
                                GradientStop { position: 1.0; color: "#17a81a" }
                            }

                        }
                        LinearGradient {
                            anchors.fill: bar
                            start: Qt.point(0, 0)
                            end: Qt.point(0, bar.height)
                            source: bar
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: Qt.rgba(0,0,0,0) }
                                GradientStop { position: 0.5; color: Qt.rgba(1,1,1,0.3) }
                                GradientStop { position: 1.0; color: Qt.rgba(0,0,0,0.05) }
                            }
                        }
                    }
                }

            }
            RowLayout {
                width: newOrder.width
                Layout.topMargin: 20
                Layout.leftMargin: window.width / 2 - 335
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
            }
            

            RowLayout {
                width: newOrder.width
                Layout.topMargin: 20
                Layout.leftMargin: window.width / 2 - 335

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
                width: newOrder.width
                Layout.topMargin: 20
                Layout.leftMargin: window.width / 2 - 335
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
                        enabled: false
                    }

                }
            }
            RowLayout {
                width: newOrder.width
                Layout.topMargin: 20
                Layout.leftMargin: window.width / 2 - 335
                RowLayout {
                    id: step4Box
                    objectName: "step4Box"
                    Layout.leftMargin: 70
                    Layout.preferredWidth: 250
                    visible: false

                    CheckBox {
                        id: step4CheckBox
                        objectName: "step4CheckBox"
                        text: "Balance updated"
                        checked: false
                        enabled: false
                    }
                }
            }  
            RowLayout {
                width: newOrder.width
                Layout.topMargin: 20
                Layout.leftMargin: window.width / 2 - 335
                RowLayout {
                    id: step5Box
                    objectName: "step5Box"
                    Layout.leftMargin: 70
                    Layout.preferredWidth: 250
                    visible: false

                    CheckBox {
                        id: step5CheckBox
                        objectName: "step5CheckBox"
                        text: "Refund"
                        checked: false
                        enabled: false
                    }

                }
             }           
        }
    }  
    footer: Pane {
        id: footerPane
        objectName: "footerPane"
        property bool outputLogTextVisible: false;
        height: 250
        Material.elevation: 6
        visible: outputLogTextVisible
        
        ScrollView {        
            anchors.horizontalCenter: parent.horizontalCenter            
            id: scrollViewLog        
            objectName: "scrollViewLog"
            width: window.height - 40  
            height: 250
            clip: true       
        
            TextEdit {     
                Layout.topMargin: 50
                width: window.height - 40          
                id: outputLogText
                wrapMode: Text.Wrap
                objectName: "outputLogText"     
                selectByMouse: true   
                readOnly: true    
            }             
        }        
    }        
}
