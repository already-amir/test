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


        Glassy{
            width:left_side_main.width*0.9
            height: left_side_main.height*0.1

            MouseArea{
                anchors.fill:parent
                onClicked: wifi_panel_id.selected_panel=1
            }

        }
    }





}
