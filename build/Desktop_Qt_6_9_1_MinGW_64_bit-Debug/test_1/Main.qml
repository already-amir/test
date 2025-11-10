import QtQuick
import "."
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
    color: "#000000"
    title: qsTr("personal assistent")


    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width/variable.n

        spacing: parent.height * 0.05



        App{
            app_img: "qrc:/res/img/openai.png"
            app_txt: "CHAT GPT"
            app_url: "https://chatgpt.com/"
        }

        App{
            app_img: "qrc:/res/img/openai.png"
            app_txt: "CALENDER"
            app_url: "file:///C:/Program Files/Arduino IDE.exe"
        }

        App{
            app_img: "qrc:/res/img/TickTick.png"
            app_txt: "TICK TICK"
            app_url: "https://ticktick.com/?language=en_US/"
        }






    }



}
