import QtQuick 2.15

Item {
    id:wifi_panel_id
    anchors.fill:parent

    property int selectedIndex: -1

    Wifi_Top{

    }
    Wifi_Bottom{

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
        function onConnected() {
            console.log("✅ Connected to WiFi")
        }

        function onConnectionFailed(reason) {
            console.log("❌ Connection failed:", reason)
        }
        function onWifi_listChanged() {
            console.log("WiFi list updated")
        }
    }



}
