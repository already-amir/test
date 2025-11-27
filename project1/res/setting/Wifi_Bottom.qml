import QtQuick 2.15

import "../"
Glassy{

    id:wifi_bottom_main



    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: parent.height * 0.2

    visible: wifi.wifi_enabeled
    g_heigh: wifi_panel_id.height * 0.8
    g_width: wifi_panel_id.width * 0.9

    ListView {
        id: wifiListView
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8
        model: wifi.wifi_list
        clip: true

        delegate: Glassy {
            g_width: wifi_bottom_main.width*0.96
            g_heigh: wifi_panel_id.selectedIndex === index ? 140 : 50


            Behavior on g_heigh {
                NumberAnimation { duration: 150 }
            }

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 8

                Item{
                    width:wifi_bottom_main.width
                    height: 50

                    Text {
                        text: model.display
                        font.pixelSize: 16
                        font.bold: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (wifi_panel_id.selectedIndex === index)
                                wifi_panel_id.selectedIndex = -1
                            else {
                                wifi_panel_id.selectedIndex = index
                                wifi.ssid = model.display
                            }
                        }
                    }
                }

                Item {
                    width: parent.width
                    height: wifi_panel_id.selectedIndex === index ? 80 : 0
                    clip: true

                    Behavior on height {
                        NumberAnimation { duration: 150 }
                    }

                    Row {
                        anchors.fill: parent
                        spacing: 6

                        Rectangle {
                            id: passField
                            width: 250
                            height: 40
                            radius: 6
                            color: "#222"
                            border.color: passInput.activeFocus ? "#00A8FF" : "#555"
                            border.width: 1

                            property string placeholder: "Enter password..."

                            TextInput {
                                id: passInput
                                anchors.fill: parent
                                anchors.margins: 8

                                color: "white"
                                focus: true

                                echoMode: TextInput.Password
                                font.pixelSize: 14

                                onTextChanged: {
                                    if (wifi_panel_id.selectedIndex === index)
                                        wifi.password = text
                                }
                            }


                            Text {
                                text: passContainer.placeholder
                                color: "#888"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                visible: passInput.text.length === 0
                                font.pixelSize: 14
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: passInput.forceActiveFocus()
                            }
                        }
                        Icon{
                            i_text: "connect"
                            i_heights:passField.height
                            i_width: passField.height*3
                            onClicked: {
                                wifi.ssid = model.display
                                wifi.connect_wifi()
                            }
                        }


                    }
                }
            }


        }
    }


}
