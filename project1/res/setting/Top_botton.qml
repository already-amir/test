import QtQuick 2.15
import "../"

Glassy{
    id:top_id
    anchors.top: parent.top
    anchors.topMargin: 15
    anchors.horizontalCenter: parent.horizontalCenter

    g_heigh: glass.height * 0.1
    g_width: glass.width * 0.9

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
    Glassy{
        id:glassy2
        anchors.right:parent.right
        g_width:row_id1.width+20
        g_heigh:parent.height
        visible: wifi.wifi_enabeled
        Row{
            id:row_id1
            anchors.right: glassy2.right
            spacing:20
            Text {
                text: qsTr("scan")
                visible: wifi.wifi_enabeled
                font.pixelSize: 20

                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 20
            }
            Icon{
                id:scan_id
                i_img:"img/scan"
                i_size: glassy2.height
                visible: wifi.wifi_enabeled
                anchors.right: glassy2.right


            }

        }
        MouseArea{
            anchors.fill: parent
            onClicked: wifi.scan_wifi()
        }
    }




}
