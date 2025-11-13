
//HomeForm.ui.qml
/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls


Rectangle {

    property alias exit_icon:exit

    anchors.fill: parent


    Image {
        id: image
        anchors.fill: parent
        source: "images/grey chair ag.jpg"
        fillMode: Image.PreserveAspectCrop


    }

    Icon{
        id:exit
        x: 592
        i_size: 40
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        i_img: "images/ross.png"
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

                        Dial {
                            id: dial
                           anchors.centerIn: parent
                            width: 88
                            height: 142
                        }


                    }
                    Rectangle{
                        width: rec.width *0.4
                        height: rec.height *0.79
                        color: "#40ffffff"
                        radius: width * 0.05
                        border.color: "#80ffffff"

                        Switch {
                            id: switch1
                            text: qsTr("Switch")
                        }


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
