// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import FresnelDemo

Window {
    width: Constants.width
    height: Constants.height

    visible: true
    title: "Fresnel Demo"

    Screen01 {
        id: mainScreen
        anchors.fill: parent
    }
}
