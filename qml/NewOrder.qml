import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import ToDo 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true
        ColumnLayout{
            RowLayout {
                width: parent.width

                Label {
                    text: "Amount"
                }
                TextInput {
                    id: inputBox
                    objectName: "InputBox"
                    //text: model.description
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhFormattedNumbersOnly

                    validator: RegExpValidator { regExp: /fruit basket/ }
                }
                ComboBox {
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
                    //text: model.description
                    //onEditingFinished: model.description = text
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                }
                ComboBox {
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
            onClicked: ooList.confirmNewOrder()
            Layout.fillWidth: true
        }
        Button {
            text: qsTr("Confirm")
            onClicked: ooList.cancelNewOrder()
            Layout.fillWidth: true
        }
    }
}
