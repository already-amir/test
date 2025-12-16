import QtQuick 2.15
import "../"



Item {

    Image {
        id: image
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Glassy{
        id:main
        g_width: parent.width*0.9
        g_heigh: parent.height *0.8
        anchors.centerIn: parent

        Row{
            anchors.centerIn: parent
            spacing: parent.width*0.01
            Left_side{

            }



            Right_side{

            }
        }
    }
}
