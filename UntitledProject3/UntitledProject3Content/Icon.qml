//Icon.qml

import QtQuick


Item {

    id:icon
    property alias i_size: icon.size
    property alias i_img: icon_image.source
    signal clicked()
    property int size
    width: size
    height: size


    Rectangle{
        anchors.fill: parent

        radius: width*0.2
        color:"#40FFFFFF"
        border.width: 1
        border.color: "#80FFFFFF"



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
