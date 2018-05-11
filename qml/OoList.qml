import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import Oo 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true

        ListView {
            implicitWidth: 250
            implicitHeight: 250
            anchors.fill: parent
            clip: true

            model: OoModel {
                list: ooList
            }
            RowLayout {
                width: parent.width

                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked
                }
                TextField {
                    text: model.description
                    onEditingFinished: model.description = text
                    Layout.fillWidth: true
                }
            }

            delegate: RowLayout {
                width: parent.width

                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked
                }
                TextField {
                    text: model.description
                    onEditingFinished: model.description = text
                    Layout.fillWidth: true
                }
            }
        }
    }

    RowLayout {
        Button {
            text: qsTr("Add")
            onClicked: ooList.appendItem()
            Layout.fillWidth: true
        }
        Button {
            text: qsTr("Remove")
            onClicked: ooList.removeCompletedItems()
            Layout.fillWidth: true
        }
    }
}
