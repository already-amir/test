import QtQuick


Item {

    id:icon
    property alias i_width: icon.width
    property alias i_height:icon.height
    property alias i_img: icon_image.source
    property alias qml_file: icon.qml

    property string qml:""
    width:_.icon_size
    height: _.icon_size

    Rectangle{
        anchors.fill: parent

        radius: 20
        color:"#40FFFFFF"
        border.width: 1
        border.color: "#80FFFFFF"
        layer.enabled: true
        layer.smooth: true


        Image {
            id:icon_image
            source: "file"
            width: parent.width *0.7
            height: parent.height*0.7
            anchors.centerIn: parent

        }

        MouseArea{
            id:clk
            anchors.fill:parent
            onClicked: {
                panelLoader.source = qml
            }

        }



    }
}
