import QtQuick 2.15
import "../"



Item {

    Image {
        id: image
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Icon{
        id:exit

        i_size: 60
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        i_img: "img/ross.png"
        onClicked: pageLoader.source = "../Page_start.qml"
    }

    Glassy{
        id:main
        g_width: parent.width *0.90
        g_heigh: parent.height *0.80
        g_round: g_width * 0.05
        anchors.centerIn: parent

        Row{
            id: row

            anchors.centerIn: parent

            spacing: main.width *0.01

            Left_side_panel{

            }
            Right_side_panel{

            }
        }
    }
}
