import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0


ColumnLayout {
    //Layout.fillWidth: true
    
    Item {
        width: 300
        height: 150

         Image {
             id: bug
             source: "https://itsyou.online/assets/img/its-you-online.gif"
             sourceSize: Qt.size(parent.width, parent.height)
             smooth: true
             visible: false
         }

        ColorOverlay {
            anchors.fill: bug
            source: bug
            color: "black"
        }
    }
    Pane {
        Layout.preferredWidth: 350
        Material.elevation: 6
        Material.background: "White"
        //Layout.fillWidth: true
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
                    objectName: "usernameInput"
                    Layout.fillWidth: true
                    Layout.preferredWidth: 200
                }
            }
          
            RowLayout {
                width: parent.width
                Label {
                    text: "Password"
                    Layout.preferredWidth: 100
                }
                TextField {
                    echoMode: TextInput.Password
                    id: password
                    objectName: "passwordInput"
                    Layout.fillWidth: true
                }
            }
            
            RowLayout {
                Text {
                    id: loginNote
                    objectName: "loginNote"
                    Layout.fillWidth: true
                    color : "red"
                    text: "Username / password is not correct."
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
                    onClicked: {
                        loginService.startLoginProcess(username.text, password.text)
                    }
                    Layout.fillWidth: true
                }
            }
            RowLayout{
                Text{    
                    text: "<a href='http://itsyou.online'>Create account</a>"
                    onLinkActivated: Qt.openUrlExternally(link)
                }
            }
        }
    }    
}
