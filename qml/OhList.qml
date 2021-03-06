import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0


import Oh 1.0

ColumnLayout {
    Text {
        text: "Order history"
        font.pixelSize: 20
    }
    Pane {
        Material.elevation: 10
        Material.background: "White"
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

            model: OhModel {
                list: ohList
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
}
