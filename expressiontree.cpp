#include "expressiontree.h"
#include <QDebug>

expressionTree::expressionTree()
{
    memset(node,0,sizeof(node));
    memset(item, 0, sizeof(item));
    tot = 0;
}

void expressionTree::setExpression(QString getExp)
{
    exp = getExp.toStdString();
    expLen = exp.size();
    init();
    if (!_isRight()) {
        exp = "ERROR";
        qDebug() << QString::fromStdString(exp);
        return;
    }
    analyse();
    head = build_tree(0, cnt);
    ans = calc(1);
    exp = ans.toString();
    s = "";
    PreOrder(1);
    qDebug() << s;
    s = "";
    InOrder(1);
    qDebug() << s;
    s = "";
    PostOrder(1);
    qDebug() << s;
    //solveExp();
}

void expressionTree::init()
{
    cnt = 0;
    nodeNum = 0;
    for (int i = 0; i < 1010; ++i)
        item[i].digital0 = bigInteger();
    for (int i = 0; i < 1020; ++i)
        node[i].dig0 = bigInteger();
}

QString expressionTree::getExpression()
{
    return QString::fromStdString(exp);
}

bool expressionTree::isRight()
{
    return _right;
}

// 判断表达式是否正确
bool expressionTree::_isRight()
{
    int flag = 0;
    while (!operation.empty()) operation.pop();
    int lenExp = expLen;
    for (int i = 0; i < lenExp; ++i) {
//        qDebug() << exp[i] <<" " << isdigit(exp[i]) << "\n" << flag;
        if (!isdigit(exp[i])) {
            if (exp[i] == '(') {
                operation.push(exp[i]);
                continue;
            }
            if (exp[i] == ')') {
                if (!operation.empty()) {
                    operation.pop();
                    continue;
                } else {
                    flag = 1;
                    break;
                }
            }
//            qDebug() << exp[i + 1];
            if ((!isdigit(exp[i + 1]))
                    && (exp[i + 1] != '(' || exp[i + 1] != ')')) {
                    flag = 1;
                    break;
            }
        }
    }
    if (flag) {
        _right = 0;
        return false;

    }
    _right = 1;
    return true;
}

void expressionTree::analyse()
{
    int len = exp.size();
    int i = 0;
    std::string digit = "";
    while (i < len) {
        if (!isdigit(exp[i])) {
            item[cnt].alpha = exp[i++];
            item[cnt++].isAlpha = true;
        } else {
            digit.clear();
            while (isdigit(exp[i])) {
                digit += exp[i];
                i++;
            }
            item[cnt].digital0 = bigInteger(digit);
            item[cnt++].isAlpha = false;
        }
    }
}

int expressionTree::build_tree(int x, int y)
{
    int c1 = -1, c2 = -1, p = 0;
    int u;
    if (y - x == 0) return 0;
    if (y - x == 1) {
        u = ++ nodeNum;
        node[u].lson = node[u].rson = 0;
        if (item[x].isAlpha) {
            node[u].isAlpha = true;
            node[u].ope = item[x].alpha;
        } else {
            node[u].isAlpha = false;
            node[u].dig0 = item[x].digital0;
        }
        return u;
    }

    //寻找根节点位置
    for (int i = x; i <y; ++i) {
        if (item[i].isAlpha && item[i].alpha == '(') p++;
        if (item[i].isAlpha && item[i].alpha == ')') p--;
        if (item[i].isAlpha && (item[i].alpha == '+' || item[i].alpha == '-'))
            if (!p) c1 = i;
        if (item[i].isAlpha && (item[i].alpha == '*' || item[i].alpha == '/'))
            if (!p) c2 = i;
    }
    if (c1 < 0)
        c1 = c2;
    if (c1 < 0)
        return build_tree(x + 1, y - 1);
    u = ++nodeNum;
    node[u].lson = build_tree(x, c1);
    node[u].rson = build_tree(c1 + 1, y);
    if (item[c1].isAlpha) {
        node[u].isAlpha = true;
        node[u].ope = item[c1].alpha;
    } else {
        node[u].isAlpha = false;
        node[u].dig0 = item[c1].digital0;
    }
    return u;
}

/*
void expressionTree::solveExp()
{

//    exp = '#' + exp + '#';
//    int len = exp.size();
//    std::string digital;

//    for (int i = 0; i < len; ++i) {
//        if (exp[i] == '#' || exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '(' || exp[i] == ')') {
//            // 如果是操作符的进行的操作
//            if (digital.size()) {
//                digitals.push(bigInteger(digital));
//                //创建一个结点放进结点栈
//                treeNode[++tot].id = tot;
//                treeNode[tot].lson = treeNode[tot].rson = 0;
//                treeNode[tot].dig0 = bigInteger(digital);
//                expNode.push(treeNode[tot]);
//            }
//            digital.clear();
//            // 操作符不是(),判断+-* /优先级,然后按优先级压栈
//            if (exp[i] != '(' && exp[i] != ')')
//                if (operation.empty()) {
//                    operation.push(exp[i]);
//                    continue;
//                }
//                else {
//                    while (cmp(operation.top(), exp[i])) {
//                        treeNode[++tot].id = tot;
//                        treeNode[tot].ope = operation.top();
//                        treeNode[tot].lson = treeNode[tot].rson = 0;
//                        treeNode[tot].rson = expNode.top().id;
//                        expNode.pop();
//                        treeNode[tot].lson = expNode.top().id;
//                        expNode.pop();
//                        expNode.push(treeNode[tot]);
//                        //                    operation.pop();
//                        bigInteger a, b, c;
//                        switch (operation.top()) {
//                        case '+':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = a + b;
//                            digitals.push(c);
//                            break;
//                        case '-':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = b - a;
//                            digitals.push(c);
//                            break;
//                        case '*':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = a * b;
//                            digitals.push(c);
//                            break;
//                        case '/':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = b / a;
//                            digitals.push(c);
//                            break;
//                        default:
//                            break;
//                        }
//                        operation.pop();
//                    }
//                }
//            else {
//                //)一直压栈直到遇到(,然后从continue把()扔了
//                if (exp[i] == ')') {
//                    while (operation.top() != '(') {
//                        treeNode[++tot].id = tot;
//                        treeNode[tot].ope = operation.top();
//                        treeNode[tot].lson = treeNode[tot].rson = 0;
//                        treeNode[tot].rson = expNode.top().id;
//                        expNode.pop();
//                        treeNode[tot].lson = expNode.top().id;
//                        expNode.pop();
//                        expNode.push(treeNode[tot]);
//                        bigInteger a, b, c;
//                        switch (operation.top()) {
//                        case '+':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = a + b;
//                            digitals.push(c);
//                            break;
//                        case '-':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = b - a;
//                            digitals.push(c);
//                            break;
//                        case '*':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = a * b;
//                            digitals.push(c);
//                            break;
//                        case '/':
//                            a = digitals.top(); digitals.pop();
//                            b = digitals.top(); digitals.pop();
//                            c = b / a;
//                            digitals.push(c);
//                            break;
//                        default:
//                            break;
//                        }
//                        operation.pop();
//                    }
//                    operation.pop();
//                    continue;
//                }
//            }
//            operation.push(exp[i]);
//        }
//        else {
//            // 不是操作符进行的操作
//            digital += exp[i];
//        }
//    }

//    if (digitals.size() != 1) {
//        exp = "error";
//    }
//    else {
//        head = expNode.top().id;
//        exp = digitals.top().toString();
//    }
//    while(!operation.empty()) operation.pop();
//    while(!digitals.empty()) digitals.pop();
}
*/

int expressionTree::getHead() {return head;}

QString expressionTree::getVal()
{
//    node[head].toStr();
//    return QString::fromStdString(node[head].val);
    std::string tmpStr = "";
    if (node[head].isAlpha) {
        tmpStr += node[head].ope;
    } else {
        tmpStr += node[head].dig0.toString();
    }
    return QString::fromStdString(tmpStr);
}

void expressionTree::setHead(int root) { head = root; }

int expressionTree::getLson() { return node[head].lson; }

int expressionTree::getRson() { return node[head].rson; }

//先序遍历
void expressionTree::PreOrder(int root)
{
//    node[root].toStr();
//    s += QString::fromStdString(node[root].val);
    if (node[root].isAlpha) {
        s += node[root].ope;
    } else {
        s += QString::fromStdString(node[root].dig0.toString());
    }
    if (node[root].lson > 0) PreOrder(node[root].lson);
    if (node[root].rson > 0) PreOrder(node[root].rson);
}

//中序遍历
void expressionTree::InOrder(int root)
{
    if (node[root].lson > 0) InOrder(node[root].lson);
//    node[root].toStr();
//    s += QString::fromStdString(node[root].val);
    if (node[root].isAlpha) {
        s += node[root].ope;
    } else {
        s += QString::fromStdString(node[root].dig0.toString());
    }
    if (node[root].rson > 0) InOrder(node[root].rson);
}

//后序遍历
void expressionTree::PostOrder(int root)
{
    if (node[root].lson > 0) PostOrder(node[root].lson);
    if (node[root].rson > 0) PostOrder(node[root].rson);
//    node[root].toStr();
//    s += QString::fromStdString(node[root].val);
    if (node[root].isAlpha) {
        s += node[root].ope;
    } else {
        s += QString::fromStdString(node[root].dig0.toString());
    }
}

bigInteger expressionTree::calc(int root)
{
    bigInteger tmpAns = bigInteger();
    if (!node[root].isAlpha) {
        tmpAns =  node[root].dig0;
        return tmpAns;
    }
    char ch = node[root].ope;
    bigInteger a = bigInteger(), b = bigInteger();
    a = calc(node[root].lson), b = calc(node[root].rson);
    switch (ch) {
    case '+':
        tmpAns = a + b;
        break;
    case '-':
        tmpAns = a - b;
        break;
    case '*':
//        tmpAns = a * b;
        tmpAns = fft_mul(a, b);
        break;
    case '/':
        tmpAns = a / b;
        break;
    default:
        break;
    }
    return tmpAns;
}

QString expressionTree::getExp()
{
    s = "";
    if(flag == 0){
        PreOrder(1);
    }else if(flag == 1){
        InOrder(1);
//        flag=2;
    }else if(flag == 2){
        PostOrder(1);
//        flag=0;
    }
    flag++;
    if(flag>=3) flag=0;
    return s;
}
