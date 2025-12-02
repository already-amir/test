import QtQuick 2.15
import "../"




Item{

    id:right_side
    width: main.width * 0.8
    height: main.height *0.95

    Column{
        anchors.centerIn: parent
        spacing: right_side.height * 0.02
        Rectangle{
           width:right_side.width*0.9
           height: right_side.height *0.15
        }

        Item{
            id:panel_id
            width:right_side.width*0.90
            height: right_side.height *0.75

            Row{
                anchors.centerIn: parent
                spacing: panel_id.width * 0.02
                Cl1{

                }

                Cl2{

                }
                Cl3{

                }
            }
        }
    }
}
