import QtQuick
import QtQuick.Controls


Button {
    id: root
    signal clicked()
    property alias bgColor: rectangle.color
    width: 125
    height: 30
    contentItem: Text {
        text: root.text
        color: Constants.textColor
        horizontalAlignment: Text.AlignHCenter
    }
    background: Rectangle {
        id: rectangle
        color: root.pressed ? Constants.controlDarkColor : Constants.controlColor
        border.color: root.hovered ? Constants.controlBorderLightColor : Constants.controlBorderColor
        radius: 5
    }
    MouseArea{
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
