
import QtQuick

Window {

    id:main_qml

    Item{
        id:_
        property int main_width:800
        property int main_heigh:480

    }

    width: _.main_width
    height: _.main_heigh

    visible: true
    title: qsTr("Parlar app")

    Image {
        id: name
        source: "file:bg.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop

    }

    Loader{
        id: panelLoader
        anchors.fill: parent
        source: "Main_window.qml"
    }









}
