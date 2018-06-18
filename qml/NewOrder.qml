import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

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
            id: columnLayoutCurrencies
            RowLayout{
                Text {
                    color : "#2b2b2b"
                    text: "Currencies"
                    font.pixelSize: 20
                    font.bold: true
                }
            }
         
            GroupBox {
                id: groupbBoxBTC
                Layout.maximumWidth: 400
                Material.background: "White"
                Material.accent: Material.Green
                title: qsTr("BTC")                    

                ColumnLayout {                    
                    //Layout.fillWidth: true
                    anchors.fill: parent
                    RowLayout{
                        Label {
                            text: "Current balance"
                            //Layout.preferredWidth: 300
                            Layout.maximumWidth: 400
                        }
                        Text {
                            id: balanceBTC
                            objectName: "balanceBTC"
                            text: newOrderService.getBalanceBTC();
                        }
                    }
                    
                    property bool createdBTCAddressVisible: false;
                    
                    RowLayout{
                        id: createdBTCAdressBox
                        objectName: "createdBTCAddressBox"                  
                        visible: parent.createdBTCAddressVisible

                        Label {
                            text: "Created BTC address"
                            Layout.preferredWidth: 150
                        }
                    }
                    RowLayout{
                        Text {
                            id: createdBTCAddress
                            objectName: "createdBTCAddress"
                            Layout.maximumWidth: 350
                            wrapMode: Text.Wrap
                            text: "";
                        }
                    }                   
                    RowLayout{
                        id: syncStatusBTCBox
                        objectName: "syncStatusBTC"                  

                        Timer {
                            id: syncStatusBTCTimer
                            interval: 5000; running: true; repeat: true
                            onTriggered: syncStatusBTC.text = newOrderService.getSyncStatusBTC()
                        }
                        Label {
                            text: "Sync status"
                            Layout.preferredWidth: 150
                        }
                        Text {
                            id: syncStatusBTC
                            objectName: "syncStatusBTC"
                            Layout.preferredWidth: 100
                        }
                    }
                    RowLayout{
                        Button {
                            Material.background: "White"
                            Material.foreground: "#2b2b2b"
                            font.capitalization: Font.MixedCase
                            id: createAddressBTC
                            objectName: "createAddressBTC"
                            text: "Create BTC address"
                            onClicked: {
                                createAddressBTC.visible= false
                                parent.parent.createdBTCAddressVisible = true
                                ooList.createBTCAddress()
                            }
                        }
                    }
                }
            }
            GroupBox {
                id: groupbBoxTFT
                Layout.maximumWidth: 400
                Material.background: "White"
                Layout.fillWidth: true
                Material.accent: Material.Green
                title: qsTr("TfChain")
                ColumnLayout {
                    //Layout.fillWidth: true
                    //anchors.fill: parent

                    RowLayout{

                        Label {
                            text: "Current balance"
                            Layout.maximumWidth: 400
                            //Layout.preferredWidth: 300
                        }
                        Text {
                            id: balance
                            objectName: "balanceTFT"
                            text: newOrderService.getBalanceTFT();
                        }
                    }
                    property bool createdTFTAddressVisible: false;

                    RowLayout{
                        id: createdTFTAdressBox
                        objectName: "createdTFTAdressBox"                  
                        visible: parent.createdTFTAddressVisible

                        Label {
                            text: "Created TFT address"
                            Layout.preferredWidth: 150
                        }
                    }
                    RowLayout{

                        Text {
                            id: createdTFTAddress
                            Layout.maximumWidth: 350
                            wrapMode: Text.Wrap
                            objectName: "createdTFTAddress"
                            text: "";
                        }
                    }
                    RowLayout{
                        id: syncStatusTFTBox
                        objectName: "syncStatusTFT"                  

                        Timer {
                            id: syncStatusTFTTimer
                            objectName: "syncStatusTFTTimer"
                            interval: 5000; running: true; repeat: true
                            onTriggered: syncStatusTFT.text = newOrderService.getSyncStatusTFT()
                        }
                        Label {
                            text: "Sync status"
                            Layout.preferredWidth: 150
                        }
                        Text {
                            id: syncStatusTFT
                            objectName: "syncStatusTFT"
                            Layout.preferredWidth: 100
                        }
                    }
                    RowLayout{
                        Button {
                            Material.background: "White"
                            Material.foreground: "#2b2b2b"
                            font.capitalization: Font.MixedCase
                            id: createAddressTFT
                            objectName: "createAddressTFT"
                            text: "Create TFT address"
                            onClicked: {
                                createAddressTFT.visible= false
                                parent.parent.createdTFTAddressVisible = true
                                newOrderService.createTFTAddress()
                                
                            }
                        }

                    }

                }
            }
            
        }
    }

    Pane {

        Material.elevation: 6
        Material.background: "White"
        Layout.fillWidth: true
        Material.accent: Material.Green

        ColumnLayout{
            
            RowLayout{
                Text {
                    color : "#2b2b2b"
                    text: "New order"
                    font.pixelSize: 20
                    font.bold: true
                }
            }
          
            RowLayout {
                Timer {
                    id: getIpTimer
                    interval: 5000; running: true; repeat: true
                    onTriggered: ipAddress.text = newOrderService.getIp()
                }
                Label {
                    text: "Role"
                    Layout.preferredWidth: 100
                }
                ComboBox {
                        id: role
                        objectName: "role"
                        width: 200
                        model: [ "Initiator", "Acceptor" ]
                        onActivated: newOrderService.initiatorAcceptorActivated(editText)
                        
                }
                Text {
                    id: ipAddress
                    objectName: "ipAddress"
                    color : "#2b2b2b"
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
                    text: "Please enter an IP"
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
            RowLayout {
                Button {
                    Material.background: Material.LightBlue
                    Material.foreground: "white"
                    font.bold: true
                    enabled: true
                    id: submitButton
                    font.capitalization: Font.MixedCase
                    objectName: "submitButton"
                    text: qsTr("Confirm")
                    onClicked: newOrderService.confirmNewOrder()
                    Layout.fillWidth: true
                }
            }
        }
    }

    
}
