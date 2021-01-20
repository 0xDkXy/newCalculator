import QtQuick 2.0

import QtQuick 2.2

Item {
    id:myLine
    property point point1: Qt.point(100,400)
    property point point2: Qt.point(240,200)

    property int lineWidth: 4
    property var lineColor: "#ffffff"

    Rectangle{
        id:line

        width: lineWidth
        color: lineColor
        transformOrigin: Item.TopLeft
        PropertyAnimation {
            id: propAni
            target: line
            property: "height"
            duration: 5000

        }

    }

    function draw() {
        var angle= 0
        var lineLength = Math.sqrt(Math.pow(point1.x - point2.x, 2) + Math.pow(point1.y - point2.y, 2))
        line.x = point2.x
        line.y = point2.y

        if(point1.y == point2.y) {
            if(point1.x <= point2.x) angle= 90
            else angle= 270
        }
        else if(point1.x == point2.x) {
            if(point1.y < point2.y) angle= 180
            else angle= 0
        }
        else {
            if(point1.x < point2.x && point1.y > point2.y) {
                angle= Math.atan((Math.abs((point1.x - point2.x)) / Math.abs((point1.y - point2.y)))) * 180 / Math.PI
            }

            else if(point1.x < point2.x && point1.y < point2.y) {

                angle = Math.atan((Math.abs((point1.y - point2.y)) / Math.abs((point1.x - point2.x)))) * 180 / Math.PI
                angle+= 90
            }
            else if(point1.x > point2.x && point1.y < point2.y) {

                jiaodu = Math.atan((Math.abs((point1.x - point2.x)) / Math.abs((point1.y - point2.y)))) * 180 / Math.PI
                angle+= 180
            }
            else if(point1.x > point2.x && point1.y > point2.y) {

                jiaodu = Math.atan((Math.abs((point1.y - point2.y)) / Math.abs((point1.x - point2.x)))) * 180 / Math.PI
                angle+= 270
            }
        }

        line.height = lineLength
        line.rotation = angle

        console.debug("line:", lineLength, angle)
    }

    onPoint1Changed: {
        draw()
    }

    onPoint2Changed: {
        draw()
    }

    Component.onCompleted: {
        draw()
    }
}
