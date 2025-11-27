import QtQuick 2.15
import "../"

Glassy{
    id:left_side_panel_id


    property int p_width:40
    property int p_heights: 40
    property string p_img: ""
    property string p_txt:""
    property int p_id: -1


    width:p_width
    height: p_heights


    Row{
        anchors.left: parent.left
        anchors.leftMargin: left_side_panel_id.width *0.05
        spacing: parent.width *0.1
        anchors.verticalCenter: parent.verticalCenter
        Image {
            width: Math.min(left_side_panel_id.width,left_side_panel_id.height)*0.8
            height: width
            source: p_img

        }
        Text {
            text: qsTr(p_txt)
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            font.pixelSize: left_side_panel_id.width * 0.08
        }
    }

    MouseArea{
        anchors.fill:parent
        onClicked: setting_main.selected_panel=p_id
    }
}
