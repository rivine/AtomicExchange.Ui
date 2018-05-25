import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import Oo 1.0

ColumnLayout {
    Text {
        text: "Open orders"
        font.pixelSize: 20
    }
    Frame {

        /*test*/
        
        Component {
            
            id: listHeaderComponent
            Item {
                width: parent.width; height: 20
                RowLayout {
                    width: parent.width
                    Text { 
                        text: '<b>Coin</b>' 
                        Layout.preferredWidth: 75
                    }
                    Text { text: '<b>Placed</b>'
                        Layout.preferredWidth: 75
                    }
                    Text { text: '<b>Amount</b>' 
                        Layout.preferredWidth: 75
                    }
                    Text { text: '<b>Price</b>' 
                        Layout.preferredWidth: 75
                    }
                    Text { text: '<b>Status</b>'
                        Layout.preferredWidth: 75
                    }
                }
            }
        }
        /*end of test */
        ListView {
            implicitWidth: 800
            implicitHeight: 150
            anchors.fill: parent
            clip: true
            header: listHeaderComponent

            model: OoModel {
                list: ooList
            }
            delegate: RowLayout {
                width: parent.width

                Text {
                    text: model.coin
                    Layout.preferredWidth: 75
                }
                Text {
                    text: model.placed
                    Layout.preferredWidth: 75
                }
                Text {
                    text: model.amount
                    Layout.preferredWidth: 75
                }
                Text {
                    text: model.price
                    Layout.preferredWidth: 75
                }
                Text {
                    text: model.status
                    Layout.preferredWidth: 75
                }
                //TextField {
                //    text: model.description
                //    onEditingFinished: model.description = text
                //    Layout.fillWidth: true
                //}
            }
        }
    }

    RowLayout {
        Button {
            Material.background: Material.LightBlue
            Material.foreground: "white"
            font.bold: true
            text: qsTr("New order")
            onClicked: ooList.newOrder()
            Layout.fillWidth: true
        }
    }
}
