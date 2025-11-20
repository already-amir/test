import QtQuick 2.15

Item {
    id: glassy
    property int g_width: 100
    property int g_heigh: 100
    property int g_round: 0.2*g_width

    width: g_width
    height: g_heigh

    Rectangle {
        anchors.fill: parent
        radius: g_round
        color: "#40FFFFFF"
        border.width: 1
        border.color: "#80FFFFFF"
    }
}
