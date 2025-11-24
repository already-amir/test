import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    width: 400
    height: 600
    visible: true

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        //padding: 10

        ListView {
            id: wifiListView
            Layout.fillWidth: true
            Layout.preferredHeight: 300
            model: wifi.wifi_list

            delegate: Rectangle {
                width: parent.width
                height: 40
                border.width: 1
                radius: 4
                color: index % 2 === 0 ? "#f0f0f0" : "#ffffff"

                Text {
                    anchors.centerIn: parent
                    text: model.display  // یا modelData هم کار می‌کنه
                    font.pixelSize: 16
                    elide: Text.ElideRight
                }
            }
        }

        Button {
            text: "Scan WiFi"
            Layout.alignment: Qt.AlignHCenter
            onClicked: wifi.scan_wifi()
        }

        Text {
            id: statusText
            Layout.alignment: Qt.AlignHCenter
            color: "red"
            font.pixelSize: 14
        }
    }

    // نمایش خطاهای process
    Connections {
        target: handler
        onCommandError: {
            statusText.text = "Error: " + error
        }
        onCommandOutput: {
            statusText.text = "Scan complete. Found " + wifi.wifi_list.count + " networks"
        }
    }
}
