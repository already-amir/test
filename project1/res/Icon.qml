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

    property bool name: value

    width: i_width
    height: i_heights

    Glassy{
        anchors.fill: parent

        Image {
            id:icon_image
            source: i_img
            width: parent.width*0.7
            height: parent.height*0.7
            anchors.centerIn: parent
        }
        Text{
            id:text_id
            text:i_text
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: parent.width/(text.length*0.7)

        }
        MouseArea{
            anchors.fill: parent
            onClicked: icon.clicked()
        }

        //



    }
}
