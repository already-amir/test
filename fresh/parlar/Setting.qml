import QtQuick 2.15
import QtQuick.Controls 2.15
Item {

    Column {
        anchors.centerIn: parent
        spacing: 20


        Icon{

            i_size: 100
            i_text:"enable"
            i_img: "img/ross.png"
            onClicked: wifiManager.enableWifi(true)
        }
        Icon{

            i_size: 100
            i_text:"disable"
            i_img: "img/ross.png"
            onClicked: wifiManager.enableWifi(false)
        }
        Icon{

            i_size: 100
            i_text:"Scan Networks"
            i_img: "img/ross.png"
            onClicked: wifiManager.scanNetworks()
        }





        ListView {
            id: listView
            width: parent.width * 0.8
            height: 200
            model: []
            delegate: Text { text: modelData }

            Connections {
                target: wifiManager
                onNetworksFound: {
                    listView.model = networks
                }
            }
        }
    }


}
