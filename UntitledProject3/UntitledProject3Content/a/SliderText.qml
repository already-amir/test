import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import FresnelDemo

RowLayout {
    id: root

    property alias sliderTitle: sliderTitle.text
    property alias sliderValue: sliderValue.text

    width: 280

    Text {
        id: sliderTitle
        color: Constants.textColor
    }

    Item {
        id: spacer
        Layout.fillWidth: true
    }

    Text {
        id: sliderValue
        color: Constants.textColor
    }
}
