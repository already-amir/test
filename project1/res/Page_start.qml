import QtQuick 2.15


Rectangle {
    id: root
    property int icon_size: Math.min(root.width, root.height) * 0.3

    Image {

        anchors.fill: parent
        source: "img/ab.jpg"
    }

    Icon{
        id:exit

        i_size: 100
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        i_img: "img/ross.png"
        onClicked: Qt.quit()
    }

    Glassy {
        id: glass

        g_width: row.width*1.1
        g_heigh: row.height*2
        g_round: row.width *0.1

        anchors.centerIn: parent

        Row {
            id: row

            anchors.centerIn: parent
            spacing: icon_size / 10

            Icon {
                id: home
                i_size: icon_size
                i_img: "img/home.png"
                onClicked: pageLoader.source = "home/Home.qml"
            }
            Icon {
                id: boiler

                i_size: icon_size
                i_img: "img/boiler.png"
                onClicked: pageLoader.source = "boiler/Boiler.qml"
            }
            Icon {
                id: setting

                i_size: icon_size
                i_img: "img/settings.png"
                onClicked: pageLoader.source = "setting/Setting.qml"
            }
            Icon {
                id: d3d

                i_size: icon_size
                i_img: "img/P3d.png"
                onClicked: pageLoader.source = "3d/P3d.qml"
            }
        }
    }
}
