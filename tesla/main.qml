import QtQuick 2.15
import QtQuick.Window 2.15

import "ui/bottom"
import "ui/right"
import "ui/left"

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Hello World")

    Item{
        id:it
        //property int x:35
        //property int y:51
        property int namex: 100
        property int namey: 100

    }

    Right_side{
        id:right_id
    }
    Left_side{
        id:left_id
    }




    Bottem_bar{
        id:bottem_id
    }



}
