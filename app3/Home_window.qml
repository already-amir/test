import QtQuick

Item {
    id:main_win

    property int icon_size: Math.min(main_win.width,main_win.height)/3

    Row{
        width: parent.width * 0.95
        height: parent.height *0.95
        spacing: parent.width*0.01
        anchors.centerIn: parent
        Column{
            height: parent.height
            width:parent.width*0.29
            Icon{
                anchors.fill: parent
                width: parent.width
                height:parent.height
                i_img: "file:settings.png"


            }
        }
        Column{
            height: parent.height
            width:parent.width*0.4
            Icon{
                width: parent.width
                height:parent.height

                i_img: "file:settings.png"


            }
        }
        Column{
            height: parent.height
            width:parent.width*0.29
            Icon{
                anchors.fill: parent
                width: parent.width
                height:parent.height
                i_img: "file:settings.png"


            }
        }
    }



}
