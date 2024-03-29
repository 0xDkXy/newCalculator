import QtQuick 2.0

Rectangle {
    id: treeNode
    signal clicked
    property alias text: text.text
    radius: 50
    border.width: 1
    border.color: "black"
    property real textHeight: height - 2
    property real fontHeight: 0.3
    property bool pressed: mouse.pressed
    property real implicitMargin: (width - text.implicitWidth) / 2

    Text {
        id: text
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        height: parent.textHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: height * fontHeight
        color: "#1b1c1d"
        font.family: "Open Sans Regular"
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: treeNode.clicked()
    }
}
