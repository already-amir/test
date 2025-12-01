import QtQuick 2.15


Item {
    Glob_var{
        id:glob

    }
    property real r: glob.red/256
    property real g: glob.green/256
    property real b: glob.blue/256
    property real t: glob.tran/100


    id: glassy
    property int g_width: 100
    property int g_heigh: 100
    property int g_round: 22

    width: g_width
    height: g_heigh

    Rectangle {
        anchors.fill: parent
        radius: g_round
        color: Qt.rgba(r,g,b,t)
        border.width: 1
        border.color: Qt.rgba(r,g,b,t*2)
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height
        radius: g_round
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(r,g,b,5*t) }
            GradientStop { position: 0.25; color: Qt.rgba(r,g,b,t) }
            GradientStop { position: 1.0; color: Qt.rgba(r,g,b,0) }
        }
    }
}
