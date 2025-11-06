import QtQuick

Item {
    id:back
    function open_url(url){
        Qt.openUrlExternally(url)
    }
}
