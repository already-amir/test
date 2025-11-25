import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"
Item{
    Image {
        id: image
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop
    }
    Glassy {
        id: glass
        g_width: 500
        g_heigh: 500

        property int selectedIndex: -1

        Column {
            anchors.centerIn: parent
            spacing: 10



            Glassy {
                g_heigh: glass.height * 0.8
                g_width: glass.width * 0.9

                ListView {
                    id: wifiListView
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 8
                    clip: true
                    model: wifi.wifi_list

                    delegate: Glassy {
                        id: cell
                        g_width: parent.width
                        g_heigh: glass.selectedIndex === index ? 140 : 50



                        Behavior on height {
                            NumberAnimation { duration: 200 }
                        }


                        Column {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 8

                            // SSID
                            Text {
                                text: model.display
                                font.pixelSize: 16
                                font.bold: true
                            }

                            // بخش بازشونده
                            Item {
                                width: parent.width
                                height: glass.selectedIndex === index ? 80 : 0
                                clip: true

                                Behavior on height {
                                    NumberAnimation { duration: 150 }
                                }

                                Column {
                                    anchors.fill: parent
                                    spacing: 6

                                    TextField {
                                        id: passField
                                        placeholderText: "Enter password..."
                                        echoMode: TextInput.Password
                                        onTextChanged: {
                                            if (glass.selectedIndex === index)
                                                wifi.password = text
                                        }
                                    }

                                    Button {
                                        text: "Connect"
                                        height: 32
                                        onClicked: {
                                            wifi.ssid = model.display
                                            wifi.connect_wifi()
                                        }
                                    }
                                }
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (glass.selectedIndex === index)
                                    glass.selectedIndex = -1
                                else {
                                    glass.selectedIndex = index
                                    wifi.ssid = model.display
                                }
                            }
                        }
                    }
                }
            }

            Text {
                id: statusText
                text: ""
                color: "white"
                font.pixelSize: 14
            }

            Connections {
                target: wifi

                function onConnected() {
                    statusText.text = "✅ Connected to " + wifi.ssid
                }

                function onConnectionFailed(reason) {
                    statusText.text = "❌ " + reason
                }

                function onCommand_err(err) {
                    statusText.text = "⚠ " + err
                }
            }
        }
    }

}

