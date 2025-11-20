import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id:appWindow
    visibility: Window.FullScreen
    visible: true
    title: "Parlar"

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "Page_start.qml"

    }

}
