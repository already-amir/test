import QtQuick 2.15
import "../"

Glassy{
    id:wifi_top_main
    anchors.top: wifi_panel_id.top
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.topMargin: parent.height * 0.05
    g_heigh: wifi_panel_id.height * 0.1
    g_width: wifi_panel_id.width * 0.9

    Icon{
        anchors.left: parent.left
        i_img: wifi.wifi_enabeled ? "img/wifi_on":"img/wifi_off"
        i_size: parent.height

        onClicked:{
            if(wifi.wifi_enabeled){
                wifi.disable_wifi()
            }
            else{
                wifi.enable_wifi()
            }
        }
    }

    Icon{
        anchors.horizontalCenter: parent.horizontalCenter
        i_size: parent.height
        onClicked: wifi.pingGoogle()
        i_img: "img/ping.png"
        visible: wifi.wifi_enabeled
    }

    Icon{
        id:wifi_top_main_glass
        anchors.right:parent.right
        i_width:parent.height*3
        i_heights:parent.height
        i_text: "scan"
        i_img:"img/scan"
        visible: wifi.wifi_enabeled
        onClicked: wifi.scan_wifi()
    }
}
