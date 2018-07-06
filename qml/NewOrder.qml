import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

ColumnLayout {
    //Layout.fillWidth: true
    width: 668

    states: [
        State {
            when: window.width <= maxWidthPhone
            PropertyChanges { target: paneCurrencies; Layout.preferredWidth: window.width - 20 } 
            PropertyChanges { target: paneNewOrder; Layout.preferredWidth: window.width - 20 }            
        },
        State {
            when: window.width > maxWidthPhone && window.width <= maxWidthTablet
            PropertyChanges { target: paneCurrencies; Layout.preferredWidth: window.width - 20 }
            PropertyChanges { target: paneNewOrder; Layout.preferredWidth: window.width - 20 }       
            PropertyChanges { target: flow1; width: 700 }
        },
        State {
            when: window.width > maxWidthTablet
            PropertyChanges { target: paneCurrencies; Layout.preferredWidth: 700 }
            PropertyChanges { target: paneNewOrder; Layout.preferredWidth: 700 }  
            PropertyChanges { target: flow1; width: 700 }
        }
        
    ]
    Pane {       
        id: paneCurrencies
        Layout.preferredWidth: 700
        Material.elevation: 6
        Material.background: "White"
        Material.accent: Material.Green

        ColumnLayout{
            id: columnLayout1
            Text {
                color : "#2b2b2b"
                text: "Currencies"
                font.pixelSize: 20
                font.bold: true
            }
            Flow{
                spacing: 10
                id: flow1
                Layout.maximumWidth: window.width - 20

                GroupBox {
                    id: groupbBoxBTC
                    //Layout.maximumWidth: 400
                    
                    Material.background: "White"
                    Material.accent: Material.Green
                    title: qsTr("BTC")                    
                    
                    ColumnLayout {                    
                        //Layout.fillWidth: true
                        anchors.fill: parent
                        RowLayout{
                            Label {
                                text: "Current balance"
                                Layout.preferredWidth: 150
                            }
                            Label {
                                Layout.preferredWidth: 150
                                id: balanceBTC
                                objectName: "balanceBTC"
                            }

                            Timer {
                                id: balanceBTCTimer
                                interval: 60000; running: true; repeat: true
                                onTriggered: balanceBTC.text = newOrderService.getBalanceBTC()
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
                                Layout.maximumWidth: 300
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
                            Label {
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
                                    newOrderService.createBTCAddress()
                                }
                            }
                        }
                    }
                }
                GroupBox {
                    id: groupbBoxTFT
                    //Layout.maximumWidth: 400
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
                                Layout.preferredWidth: 150
                            }
                            Label {
                                Layout.preferredWidth: 150
                                id: balanceTFT
                                objectName: "balanceTFT"
                            }
                            Timer {
                                id: balanceTFTTimer
                                interval: 60000; running: true; repeat: true
                                onTriggered: balanceTFT.text = newOrderService.getBalanceTFT()
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
                                Layout.maximumWidth: 300
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
                            Label {
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
    }

    Pane {
        id: paneNewOrder
        Layout.preferredWidth: 700
        Material.elevation: 6
        Material.background: "White"
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
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Timer {
                    id: getIpTimer
                    objectName: "getIpTimer"
                    interval: 5000; running: true; repeat: true
                    onTriggered: ipAddress.text = newOrderService.getIp()
                }
                Label {
                    text: "My IP"
                    Layout.preferredWidth: 100
                }

                TextEdit {
                    id: ipAddress
                    objectName: "ipAddress"
                    color : "#2b2b2b"
                    selectByMouse: true   
                    readOnly: true
                }
            }
            RowLayout {               
                id: ipAcceptorBox
                objectName: "ipAcceptorBox"
                visible: true

                Label {
                    text: "Peer IP"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: ipPeerId
                    objectName: "ipAcceptor"
                    Layout.fillWidth: true
                    validator: RegExpValidator { regExp: /\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b/ }
                    text: newOrderService.ipPeer
                }
                Binding {
                    target: newOrderService
                    property: "ipPeer"
                    value: ipPeerId.text
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
                Label {
                    text: "Sell"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: sellAmountId
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: RegExpValidator { regExp: /\d{1,9}(?:.\d{1,9})+$/ }
                    text: newOrderService.sellAmount
                }
                Binding {
                    target: newOrderService
                    property: "sellAmount"
                    value: sellAmountId.text
                }
                ComboBox {
                        id: coin
                        objectName: "coin"
                        width: 200
                        model: [  "BTC", "TFT"]
                        enabled: true;
                        onActivated: newOrderService.coinChanged(index)
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
                Label {
                    text: "Buy"
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: buyAmountId
                    Layout.fillWidth: true
                    validator: RegExpValidator { regExp: /\d{1,9}(?:.\d{1,9})+$/ }
                    text: newOrderService.buyAmount

                }
                Binding {
                    target: newOrderService
                    property: "buyAmount"
                    value: buyAmountId.text
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
