/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick
import QtQuick.Controls
import UntitledProject7

Rectangle {
    id: rectangle2
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor
    property bool a: false

    Row{
        anchors.centerIn: parent
        Rectangle {
            id: rectangle

            width: 100
            height: 100
            color: a?"red":"blue"
        }

        Rectangle {
            id: rectangle1

            width: 100
            height: 100
            color: "#ffffff"
            MouseArea {
                id: mouseArea

                anchors.fill: parent

                Connections {
                    target: mouseArea
                    function onClicked() { rectangle2.a=!rectangle2.a
                    aa.say_hello()
                    }
                }
            }
        }

    }






}
