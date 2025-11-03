import QtQuick

Window {

    Item{
        id: variable
        property int main_win_width: 1280
        property int main_win_heights: 720
        property int n: 5
        property int m: 3

    }

    width: variable.main_win_width
    height: variable.main_win_heights
    visible: true
    title: qsTr("personal assistent")


    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width/variable.n

        spacing: parent.height * 0.05



        Rectangle{


            height: parent.height/variable.m
            width: parent.width
            color:"red"
            Text {
                text: qsTr("chat GPT")
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    Qt.openUrlExternally("https://chatgpt.com/")
                }
            }
            Image {
                anchors.fill: parent
                source: "openai.png"
            }
        }

        Rectangle{

            height: parent.height/variable.m
            width: parent.width
            color:"blue"
            Text {
                text: qsTr("CALENDER")
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    Qt.openUrlExternally("https://calendar.google.com/calendar/u/0/r?pli=1")
                }
            }
        }

        Rectangle{

            height: parent.height/variable.m
            width: parent.width
            color:"yellow"
            Text {
                text: qsTr("TICK TICK")
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    Qt.openUrlExternally("https://ticktick.com/?language=en_US")
                }
            }
        }

    }



}
