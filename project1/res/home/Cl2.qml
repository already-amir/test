import QtQuick 2.15
import"../"

Column {

    spacing: panel_id.height * 0.02

   Glassy{
        width:panel_id.width * 0.4
        height:panel_id.height *0.3

    }
   Row{
        spacing: panel_id.width * 0.02
       Glassy{
            width:panel_id.width * 0.19
            height:panel_id.height *0.27

        }
       Glassy{
            width:panel_id.width * 0.19
            height:panel_id.height *0.27

        }
   }


   Glassy{
        width:panel_id.width * 0.4
        height:panel_id.height *0.41

    }

}
