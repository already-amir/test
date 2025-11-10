import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick3D.Helpers.impl
import FresnelDemo

Rectangle {
    id: root
    color: Constants.controlBgColor
    property var source: null
    property int detailLevel: detailComboBox.currentIndex
    property alias fresnelAmount: fresnelAmount.value
    property alias fresnelPower: fresnelPower.value
    property alias fresnelScale: fresnelScale.value
    property alias fresnelBias: fresnelBias.value
    property alias mirrorRoughness: mirrorRoughness.value
    property alias skyBoxRotation: skyBoxRotation.value
    property alias sphereMetalness: sphereMetalness.value
    property alias monkeyMetalness: monkeyMetalness.value
    property alias moveModel: modeSwitch.position

    width: 300
    height: 640

    Column {
        id: modelInfo
        width: parent.width
        height: parent.height / 5
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        visible: parent.height > 1000
        spacing: 5

        Text {
            text: qsTr("MODEL INFO")
            color: Constants.textColor
            font.pixelSize: 20
            font.bold: true
        }

        Item {
            width: parent.width
            height: 5
        }

        RenderStatsMeshesModel {
            id: meshModel
            meshData: root.source.renderStats.meshDetails
        }

        HorizontalHeaderView {
            syncView: tableView
            resizableColumns: false
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.VerticalFlick
            delegate: Text {
                text: display
                color: Constants.textColor
                visible: index === 0 || index === 2
            }
        }

        TableView {
            id: tableView
            width: parent.width
            height: contentHeight
            interactive: false
            model: meshModel
            columnSpacing: 1
            rowSpacing: 1
            delegate: Text {
                required property string display
                text: display
                color: Constants.textColor
                visible: column === 0 || column === 2
            }
        }

        Text {
            text: qsTr("RUNNING AT ") + root.source.renderStats.fps + qsTr(" FPS")
            color: Constants.textColor
        }
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: modelInfo.visible ? modelInfo.bottom : parent.top
        spacing: 7

        Text {
            text: qsTr("SCENE CONTROLS")
            color: Constants.textColor
            font.pixelSize: 20
            font.bold: true
        }

        Row {
            spacing: 10
            Text {
                height: 24
                text: qsTr("Reflection detail: ")
                color: Constants.textColor
                verticalAlignment: Text.AlignVCenter
            }

            CustomComboBox {
                id: detailComboBox
                currentIndex: 2
                model: [ qsTr("Very Low"), qsTr("Low"), qsTr("Medium"), qsTr("High"), qsTr("Very High") ]
            }
        }

        SliderText {
            sliderTitle: qsTr("Fresnel bias")
            sliderValue: fresnelBias.value.toFixed(3)
        }

        CustomSlider {
            id: fresnelBias
            from: -1
            to: 1
            value: -0.15
        }

        SliderText {
            sliderTitle: qsTr("Fresnel scale")
            sliderValue: fresnelScale.value.toFixed(3)
        }

        CustomSlider {
            id: fresnelScale
            from: 0
            to: 50
            value: 2.2
        }

        SliderText {
            sliderTitle: qsTr("Fresnel power")
            sliderValue: fresnelPower.value.toFixed(3)
        }

        CustomSlider {
            id: fresnelPower
            from: 0
            to: 10
            value: 0.7
        }

        SliderText {
            sliderTitle: qsTr("Fresnel amount")
            sliderValue: fresnelAmount.value.toFixed(3)
        }

        CustomSlider {
            id: fresnelAmount
            from: 0
            to: 100
            value: 1.2
        }

        SliderText {
            sliderTitle: qsTr("Mirror roughness")
            sliderValue: mirrorRoughness.value.toFixed(3)
        }

        CustomSlider {
            id: mirrorRoughness
            from: 0
            to: 1
            value: 0.1
        }

        SliderText {
            sliderTitle: qsTr("Rotate background")
            sliderValue: skyBoxRotation.value.toFixed(0)
        }

        CustomSlider {
            id: skyBoxRotation
            from: -360
            to: 360
            value: 0
        }

        SliderText {
            sliderTitle: qsTr("Monkey metalness")
            sliderValue: monkeyMetalness.value.toFixed(2)
        }

        CustomSlider {
            id: monkeyMetalness
            from: 0
            to: 1
            value: 1
        }

        SliderText {
            sliderTitle: qsTr("Sphere metalness")
            sliderValue: sphereMetalness.value.toFixed(2)
        }

        CustomSlider {
            id: sphereMetalness
            from: 0
            to: 1
            value: 1
        }

        RowLayout {
            height: 60
            width: parent.width
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Text {
                text: qsTr("Move camera")
                color: Constants.textColor
                opacity: modeSwitch.position ? 0.3 : 1
            }

            CustomSwitch {
                id: modeSwitch
            }

            Text {
                text: qsTr("Move model")
                color: Constants.textColor
                opacity: modeSwitch.position ? 1 : 0.3
            }
        }

        CustomButton {
            id: resetButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Reset fresnel")

            Connections {
                onClicked: {
                    fresnelBias.value = -0.15
                    fresnelScale.value = 2.2
                    fresnelPower.value = 0.7
                    fresnelAmount.value = 1.2
                }
            }
        }

        CustomButton {
            id: resetCameraButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Reset camera")

            Connections {
                onClicked: {
                    sceneCamera.position = "0, 0, 450"
                    sceneCamera.eulerRotation = "0, 0, 0"
                    sceneCamera.pivot = "0, 0, 0"
                    cameraNode.position = "0, 0, 0"
                    cameraNode.eulerRotation = "0, 0, 0"
                    cameraNode.pivot = "0, 0, 0"
                }
            }
        }

        CustomButton {
            id: resetMonkeyButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Reset monkey")

            Connections {
                onClicked: {
                    monkeyModel.position = "0, 0, 0"
                    monkeyModel.eulerRotation = "0, 0, 0"
                    monkeyModel.pivot = "0, 0, 0"
                }
            }
        }
    }

    Column {
        width: parent.width
        height: parent.height / 5
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        visible: parent.height > 800

        Text {
            id: titleText
            text: moveModel ? qsTr("MODEL CONTROLS") : qsTr("CAMERA CONTROLS")
            color: Constants.textColor
            font.pixelSize: 20
            font.bold: true
        }

        Item {
            id: filler
            width: parent.width
            height: 20
        }

        Row {
            width: parent.width
            height: parent.height - filler.height
            Text {
                width: parent.width / 3
                color: Constants.textColor
                visible: !moveModel
                text: qsTr("W or Up arrow\nA or Left arrow\nS or Down arrow\nD or Right arrow\nR or Page up\nF or Page down\nMouse 1\nMouse 2\nMouse wheel")
            }

            Text {
                width: parent.width / 3
                color: Constants.textColor
                visible: moveModel
                text: qsTr("W or Up arrow\nA or Left arrow\nS or Down arrow\nD or Right arrow\nR or Page up\nF or Page down\nMouse 1\nMouse wheel")
            }

            Text {
                width: 50
                color: Constants.textColor
                horizontalAlignment: Text.AlignHCenter
                visible: !moveModel
                text: qsTr("-\n-\n-\n-\n-\n-\n-\n-\n-")
            }

            Text {
                width: 50
                color: Constants.textColor
                horizontalAlignment: Text.AlignHCenter
                visible: moveModel
                text: qsTr("-\n-\n-\n-\n-\n-\n-\n-")
            }

            Text {
                width: parent.width / 3
                color: Constants.textColor
                visible: !moveModel
                text: qsTr("Move forward\nMove backwards\nMove left\nMove right\nMove up\nMove down\nRotate camera\nRotate model\nZoom in or out")
            }

            Text {
                width: parent.width / 3
                color: Constants.textColor
                visible: moveModel
                text: qsTr("Move forward\nMove backwards\nMove left\nMove right\nMove up\nMove down\nRotate model\nZoom in or out")
            }
        }
    }
}
