

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Effects
import QtQuick3D.Helpers

import QtQuick.Timeline 1.0


Rectangle {
    id: root
    signal clicked()
    width: 100
    height: 100
    color: Constants.backgroundColor
    property alias exitButton_icon: exitButton

    View3D {
        id: view3D
        width: parent.width - controls.width
        height: parent.height
        anchors.right: parent.right
        environment: sceneEnvironment
        camera: sceneCamera

        SceneEnvironment {
            id: sceneEnvironment
            backgroundMode: SceneEnvironment.SkyBox
            probeOrientation.y: controls.skyBoxRotation
            clearColor: "#111111"
            lightProbe: royal_esplanade_4k
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
            }

            Model {
                id: monkeyModel
                materials: monkeyMaterial
                source: "suzanne.mesh"
                castsReflections: true
                receivesReflections: true
                scale.y: 100
                scale.z: 100
                scale.x: 100

                ReflectionProbe {
                    quality: controls.detailLevel
                    parallaxCorrection: true
                    boxSize.x: 10000
                    boxSize.y: 10000
                    boxSize.z: 10000
                }
            }

            Node {
                id: cameraNode
                PerspectiveCamera {
                    id: sceneCamera
                    z: 450
                }
            }

            Sphere {
                id: sphere
                ReflectionProbe {
                    quality: controls.detailLevel
                    parallaxCorrection: true
                    boxSize.x: 10000
                    boxSize.y: 10000
                    boxSize.z: 10000
                }
            }

            Model {
                id: mirror
                z: -750
                source: "#Cube"
                eulerRotation.y: 90
                castsReflections: true
                scale.z: 10
                scale.y: 10
                scale.x: 0.01
                receivesReflections: true
                materials: mirrorMaterial

                ReflectionProbe {
                    quality: controls.detailLevel
                    parallaxCorrection: true
                    boxSize.x: 10000
                    boxSize.y: 10000
                    boxSize.z: 10000
                }
            }
        }

        ArcballController {
            id: arcballController
            controlledObject: monkeyModel
        }

        DragHandler {
            id: dragHandler
            target: null
            acceptedButtons: Qt.RightButton
            enabled: !controls.moveModel
        }

        Connections {
            target: dragHandler
            onCentroidChanged: {
                arcballController.mouseMoved(
                            toNDC(dragHandler.centroid.position.x,
                                  dragHandler.centroid.position.y))
            }

            onActiveChanged: {
                if (dragHandler.active) {
                    view3D.forceActiveFocus()
                    arcballController.mousePressed(
                                toNDC(dragHandler.centroid.position.x,
                                      dragHandler.centroid.position.y))
                } else
                    arcballController.mouseReleased(
                                toNDC(dragHandler.centroid.position.x,
                                      dragHandler.centroid.position.y))
            }

            function toNDC(x, y) {
                return Qt.vector2d((2.0 * x / width) - 1.0,
                                   1.0 - (2.0 * y / height))
            }
        }

        MouseRotatorAndWASD {
            x: 0
            y: -1
            controlledObject: controls.moveModel ? monkeyModel : cameraNode
            xInvert: false
            yInvert: true
            focus: controls.moveModel || !controls.moveModel
        }
    }

    FresnelControls {
        id: controls
        width: 300
        height: parent.height
        source: view3D
    }

    DebugView {
        source: view3D
        anchors.right: parent.right
        resourceDetailsVisible: true
        opacity: 0
    }

    CustomButton {
        id: exitButton
        width: 32
        height: 32
        bgColor: pressed ? Constants.controlColor : Constants.controlBgColor
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10





        Image {
            id: closeIcon
            anchors.centerIn: parent
            source: "images/closeIcon.svg"
        }
    }

    Item {
        id: __materialLibrary__

        Texture {
            id: royal_esplanade_4k
            source: "images/royal_esplanade_4k.hdr"
        }

        PrincipledMaterial {
            id: monkeyMaterial
            metalness: controls.monkeyMetalness
            clearcoatFresnelBias: controls.fresnelBias
            clearcoatFresnelScaleBiasEnabled: true
            clearcoatFresnelScale: controls.fresnelScale
            clearcoatFresnelPower: controls.fresnelPower
            clearcoatAmount: controls.fresnelAmount
            vertexColorsEnabled: false
            objectName: "Monkey Material"
            baseColor: "#ffee00"
        }

        PrincipledMaterial {
            id: greenMaterial
            metalness: controls.sphereMetalness
            baseColor: "#00ff58"
            objectName: "Green Material"
            clearcoatFresnelBias: controls.fresnelBias
            clearcoatFresnelScaleBiasEnabled: true
            clearcoatFresnelScale: controls.fresnelScale
            clearcoatFresnelPower: controls.fresnelPower
            clearcoatAmount: controls.fresnelAmount
        }


    }
}

/*##^##
Designer {
    D{i:0;matPrevEnvDoc:"SkyBox";matPrevEnvValueDoc:"preview_studio";matPrevModelDoc:"#Sphere"}
D{i:1;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}D{i:3;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/

