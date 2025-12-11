import QtQuick 2.15
import QtQuick.Controls 2.15


import "../"

Item{
    Image {
        id: image
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

    Column {
            spacing: 10
            anchors.centerIn: parent

            TextField {
                id: topicInput
                placeholderText: "Topic"
            }

            TextField {
                id: messageInput
                placeholderText: "Message"
            }

            Button {
                text: "Connect"
                onClicked: {
                    mqttClient.connectToBroker("ws://192.168.0.29:5050/mqtt", "K6mntxTf9qUxYeUlpQOH")
                }
            }

            Button {
                text: "Publish"
                onClicked: {
                    mqttClient.publishMessage(topicInput.text, messageInput.text)
                }
            }

            Button {
                text: "Subscribe"
                onClicked: {
                    mqttClient.subscribeTopic(topicInput.text)
                }
            }

            ListView {
                id: msgList
                width: parent.width
                height: 150
                model: ListModel {}

                delegate: Text {
                    text: model.topic + ": " + model.message
                }
            }

            Connections {
                target: mqttClient
                onMessageReceived: {
                    msgList.model.append({"topic": topic, "message": message})
                }
            }
        }

}

