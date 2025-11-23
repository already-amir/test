
import QtQuick 2.15
import "../"


Rectangle {
    id: root


    anchors.fill: parent

    Image {

        anchors.fill: parent
        source: "../img/ab.jpg"
    }

    Icon{
        id:exit
        i_size: Math.min(parent.width,parent.height)/8
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        i_img: "../img/ross.png"
        onClicked: pageLoader.source = "../Page_start.qml"
    }

    Glassy {
        id: glass

        g_width: row.width*1.1
        g_heigh: row.height*2
        g_round: row.width *0.1

        anchors.centerIn: parent

        Row {
            id: row
            anchors.centerIn: parent

            spacing: 100 / 10
            Icon{

                i_size: 100
                i_text:"enable"
                i_img: "../img/ross.png"
                onClicked:{
                    handler.enable_wifi()


                }
            }
            Icon{

                i_size: 100
                i_text:"disable"
                i_img: "../img/ross.png"
                onClicked: handler.disable_wifi()

            }
            Icon{

                i_size: 100
                i_text:"Scan Networks"
                i_img: "../img/ross.png"
                onClicked: handler.scan_wifi()

            }








        }
    }
}



