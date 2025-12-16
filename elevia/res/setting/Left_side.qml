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

        Icon{
            id:wifi_p_id
            i_width: left_side_main.width *0.8
            i_heights: left_side_main.height *0.1
            i_img: "img/wifi_on.png"
            i_text: "WIFI"
            onClicked: selected_panel=1
        }
        Icon{
            id:bluetooth_p_id
            i_width: left_side_main.width *0.8
            i_heights: left_side_main.height *0.1
            i_img: "img/bluetooth.png"
            i_text: "BLUETOOTH"
            onClicked: selected_panel=2
        }
        Icon{
            id:exit_p_id
            i_width: left_side_main.width *0.8
            i_heights: left_side_main.height *0.1
            i_text: "BACK"
            onClicked: pageLoader.source = "../Page_start.qml"
        }
    }
}
