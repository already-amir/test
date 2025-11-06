import QtQuick

Item {
    id: root_app
    property alias app_txt: app_name.text
    property alias app_img: app_image.source
    property alias app_url: app_clk.url
    signal clickk (string url )



    height: 150
    width: height
    Rectangle {
        anchors.fill: parent
        color: "#000000"

        Image {
            id: app_image
            height: parent.height * 0.8
            width: height
            anchors.centerIn: parent
            source: "qrc:/res/img/openai.png"
        }

        Text {
            id: app_name
            text: qsTr("chat GPT")
            color: "white"
            anchors.top: app_image.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea {
            id: app_clk
            anchors.fill: parent
            property string url: "https://chatgpt.com/"
            onClicked: root_app.clickk(url)
        }

        Component.onCompleted: {
            root_app.clickk.connect(back.open_url)
        }

    }
}
