import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"
Glassy{

    id:bottom_id

    anchors.bottomMargin: 15
    anchors.bottom: parent.bottom

    anchors.horizontalCenter: parent.horizontalCenter
    visible: wifi.wifi_enabeled
    g_heigh: glass.height * 0.8
    g_width: glass.width * 0.9

    ListView {
        id: wifiListView
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8
        model: wifi.wifi_list
        clip: true

        delegate: Glassy {
            g_width: bottom_id.width
            g_heigh: glass.selectedIndex === index ? 140 : 50


            Behavior on g_heigh {
                NumberAnimation { duration: 200 }
            }

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 8

                Item{
                    width:bottom_id.width
                    height: 50

                    Text {
                        text: model.display
                        font.pixelSize: 16
                        font.bold: true


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


        }
    }


}
