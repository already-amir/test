import QtQuick 2.15
import "../"


Glassy{
  id:main_left
  g_width: main.width * 0.15
  g_heigh: main.height *0.95

  Column{
    anchors.top: parent.top
    anchors.topMargin: parent.height *0.05
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: parent.height * 0.02

    Left_side_panel{
      id:wifi_p_id
      p_width: main_left.width *0.8
      p_heights: main_left.height *0.1
      p_img: "img/ross.png"
      p_txt: "BACK"

      MouseArea{
        anchors.fill: parent
        onClicked: pageLoader.source = "../Page_start.qml"
      }
    }
  }
}
