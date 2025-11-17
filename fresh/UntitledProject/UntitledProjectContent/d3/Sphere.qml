import QtQuick
import QtQuick.Controls
import QtQuick3D

Model {
    property real angle
    x: Math.cos(angle) * 333
    z: Math.sin(angle) * 333
    source: "#Sphere"
    castsReflections: true
    receivesReflections: true
    receivesShadows: true
    usedInBakedLighting: false
    materials: greenMaterial

    Node {
        id: __materialLibrary__
    }

    NumberAnimation on angle {
        from: 0
        to: Math.PI * 2
        duration: 20000
        loops: Animation.Infinite
    }
}
/*##^##
Designer {
    D{i:0;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/
