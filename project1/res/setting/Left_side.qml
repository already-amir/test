import QtQuick 2.15
import "../"


Glassy{
    id:left_side_main
    g_width: setting_main.width * 0.2
    g_heigh: setting_main.height *0.9

    Column{
        anchors.top: parent.top
        anchors.topMargin: parent.height *0.05
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: parent.height * 0.02

        Left_side_panel{
            id:wifi_p_id
            p_width: left_side_main.width *0.8
            p_heights: left_side_main.height *0.1
            p_img: "img/wifi_on.png"
            p_txt: "WIFI"
            p_id: 1
        }

        Left_side_panel{
            id:bluetooth_p_id
            p_width: left_side_main.width *0.8
            p_heights: left_side_main.height *0.1
            p_img: "img/bluetooth.png"
            p_txt: "BLUETOOTH"
            p_id: 2
        }

        Left_side_panel{
            id:exit_p_id
            p_width: left_side_main.width *0.8
            p_heights: left_side_main.height *0.1
            //p_img: "../img/ross.png"
            p_txt: "BACK"
            p_id: -1
            MouseArea{
                anchors.fill: parent
                onClicked: pageLoader.source = "../Page_start.qml"
            }
        }
    }
}
