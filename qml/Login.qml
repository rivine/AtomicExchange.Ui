import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import ToDo 1.0

ColumnLayout {
    Layout.fillWidth: true

    // states: [
    //     State {
    //         when: window.width <= maxWidthPhone
    //         //ParentChange { target: groupbBoxBTC; parent: columnLayoutCurrencies; }
    //         ParentChange { target: groupbBoxTFT; parent: columnLayoutCurrencies; }

            
    //     },
    //     State {
    //         when: window.width > maxWidthPhone && window.width <= maxWidthTablet
    //         //ParentChange { target: groupbBoxBTC; parent: rowLayoutGroupboxes; }
    //         ParentChange { target: groupbBoxTFT; parent: rowLayoutGroupboxes; }
    //     },
    //     State {
    //         when: window.width > maxWidthTablet
    //         ParentChange { target: groupbBoxBTC; parent: rowLayoutGroupboxes; }
    //         ParentChange { target: groupbBoxTFT; parent: rowLayoutGroupboxes; }
    //     }
        
    // ]


    Pane {

        Material.elevation: 6
        Material.background: "White"
        Layout.fillWidth: true
        Material.accent: Material.Green

        ColumnLayout{
            
            RowLayout{
                Text {
                    color : "#2b2b2b"
                    text: "Login"
                    font.pixelSize: 20
                    font.bold: true
                }
            }
          
          
            RowLayout {
                width: parent.width
                id: userNameBox
                objectName: "usernameBox"
                visible: true

                Label {
                    text: "Username"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: username
                    objectName: "username"
                    Layout.fillWidth: true

                }
            }
          
            RowLayout {
                width: parent.width

                Label {
                    text: "Password"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: password
                    objectName: "password"
                    Layout.fillWidth: true
                }
            }
            
            RowLayout {
                Text {
                    id: loginNote
                    objectName: "loginNote"
                    Layout.fillWidth: true
                    color : "red"
                    text: "Username / password combination is not correct."
                    visible: false;
                }
            }


            RowLayout {
                Button {
                    Material.background: Material.LightBlue
                    Material.foreground: "white"
                    font.bold: true
                    id: loginButton
                    font.capitalization: Font.MixedCase
                    objectName: "loginButton"
                    text: qsTr("Log in")
                    onClicked: ooList.login(username.text, password.text)
                    Layout.fillWidth: true
                }
            }
        }
    }

    
}
