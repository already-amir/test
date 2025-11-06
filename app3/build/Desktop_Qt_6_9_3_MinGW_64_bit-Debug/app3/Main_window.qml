import QtQuick

Item {

    id:main_win

    property int icon_size: Math.min(main_win.width,main_win.height)/3

    Image {
        id: name
        source: "file:bg.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop

    }

    Rectangle{
        anchors.centerIn: parent
        radius: 20
        color:"#40FFFFFF"
        border.width: 1
        border.color: "#80FFFFFF"
        layer.enabled: true
        layer.smooth: true
        width:row_1.implicitWidth+icon_size/6
        height: row_1.implicitHeight+icon_size/6
        Row{
            id:row_1
            anchors.centerIn: parent
            spacing: 20
            Icon{
                width: icon_size
                height: icon_size
                i_img: "file:home.png"
                qml_file: "Home_window.qml"

            }
            Icon{
                width: icon_size
                height: icon_size

                i_img: "file:settings.png"
                qml_file: ".qml"

            }
            Icon{
                width: icon_size
                height: icon_size
                qml_file: ".qml"
                i_img: "file:boiler.png"

            }

        }

    }
}
