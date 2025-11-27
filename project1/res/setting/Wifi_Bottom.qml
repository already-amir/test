import QtQuick 2.15
import QtQuick.Controls 2.15
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
            g_heigh: wifi_panel_id.selected_index === index ? 140 : 50


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
                            if (wifi_panel_id.selected_index === index)
                                wifi_panel_id.selected_index = -1
                            else {
                                wifi_panel_id.selected_index = index
                                wifi.ssid = model.display
                            }
                        }
                    }
                }

                Item {
                    width: parent.width
                    height: wifi_panel_id.selected_index === index ? 80 : 0
                    clip: true

                    Behavior on height {
                        NumberAnimation { duration: 150 }
                    }

                    Row {
                        anchors.fill: parent
                        spacing: 6

                        TextField {
                            id: passField
                            placeholderText: "Enter password..."
                            echoMode: TextInput.Password
                            onTextChanged: {
                                if (wifi_panel_id.selected_index === index)
                                    wifi.password = text
                            }
                        }
                        Icon{
                            id:connect_b
                            i_text: "connect"
                            i_heights:passField.height
                            i_width: passField.height*3
                            onClicked: {
                                wifi.ssid = model.display
                                wifi.connect_wifi()
                            }

                            Connections{
                                target: wifi
                                function onConnected(success,reason) {

                                    if (success){
                                        console.log("✅ Connected to WiFi")
                                        connect_b.i_text="connected"

                                    }

                                    else{
                                        console.log("❌ Connection failed:", reason)
                                        connect_b.i_text="not connected"+reason
                                    }



                                }
                            }
                        }


                    }
                }
            }


        }
    }
    //






}
