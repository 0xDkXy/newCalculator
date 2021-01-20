import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    id: window
    width: 320
    height: 480
    visible: true
    title: qsTr("Calculator")

    Rectangle {
        id: choseItem // 选择菜单
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 10
        color: "white"
        Button {
            id: calcItem
            x: 0
            y: 0
//            color: "red"
            anchors.left: parent.left
            width: parent.width / 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: "计算器"
            onClicked: {
                console.log("点击计算器")
                calculate.visible = true
                tree.visible = false
            }
        }
        Button {
            id: treeItem
//            color: "blue"
            x: parent.width / 2
            y: 0
            anchors.right: parent.right
            width: parent.width / 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: "表达式树"
            onClicked: {
                console.log("点击树")
                calculate.visible = false
                tree.visible = true
            }
        }
    }

    Rectangle {
        id: calculate
        visible: true
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: choseItem.top
        color: "white"

        //组件

        //表达式文本框
        Rectangle {
            id: resultArea
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: parent.height * 3 / 8 - 10
            border.color: "white"
            border.width: 1
            color: "#46a2da"
    //        Text {
    //            id: resultText
    //            text: "0"
    //            color: "white"
    ////            anchors.leftMargin: buttons.implicitMargin
    ////            anchors.rightMargin: buttons.implicitMargin
    //            anchors.fill: parent
    //            horizontalAlignment: Text.AlignRight
    //            verticalAlignment: Text.AlignVCenter
    //            font.pixelSize: window.height * 3 / 32
    //            font.family: "Open Sans Regular"
    //            fontSizeMode: Text.Fit
    //        }
            TextInput {
                id: resultText
                text: ""
                color: "white"
                //            anchors.leftMargin: buttons.implicitMargin
                //            anchors.rightMargin: buttons.implicitMargin
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: window.height * 3 / 32
                font.family: "Open Sans Regular"


    //                        fontSizeMode: Text.Fit
            }
        }

        //输入button
        Item {
            id: button
            anchors.top: resultArea.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            //Repeater 操作符
            Repeater {
                id: operations//操作符
                model: ["÷", "×", "+", "-"]
    //            property string operation: ["÷", "×", "+", "-"]
                Button {
                    y: 0
                    x: index * width
                    width: parent.width / 4
                    height:  parent.height / 5
                    color: pressed ? "#5caa15" : "#80c342"
                    text: modelData
                    fontHeight: 0.4
                    onClicked: {
                        if (modelData == "÷") resultText.text += '/'
                        else if (modelData == "×") resultText.text += '*'
                        else resultText.text += modelData
                    }
                }
            }

            // 数字
            Repeater {
                id: digits
                model: ["7", "8", "9", "4", "5", "6", "1", "2", "3", "0", ".", "C"]
                Button {
                    x: (index % 3) * width
                    y: Math.floor(index / 3 + 1) * height
                    width: parent.width / 4
                    height: parent.height / 5
                    color: pressed ? "#d6d6d6" : "#eeeeee"
                    text: modelData
                    onClicked: {
                        switch(modelData)
                        {
                        case "C":
                            resultText.text = ""
                            clean()
                            break;
                        default:
                            resultText.text = resultText.text + modelData
                            break;
                        }

    //                    console.log("点击树")
                    }
                }
            }
            //左括号
            Button {
                id: leftk
                y: parent.height / 5
                x: 3 * width
                width: parent.width / 4
                height:  parent.height / 5
                color: pressed ? "#5caa15" : "#80c342"
                text: "("
                fontHeight: 0.4
                onClicked: {
                    resultText.text += text
                }
            }
            //左括号
            Button {
                id: rightk
                y: (parent.height / 5) * 2
                x: 3 * width
                width: parent.width / 4
                height:  parent.height / 5
                color: pressed ? "#5caa15" : "#80c342"
                text: ")"
                fontHeight: 0.4
                onClicked: {
                    resultText.text += text
                }
            }
            // 操作符=
            Button {
                id: resultButton
                x: 3 * width
                y: (parent.height / 5) * 3
                textHeight: y - 50
                fontHeight: 0.4
                width: parent.width / 4
                height: (parent.height / 5) * 2
                color: pressed ? "#e0b91c" : "#face20"
                text: "="
                onClicked: {
//                    operations.itemAt(2).visible = false

                    expTree.setExpression(resultText.text)
                    if(expTree.isRight()){
                        resultText.text = expTree.getExpression()
                        var headNode = expTree.getHead()
                        for(var i=0 ; i < 3; i++) {
                            expression.itemAt(i).text += expTree.getExp()
                        }

                        showTree(headNode, 1, 160, 50)
                    }else{
                        resultText.text = "表达式错误"
                    }
                }
            }

        }
    }

    // tree
    Rectangle {
        id: tree
        visible: false
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: choseItem.top
        color: "white"
//        TreeNode {
//            x: 100
//            y: 100
//            id: node0
//            textHeight: y - 2
//            fontHeight: 0.4
//            width: 30
//            height: 30
//            text: "lhy"
//        }
        Repeater {
            id: expression
            model: ["前缀:", "中缀:", "后缀:"]
            Button {
                visible: true
//                color: "black"
                x: 0
                y: parent.height-(parent.height/20)*(index+1)
                height: 10
                width: 320
                textHeight: 0
//                fontHeight: 0.5
                text: modelData
            }
        }

        Repeater {
            id: linel
            model: 3010
//            property point pointLeftUp: Qt.point(x1,y1)
//            property point pointRightUp: Qt.point(x1+30,y1+30)
            Rectangle {//模拟线段
               visible: false
               width:42 //长
               height:1  //高
               color:"red" //颜色
               rotation:-45 //顺时针旋转的角度
            }
        }
        Repeater {
            id: liner
            model: 3010
//            property point pointLeftUp: Qt.point(x1,y1)
//            property point pointRightUp: Qt.point(x1+30,y1+30)
            Rectangle {//模拟线段
               visible: false
               width:42 //长
               height:1  //高
               color:"red" //颜色
               rotation:45 //顺时针旋转的角度
            }
        }

        Repeater {
            id: node
            model: 3010
            TreeNode {
                visible: false
                x:100
                y:100
                textHeight: y - 2
                fontHeight: 0.4
                width: 30
                height: 30
                text: "NULL"
            }
        }

    }
    function showTree(tRoot, index, x1, y1)
    {
        console.log(tRoot)
        node.itemAt(index).visible = true
        node.itemAt(index).x = x1
        node.itemAt(index).y = y1
        expTree.setHead(tRoot)
        node.itemAt(index).text = expTree.getVal()
        var lson = expTree.getLson();
        if(lson != 0){
            showTree(lson, index*2, x1-30, y1+30)
            linel.itemAt(index).x = (x1+x1-30)/2
            linel.itemAt(index).y = (y1+y1+30)/2
            linel.itemAt(index).visible = true
//            line.itemAt(index).rotation = 315
        }
        expTree.setHead(tRoot)
        var rson = expTree.getRson();
        if(rson != 0){
            showTree(rson, index*2+1, x1+30, y1+30)
            liner.itemAt(index).x = (x1+x1+30)/2
            liner.itemAt(index).y = (y1+y1+46)/2
            liner.itemAt(index).visible = true
        }

//        expTree.setRoot(tRoot)
//        node.itemAt(index).text = expTree.getVal()
        /*
        var lson = expTree.getLson();
        if(lson != 0) {
            showTree(lson, index*2);
        }
        expTree.setRoot(tRoot)
        var rson = expTree.getRson();
        if(rson != 0) {
            showTree(rson, index*2+1);
        }
        */
    }

    function clean()
    {
        for(var i = 0; i < 3010; i++){
            node.itemAt(i).visible = false
            liner.itemAt(i).visible = false
            linel.itemAt(i).visible = false
        }
        var strA=["前缀:", "中缀:", "后缀:"]

        for(var i = 0; i < 3; ++i) {
            expression.itemAt(i).text = strA[i];
        }

        expTree.clean();
    }
}
