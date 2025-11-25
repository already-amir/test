import QtQuick 2.15
import "../"
import QtQuick.Controls 2.15
Item {
    anchors.fill:parent
    id:main
    Image {
        id: image
        anchors.fill: parent
        source: "../img/ab.jpg"
        fillMode: Image.PreserveAspectCrop
    }



    Row{
        anchors.centerIn: parent
        spacing: 20

        Glassy{
            g_width: main.width * 0.2
            g_heigh: main.height *0.9

            Button {
                text: "Check Internet"
                onClicked: wifi.pingGoogle()
            }

            Connections {
                target: wifi

                function onPingResult(success, output) {
                    if (success)
                        console.log("✅ Connected to internet:", output)
                    else
                        console.log("❌ No internet:", output)
                }
            }


        }

        Right_side{

        }


    }

















}
