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
        objectName: "startLoginPane"
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
                    id: usernameInputId
                    objectName: "usernameInput"
                    Layout.fillWidth: true
                    Layout.preferredWidth: 200
                    text: loginService.username
                }
                Binding {
                    target: loginService
                    property: "username"
                    value: usernameInputId.text
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
                    id: passwordInputId
                    objectName: "passwordInput"
                    Layout.fillWidth: true
                    text: loginService.password
                }
                Binding {
                    target: loginService
                    property: "password"
                    value: passwordInputId.text
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
                        loginService.startLoginProcess()
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
    Pane {
        Layout.preferredWidth: 350
        Material.elevation: 6
        Material.background: "White"
        //Layout.fillWidth: true
        Material.accent: Material.Green
        objectName: "selectAuthenticatorPane"
        visible: false
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
                visible: true

                Label {
                    text: "Authenticator method"
                    Layout.preferredWidth: 100
                }
                ComboBox {
                        objectName: "authenticatorMethod"
                        width: 200
                        model: ["Authenticator application","SMS"]
                        enabled: true;
                }
            }
            RowLayout {
                Button {
                    Material.background: Material.LightBlue
                    Material.foreground: "white"
                    font.bold: true
                    id: nextButton
                    font.capitalization: Font.MixedCase
                    objectName: "nextButton"
                    text: qsTr("Next")
                    onClicked: {
                        loginService.selectAuthenticator()
                    }
                    Layout.fillWidth: true
                }
            }
        }
    }     
    Pane {
        Layout.preferredWidth: 350
        Material.elevation: 6
        Material.background: "White"
        //Layout.fillWidth: true
        Material.accent: Material.Green
        objectName: "enterCodePane"
        visible: false
        ColumnLayout{
            
            RowLayout{
                Text {
                    color : "#2b2b2b"
                    text: "Authentication method"
                    font.pixelSize: 20
                    font.bold: true
                }
            }          
          
            RowLayout {
                width: parent.width
                visible: true

                Label {
                    text: "Authenticator method"
                    Layout.preferredWidth: 100
                }
                ComboBox {
                        objectName: "authenticatorMethod"
                        width: 200
                        model: ["Authenticator application","SMS"]
                        enabled: true;
                }
            }
            RowLayout {
                Button {
                    Material.background: Material.LightBlue
                    Material.foreground: "white"
                    font.bold: true
                    id: nextButton
                    font.capitalization: Font.MixedCase
                    objectName: "nextButton"
                    text: qsTr("Next")
                    onClicked: {
                        loginService.selectAuthenticator()
                    }
                    Layout.fillWidth: true
                }
            }
        }
    }     
    Pane {
        Layout.preferredWidth: 350
        Material.elevation: 6
        Material.background: "White"
        //Layout.fillWidth: true
        Material.accent: Material.Green
        objectName: "AuthenticatorAppPane"
        visible: false
        ColumnLayout{
            
            RowLayout{
                Text {
                    color : "#2b2b2b"
                    text: "Fill in the 6 digit code from the authenticator application on your phone."
                    font.pixelSize: 20
                    font.bold: true
                }
            }          
                              
            RowLayout {
                width: parent.width
                visible: true

                Label {
                    text: "Authenticator method"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: authenticatorAppCodeId
                    objectName: "authenticatorAppCode"
                    Layout.fillWidth: true
                    Layout.preferredWidth: 200
                    text: loginService.authenticatorAppCode
                    validator: RegExpValidator { regExp: /\b\d{6}\b/ }
                }
                Binding {
                    target: loginService
                    property: "authenticatorAppCode"
                    value: authenticatorAppCodeId.text
                }
            }
            RowLayout {
                Button {
                    Material.background: Material.LightBlue
                    Material.foreground: "white"
                    font.bold: true
                    id: nextButton
                    font.capitalization: Font.MixedCase
                    objectName: "nextButton"
                    text: qsTr("Next")
                    onClicked: {
                        loginService.loginPotp()
                    }
                    Layout.fillWidth: true
                }
            }
        }
    }         
}
