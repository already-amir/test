import QtQuick 2.15
import "../"
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
Item{
    id:window
    Image {
        id: screenBackground
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Icon{
        id:exit
        i_size: parent.height * 0.2
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: parent.width *0.02
        anchors.topMargin: parent.height *0.02
        i_img: "img/ross.png"
        onClicked: pageLoader.source = "../Page_start.qml"
    }




    Item {
        id: root
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15

            // Header
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Text {
                    text: "Bluetooth Manager"
                    font.bold: true
                    font.pixelSize: 26
                }

                Rectangle {
                    width: 16; height: 16
                    radius: 8
                    color: bluetooth.powered ? "#4CAF50" : "#F44336"
                }

                Button {
                    text: bluetooth.powered ? "Turn Off" : "Turn On"
                    enabled: !bluetooth.busy
                    onClicked: {
                        if (bluetooth.powered)
                            bluetooth.powerOff()
                        else
                            bluetooth.powerOn()
                    }
                }

                Item { Layout.fillWidth: true }

                BusyIndicator {
                    running: bluetooth.busy
                    visible: bluetooth.busy
                }
            }

            // Scan button
            Button {
                text: "Scan"
                enabled: !bluetooth.busy
                onClicked: bluetooth.startScan()
            }

            // Device List
            ListView {
                id: deviceList
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 8
                clip: true
                model: bluetooth.device_list

                delegate: Rectangle {
                    width: parent.width
                    height: 70
                    radius: 10
                    color: "#202020"
                    border.color: "#444"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        ColumnLayout {
                            Layout.fillWidth: true
                            Text {
                                text: JSON.parse(modelData).name
                                font.pixelSize: 18
                                color: "white"
                            }
                            Text {
                                text: JSON.parse(modelData).mac
                                font.pixelSize: 14
                                color: "#bbbbbb"
                            }
                        }

                        ColumnLayout {
                            spacing: 4

                            Text {
                                text: JSON.parse(modelData).connected ? "Connected" : "Disconnected"
                                color: JSON.parse(modelData).connected ? "lightgreen" : "tomato"
                                font.pixelSize: 14
                            }

                            Row {
                                spacing: 8

                                Button {
                                    text: JSON.parse(modelData).connected ? "Disconnect" : "Connect"
                                    enabled: !bluetooth.busy
                                    onClicked: {
                                        if (JSON.parse(modelData).connected)
                                            bluetooth.disconnectDevice(JSON.parse(modelData).mac)
                                        else
                                            bluetooth.connectDevice(JSON.parse(modelData).mac)
                                    }
                                }

                                Button {
                                    text: JSON.parse(modelData).paired ? "Unpair" : "Pair"
                                    enabled: !bluetooth.busy
                                    onClicked: bluetooth.pairDevice(JSON.parse(modelData).mac)
                                }

                                Button {
                                    text: JSON.parse(modelData).trusted ? "Untrust" : "Trust"
                                    enabled: !bluetooth.busy
                                    onClicked: bluetooth.trustDevice(JSON.parse(modelData).mac)
                                }

                                Button {
                                    text: "Remove"
                                    enabled: !bluetooth.busy
                                    onClicked: bluetooth.removeDevice(JSON.parse(modelData).mac)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}


