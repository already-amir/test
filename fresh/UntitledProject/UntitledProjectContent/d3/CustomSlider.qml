/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls


Slider {
    id: root
    width: 280

    handle: Rectangle {
        id: handle
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + root.availableHeight / 2 - height / 2
        width: 20
        height: 20

        color: root.pressed ? Constants.controlDarkColor : Constants.controlColor
        border.color: hoverHandler.hovered ? Constants.controlBorderLightColor : Constants.controlBorderColor
        radius: 5

        HoverHandler {
            id: hoverHandler
        }
    }
}
