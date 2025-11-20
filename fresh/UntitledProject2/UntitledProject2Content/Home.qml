//Home.qml
import QtQuick

HomeForm {
    signal gotoPage(string page)

    exit_icon.onClicked: gotoPage("Main.qml")
}
