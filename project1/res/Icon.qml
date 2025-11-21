import QtQuick 2.15

Item {

    id:icon
    property int i_size: 50
    property string i_img: "img/ross.png"
    property string i_text:""
    signal clicked()

    width: i_size
    height: i_size

    Glassy{
        anchors.fill: parent

        Image {
            id:icon_image
            source: i_img
            width: parent.width *0.7
            height: parent.height*0.7
            anchors.centerIn: parent
        }
        Text{
            id:text_id
            text:i_text
            width: parent.width
            height: parent.height * 0.1
        }
        MouseArea{
            anchors.fill: parent
            onClicked: icon.clicked()
        }
    }
}
