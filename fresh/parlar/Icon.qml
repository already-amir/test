import QtQuick 2.15

Item {

    id:icon
    property alias i_size: icon.size
    property alias i_img: icon_image.source
    signal clicked()
    property int size
    width: size
    height: size

    Glassy{

        anchors.fill: parent

        Image {
            id:icon_image
            source: "file"
            width: parent.width *0.7
            height: parent.height*0.7
            anchors.centerIn: parent
        }

        MouseArea{
            anchors.fill: parent
            onClicked: icon.clicked()
        }
    }
}
