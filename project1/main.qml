import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id:appWindow
    //visibility: Window.FullScreen
    width: 800
    height: 480
    visible: true
    title: "Parlar"


    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "res/Page_start.qml"

    }







}

