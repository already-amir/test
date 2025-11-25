import QtQuick 2.15
import "../"


Glassy{
    id:glass
    g_width: main.width * 0.7
    g_heigh: main.height *0.9
    property int selectedIndex: -1

        Top_botton{

        }

        Bottom{

        }



        Connections {
            target: wifi

            function onCommand_out(output) {
                //logBox.text += "\n" + output
            }

            function onCommand_err(error) {
                //logBox.text += "\n[ERROR] " + error
            }
        }




}
