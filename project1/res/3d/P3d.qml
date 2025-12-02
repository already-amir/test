import QtQuick 2.15
import "../"
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15

Item{
    id:window
    Image {
        id: screenBackground
        anchors.fill: parent
        source: "../img/grc.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    Icon{
        id:exit
        i_size: parent.height * 0.2
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: parent.width *0.02
        anchors.topMargin: parent.height *0.02
        i_img: "img/ross.png"
        onClicked: pageLoader.source = "../Page_start.qml"
    }

    // GlassButton.qml

    /*
    Button {
        id: control
        width: 500
        height: 500
        padding: 0

        // --- Background (Glass) ---
        background: Item {
            id: bg
            width: control.width
            height: control.height
            layer.enabled: true

            // Blur پشت دکمه (شیشه واقعی)
            FastBlur {
                id: blur
                anchors.fill: parent
                radius: 32                 // شدت شیشه
                source: ShaderEffectSource {
                    sourceItem: control.parent
                    recursive: true
                    hideSource: false
                }
            }

            // لایه رنگ شیشه‌ای
            Rectangle {
                anchors.fill: parent
                radius: 12
                color: Qt.rgba(1, 1, 1, 0.15)   // شفاف
                border.color: Qt.rgba(1, 1, 1, 0.25)
                border.width: 1
            }

            // Highlight بالای دکمه
            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: parent.height * 0.28
                radius: 12
                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.rgba(1,1,1,0.45) }
                    GradientStop { position: 1.0; color: Qt.rgba(1,1,1,0.05) }
                }
            }
        }

        // --- متن ---
        contentItem: Text {
            text: control.text
            font.pixelSize: 16
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            opacity: control.enabled ? 1.0 : 0.4
        }

        // --- حالت‌ها ---
        states: [
            State {
                name: "pressed"
                when: control.down
                PropertyChanges { target: bg; scale: 0.95 }
                PropertyChanges { target: blur; radius: 18 }
            },
            State {
                name: "hovered"
                when: control.hovered
                PropertyChanges { target: bg; scale: 1.03 }
            }
        ]

        transitions: Transition {
            NumberAnimation { properties: "scale,radius"; duration: 120; easing.type: Easing.OutQuad }
        }
    }
*/

}


