import QtQuick 2.15

Item {

    Rectangle {
        id: root


        anchors.fill: parent

        Image {

            anchors.fill: parent
            source: "img/ab.jpg"
        }

        Icon{
            id:exit
            i_size: 40
            anchors.right: parent.right
            anchors.top:parent.top
            anchors.rightMargin: 8
            anchors.topMargin: 8
            i_img: "img/ross.png"
            onClicked: pageLoader.source = "Page_start.qml"
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
                Icon{

                    i_size: 100
                    i_text:"enable"
                    i_img: "img/ross.png"
                    onClicked: wifimanage.enableWifi(true)
                }
                Icon{

                    i_size: 100
                    i_text:"disable"
                    i_img: "img/ross.png"
                    onClicked: wifimanage.enableWifi(false)
                }
                Icon{

                    i_size: 100
                    i_text:"Scan Networks"
                    i_img: "img/ross.png"
                    onClicked: wifimanage.scanNetworks()
                }





                ListView {
                    id: listView
                    width: parent.width * 0.8
                    height: 200
                    model: []
                    delegate: Text { text: modelData }

                    Connections {
                        target: wifimanage
                        onNetworksFound: {
                            listView.model = networks
                        }
                    }
                }
            }
        }
    }


}
