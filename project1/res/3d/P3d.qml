import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
ColumnLayout {
        anchors.fill: parent
        spacing: 10
        //padding: 10

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "Enable WiFi"
                onClicked: wifi.enable_wifi()
            }

            Button {
                text: "Disable WiFi"
                onClicked: wifi.disable_wifi()
            }

            Button {
                text: "Scan Networks"
                onClicked: wifi.scan_wifi()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 10
            color: "#1e1e1e"

            ListView {
                id: wifiListView
                anchors.fill: parent
                anchors.margins: 10
                spacing: 6
                model: wifi.wifi_list

                delegate: Rectangle {
                    width: parent.width
                    height: 50
                    radius: 6
                    color: index % 2 === 0 ? "#2e2e2e" : "#3a3a3a"

                    Text {
                        text: modelData
                        color: "white"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        font.pixelSize: 16
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Selected Network:", modelData)
                        }
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 120
            radius: 10
            color: "#101010"

            TextArea {
                id: logBox
                anchors.fill: parent
                color: "lime"
                font.pixelSize: 13
                readOnly: true
                wrapMode: Text.Wrap
            }
        }
        Connections {
            target: wifi

            function onCommand_out(output) {
                logBox.text += "\n" + output
            }

            function onCommand_err(error) {
                logBox.text += "\n[ERROR] " + error
            }
        }
    }



