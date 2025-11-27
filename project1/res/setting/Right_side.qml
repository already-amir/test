import QtQuick 2.15
import "../"
import QtQuick.Controls 2.15

Glassy{
    id:right_side_main
    g_width: setting_main.width * 0.7
    g_heigh: setting_main.height *0.9

    Wifi_panel{
        visible: (wifi_panel_id.selected_panel===2)
    }
}
