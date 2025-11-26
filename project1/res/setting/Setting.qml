import QtQuick 2.15

Item {
    anchors.fill:parent
    id:setting_main
    Image {
        id: image
        anchors.fill: parent
        source: "../img/ab.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Row{
        anchors.centerIn: parent
        spacing: 20



        Left_side{

        }

        Right_side{

        }
    }
}
