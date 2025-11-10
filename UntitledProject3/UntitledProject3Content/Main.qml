//Main.qml
import QtQuick
import UntitledProject3

MainForm {
    signal gotoPage(string page)

    home_icon.onClicked: gotoPage("Home.qml")
    boiler_icon.onClicked: gotoPage("Boiler.qml")
    setting_icon.onClicked: gotoPage("a_App.qml")
    d3d_icon.onClicked: gotoPage("a_App.qml")
}
