import QtQuick 2.15
import "../"

Item {
    id:wifi_panel_id
    anchors.fill:parent

    property int selected_index: -1


    Wifi_Top{

    }
    Wifi_Bottom{

    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        radius: 20
        opacity: wifi.busy ? 0.4 : 0
        visible: opacity > 0
        z: 999

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }

        MouseArea {
            anchors.fill: parent
            enabled: wifi.busy
        }
        Image {
            anchors.centerIn: parent
            visible: wifi.busy


            source: "../img/loading.gif"
            width: 40
            height: 40

        }
    }


    Connections {
        target: wifi

        function onCommand_out(output) {
            //logBox.text += "\n" + output
        }

        function onCommand_err(error) {
            //logBox.text += "\n[ERROR] " + error
        }
        function onPingResult(success, output) {
            if (success)
                console.log("✅ Connected to internet:", output)
            else
                console.log("❌ No internet:", output)
        }
        function onConnected(success,reason) {

            if (success){
                console.log("✅ Connected to WiFi")
                //connect_b.text="connected"
            }

            else
                console.log("❌ Connection failed:", reason)
        }

        function onWifi_listChanged() {
            console.log("WiFi list updated")
        }
    }



}
