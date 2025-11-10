import QtQuick
import QtQuick.Controls
import FresnelDemo

Switch {
    id: root

    indicator: Rectangle {
        implicitWidth: 46
        implicitHeight: 16
        x: root.leftPadding
        y: parent.height / 2 - height / 2
        radius: 5
        color: root.position ? Constants.controlDarkColor : Constants.controlLightColor

        Rectangle {
            x: root.checked ? parent.width - width : 0
            y: (parent.height - height) / 2
            width: 20
            height: 20
            radius: 5
            color: root.pressed ? Constants.controlDarkColor : Constants.controlColor
            border.color: root.hovered ? Constants.controlBorderLightColor : Constants.controlBorderColor
        }
    }
}
