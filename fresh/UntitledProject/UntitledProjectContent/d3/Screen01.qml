import QtQuick

Screen01Form {

    signal gotoPage(string page)

    exitButton_icon.onClicked: gotoPage("Main.qml")


}
