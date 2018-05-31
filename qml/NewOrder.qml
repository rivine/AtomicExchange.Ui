import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import ToDo 1.0

ColumnLayout {
    Layout.fillWidth: true
    Text {
        color : "#2b2b2b"
        text: "New order"
        font.pixelSize: 20
        font.bold: true
    }
    Pane {

        Material.elevation: 10
        Material.background: "White"
        Layout.fillWidth: true
        Material.accent: Material.Green
    
        ColumnLayout{
            RowLayout {
                Label {
                    text: "Role"
                    Layout.preferredWidth: 100
                }
                ComboBox {
                        id: role
                        objectName: "role"
                        width: 200
                        model: [ "Initiator", "Acceptor" ]

                        onActivated: ooList.initiatorAcceptorActivated(editText)
                        
                }
                Text {
                    color : "#2b2b2b"
                    text: ooList.getIp();
                }

            }
            RowLayout {
                width: parent.width
                   id: ipAcceptorBox
                    objectName: "ipAcceptorBox"
                    visible: true

                Label {
                    text: "Ip acceptor"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: ipAcceptor
                    objectName: "ipAcceptor"
                    Layout.fillWidth: true
                    validator: RegExpValidator { regExp: /\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b/ }
                }
                Text {
                    id: ipNote
                    objectName: "ipNote"
                    //text: model.description
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                    color : "red"
                    text: "Please enter a IP"
                    visible: false;
                }
            }
            RowLayout {
                width: parent.width

                Label {
                    text: "Amount"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: amount
                    objectName: "amount"
                    //text: model.description
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhFormattedNumbersOnly

                    validator: RegExpValidator { regExp: /\d{1,9}(?:,\d{1,9})+$/ }
                }
                ComboBox {
                        id: coin
                        objectName: "coin"
                        width: 200
                        model: [  "BTC", "TFT"]
                        enabled: false;
                }
                Text {
                    id: amountNote
                    objectName: "amountNote"
                    //text: model.description
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                    color : "red"
                    text: "Please enter a valid amount"
                    visible: false;
                }

            }
            RowLayout {
                width: parent.width

                Label {
                    text: "Value"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: value
                    objectName: "value"
                    Layout.fillWidth: true
                    validator: RegExpValidator { regExp: /\d{1,9}(?:,\d{1,9})+$/ }
                }
                ComboBox {
                        id: destinationCoin
                        objectName: "destinationCoin"
                        width: 200
                        model: [ "TFT", "BTC"]
                        enabled: false;
                }
                Text {
                    id: valueNote
                    objectName: "valueNote"
                    //text: model.description
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                    color : "red"
                    text: "Please enter a valid value"
                    visible: false;
                }
            }
        }
    }

    RowLayout {
        Button {
            Material.background: Material.LightBlue
            Material.foreground: "white"
            font.bold: true
            id: submitButton
            objectName: "submitButton"
            text: qsTr("Confirm")
            onClicked: ooList.confirmNewOrder()
            Layout.fillWidth: true
        }
    }
}
