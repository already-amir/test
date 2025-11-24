import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    width: 400
    height: 600
    visible: true





    ListView {
        width: 600
        height: 250
        model: handler.NNetworksModel

        delegate: Rectangle {
            width: ListView.view.width
            height: 40
            border.width: 1

            Text {
               text: model.display
                anchors.centerIn: parent
            }
        }

    }


    Button {
        text: "Scan WiFi"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: handler.scan_wifi()
    }
}
