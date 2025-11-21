import QtQuick 2.15
import "../"

Rectangle {

    property alias exit_icon:exit

    anchors.fill: parent


    Image {
        id: image
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop


    }

    Icon{
        id:exit
        i_size: 40
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        i_img: "../img/ross.png"
        onClicked: pageLoader.source = "../Page_start.qml"
    }



    Rectangle{
        id:rec
        width: parent.width *0.8
        height: parent.height *0.75
        color: "#40ffffff"
        radius: width * 0.05
        border.color: "#80ffffff"
        anchors.centerIn: parent

        Row{
            id: row
            anchors.centerIn: parent
            spacing: rec.width *0.015
            Rectangle{
                width: rec.width *0.1
                height: rec.height *0.9
                color: "#40ffffff"
                radius: width * 0.1
                border.color: "#80ffffff"

            }
            Column{
                spacing: rec.height *0.01
                Rectangle{
                    width: rec.width *0.83
                    height: rec.height *0.1
                    color: "#40ffffff"
                    radius: width * 0.02
                    border.color: "#80ffffff"
                }

                Row{
                    spacing: rec.width *0.015
                    Rectangle{
                        width: rec.width *0.2
                        height: rec.height *0.79
                        color: "#40ffffff"
                        radius: width * 0.1
                        border.color: "#80ffffff"




                    }
                    Rectangle{
                        width: rec.width *0.4
                        height: rec.height *0.79
                        color: "#40ffffff"
                        radius: width * 0.05
                        border.color: "#80ffffff"




                    }
                    Rectangle{
                        width: rec.width *0.2
                        height: rec.height *0.79
                        color: "#40ffffff"
                        radius: width * 0.1
                        border.color: "#80ffffff"


                    }




                }
            }



        }



    }

}
