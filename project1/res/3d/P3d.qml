import QtQuick 2.15
import "../"
Item {

    Rectangle {
        id: root

        anchors.fill: parent

        Image {

            anchors.fill: parent
            source: "../img/ab.jpg"
        }

        Icon{
            id:exit
            i_size: 40
            anchors.right: parent.right
            anchors.top:parent.top
            anchors.rightMargin: 8
            anchors.topMargin: 8
            i_img: "../img/ross.png"
            onClicked: pageLoader.source = "../Page_start.qml"

        }


        Glassy {
            id: glass

            g_width: 300
            g_heigh: 300
            g_round: 20
            anchors.centerIn: parent



            Text{
                text: "3D"
                anchors.centerIn: parent
                font.bold: true
                font.pixelSize: 20
            }
        }
    }


}
