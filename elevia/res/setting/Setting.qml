import QtQuick 2.15

Item {
    anchors.fill:parent
    id:setting_main
    property int selected_panel: -1

    Image {
        id: image
        anchors.fill: parent
        source: "../img/ab.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Row{
        anchors.centerIn: parent
        spacing: parent.width*0.02

        Left_side{

        }

        Right_side{

        }
    }
}
