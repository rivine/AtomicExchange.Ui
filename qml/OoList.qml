import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import Oo 1.0

ColumnLayout {
    Text {
        text: "Open orders"
        font.pixelSize: 24
        font.bold: true
    }
    Frame {
        Layout.fillWidth: true
        /*test*/
          property Item listHeaderItem: null
        Component {
            
            id: listHeaderComponent
            Item {
                width: parent.width; height: 20
                RowLayout {
                    width: parent.width
                    Text { 
                        text: '<b>Coin</b>' 
                    }
                    Text { text: '<b>Placed</b>'}
                    Text { text: '<b>Amount</b>' }
                    Text { text: '<b>Buy/Sell</b>'}
                    Text { text: '<b>Price</b>' }
                    Text { text: '<b>Status</b>'}
                }
            }
        }
        /*end of test */
        ListView {
            implicitWidth: 800
            implicitHeight: 250
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
                }
                Text {
                    text: model.placed
                }
                Text {
                    text: model.amount
                }
                Text {
                    text: model.buySell
                }
                Text {
                    text: model.price
                }
                Text {
                    text: model.status
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
            text: qsTr("Buy / Sell")
            onClicked: ooList.newOrder()
            Layout.fillWidth: true
        }
    }
}
