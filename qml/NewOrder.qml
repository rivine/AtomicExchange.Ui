import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import ToDo 1.0

ColumnLayout {
    Text {
        text: "New order"
        font.pixelSize: 20
        font.bold: true
    }
    Frame {

        Layout.fillWidth: true
        ColumnLayout{
            RowLayout {
                width: parent.width

                Label {
                    text: "Amount"
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
                        model: [ "TFT", "BTC", "Ripple" ]
                }

            }
            RowLayout {
                width: parent.width

                Label {
                    text: "Source Wallet"
                }
                Text {
                    text: "f1Zfeea2Ee631ZeF"
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                }
                Label {
                    text: "(Please deposit the amount here)"
                }

            }
            RowLayout {
                width: parent.width

                Label {
                    text: "Value"
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
                        model: [ "TFT", "BTC", "Ripple" ]
                }
            }
            RowLayout {
                width: parent.width

                Label {
                    text: "Destination Wallet"
                }
                TextField {
                    //text: model.description
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                }

            }
        }
    }

    RowLayout {
        Button {
            text: qsTr("Cancel")
            onClicked: ooList.cancelNewOrder()
            Layout.fillWidth: true
        }
        Button {
            text: qsTr("Confirm")
            onClicked: ooList.confirmNewOrder()
            Layout.fillWidth: true
        }
    }
}
