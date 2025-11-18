import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
Rectangle{
    id:left_side
    anchors{
        left: parent.left
        right: right_id.left
        top: parent.top
        bottom: bottem_id.top
    }
    color:"orange"

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            name: "osm"  // OpenStreetMap plugin
        }
        center: QtPositioning.coordinate(it.namex, it.namey)  // Tehran coordinates
        zoomLevel: 14

    }

}
