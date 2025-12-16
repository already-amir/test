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

    Icon{
      i_width: main_left.width *0.8
      i_heights: main_left.height *0.1

      i_text: "BACK"
      onClicked: pageLoader.source = "../Page_start.qml"
    }


  }
}
