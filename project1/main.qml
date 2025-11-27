import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id:appWindow
    //
    width: 800
    height: 480
    //visibility: Window.FullScreen
    visible: true
    title: "ELEVIA"

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "res/Page_start.qml"

    }
}

