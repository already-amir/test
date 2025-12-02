import QtQuick 2.15
import "../"

Item{
    Image {
        id: image
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Icon{
        id:exit
        i_size: parent.height * 0.2
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: parent.width *0.02
        anchors.topMargin: parent.height *0.02
        i_img: "img/ross.png"
        onClicked: pageLoader.source = "../Page_start.qml"
    }
}

