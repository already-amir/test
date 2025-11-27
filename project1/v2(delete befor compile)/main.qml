Button {
    text: "Scan Wifi"
    onClicked: wifi.scan()
}

ListView {
    model: wifi.networks
    delegate: Text { text: modelData }
}
