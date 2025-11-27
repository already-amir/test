import QtQuick 2.15
import"../"
Item {

    Image {
        id: image
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Icon{
        id:exit

        i_size: Math.min(parent.width,parent.height)/8
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        i_img: "img/ross.png"
        onClicked: pageLoader.source = "../Page_start.qml"
    }
}
