
//App.qml
import QtQuick
import UntitledProject3
import QtQuick3D.Particles3D


Window {
    id:appWindow
    width: 800
    height: 480

    visible: true
    title: "Parlar"

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "Main.qml"

        onLoaded: {
            item.gotoPage.connect(function(page){
                pageLoader.source = page
            })
        }
    }

}

