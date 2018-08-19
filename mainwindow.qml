import QtQuick 2.0

Rectangle {
    id: mainWindow
    width: 400
    height: 300
    color: "black"
    antialiasing: true
    focus: true

    // Forward key input to controller
    signal keyPressed(int key)
    Keys.onPressed: keyPressed(event.key)

    Rectangle {
        height: 10
        width: 10
        color: "white"
    }

    Text {
        text: "Hello World!"
        color: "orange"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
