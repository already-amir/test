//MainForm.ui.qml

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/


import QtQuick
import QtQuick.Controls
import UntitledProject3

Rectangle {
    id: root
    property int icon_size: Math.min(root.width,root.height)*0.3

    property alias home_icon: home
    property alias boiler_icon: boiler
    property alias setting_icon: setting
    property alias d3d_icon: d3d
    Image {

        anchors.fill: parent
        source: "images/abstract-luxury-plain-blur-grey-black-gradient-used-as-background-studio-wall-display-your-products.jpg"
    }

    Rectangle {
        id: rectangle
        width: row.width*1.1
        height: row.height*1.5
        color: "#40ffffff"
        radius: width * 0.05
        border.color: "#80ffffff"
        anchors.centerIn: parent


        Row {
            id:row
            anchors.centerIn: parent

            spacing: icon_size / 10
            Icon {
                id: home
                i_size: icon_size
                i_img: "images/home.png"

            }
            Icon {
                id: boiler
                i_size: icon_size
                i_img: "images/boiler.png"
            }
            Icon {
                id: setting
                i_size: icon_size
                i_img: "images/settings.png"
            }
            Icon {
                id: d3d
                i_size: icon_size
                i_img: "images/P3d.png"
            }
        }
    }
}
