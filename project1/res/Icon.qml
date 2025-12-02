import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15



Item {
    id:icon
    property int i_size: 50
    property int i_width:i_size
    property int i_heights:i_size
    property string i_img: ""
    property string i_text:""
    signal clicked()

    width: i_width
    height: i_heights
    scale: 1.0

    Behavior on scale {
        NumberAnimation { duration: 100; easing.type: Easing.OutQuad }
    }

    Glassy{
        id:gg
        anchors.fill: parent

        Row{

            spacing: parent.width*0.1
            anchors.centerIn: parent
            Image {
                visible: i_img!=""
                source: i_img
                width: gg.height*0.7
                height: gg.height*0.7
                anchors.verticalCenter : parent.verticalCenter
                //anchors.left: parent.left
            }

            Text{
                visible: i_text!=""
                text:i_text
                font.bold: true
                font.pixelSize: gg.width/(text.length*1.5)
                anchors.verticalCenter : parent.verticalCenter
            }
        }

        MouseArea{
            anchors.fill: parent
            onPressed: {
                icon.scale = 0.85
            }
            onReleased: {
                icon.scale = 1.0
                icon.clicked()
            }
            onCanceled: icon.scale = 1.0
        }
    }
}
