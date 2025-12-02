import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property bool s: true

    color:s?"red":"blue"

    Rectangle{
        width:100
        height: 100
        color:!s?"red":"blue"
        anchors.centerIn: parent
        MouseArea{
            anchors.fill: parent
            onClicked: s=!s
        }
        Text {

            text: qsTr("running on QT 6")
            anchors.centerIn: parent
        }
    }
}
