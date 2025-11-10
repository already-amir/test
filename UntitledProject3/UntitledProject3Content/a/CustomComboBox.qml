import QtQuick
import QtQuick.Controls
import FresnelDemo

ComboBox {
    id: root
    width: 120
    height: 24

    delegate: ItemDelegate {
        id: delegate
        width: root.width
        height: root.height

        required property var model
        required property int index

        contentItem: Text {
            width: root.width
            height: root.height
            verticalAlignment: Text.AlignVCenter
            text: delegate.model[root.textRole]
            color: highlighted ? Constants.textColor : boxText.color
        }
        highlighted: root.highlightedIndex === index

        background: Rectangle {
            color: highlighted ? Constants.controlColor : Constants.backgroundColor
        }
    }

    indicator: Image {
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        source: "images/downArrow.svg"
    }

    contentItem: Text {
        id: boxText
        width: root.width
        height: root.height
        leftPadding: 10
        text: root.displayText
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: root.width
        implicitHeight: root.height
        border.color: root.hovered ? Constants.controlBorderLightColor : Constants.controlBorderColor
    }
}
