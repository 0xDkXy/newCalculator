#include "expressiontree.h"

expressionTree::expressionTree()
{
    memset(treeNode,0,sizeof(treeNode));
    tot = 0;
}

void expressionTree::setExpression(QString getExp)
{
    exp = getExp.toStdString();
    solveExp();
}

QString expressionTree::getExpression()
{
    return QString::fromStdString(exp);
}

bool expressionTree::isRight()
{
    return true;
}

int prio(char x)
{
    switch (x) {
        case '+':
            return 2;
            break;
        case '-':
            return 2;
            break;
        case '*':
            return 3;
            break;
        case '/':
            return 3;
            break;
//        case '(':
//            return 1;
//            break;
//        case ')':
//            return 1;
            break;
        default:
            return 0;

    }
}

bool cmp(char a, char b) { return prio(b)<prio(a); }

void expressionTree::solveExp()
{
    exp = '#' + exp + '#';
    int len = exp.size();
    std::string digital;

    for (int i = 0; i < len; ++i) {
        if (exp[i] == '#' || exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '(' || exp[i] == ')') {
            // 如果是操作符的进行的操作
            if (digital.size()) {
                digitals.push(bigInteger(digital));
                //创建一个结点放进结点栈
                treeNode[++tot].id = tot;
                treeNode[tot].lson = treeNode[tot].rson = 0;
                treeNode[tot].dig0 = bigInteger(digital);
                expNode.push(treeNode[tot]);
            }
            digital.clear();
            // 操作符不是(),判断+-* /优先级,然后按优先级压栈
            if (exp[i] != '(' && exp[i] != ')')
                if (operation.empty()) {
                    operation.push(exp[i]);
                    continue;
                }
                else {
                    while (cmp(operation.top(), exp[i])) {
                        treeNode[++tot].id = tot;
                        treeNode[tot].ope = operation.top();
                        treeNode[tot].lson = treeNode[tot].rson = 0;
                        treeNode[tot].rson = expNode.top().id;
                        expNode.pop();
                        treeNode[tot].lson = expNode.top().id;
                        expNode.pop();
                        expNode.push(treeNode[tot]);
                        //                    operation.pop();
                        bigInteger a, b, c;
                        switch (operation.top()) {
                        case '+':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = a + b;
                            digitals.push(c);
                            break;
                        case '-':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = b - a;
                            digitals.push(c);
                            break;
                        case '*':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = a * b;
                            digitals.push(c);
                            break;
                        case '/':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = b / a;
                            digitals.push(c);
                            break;
                        default:
                            break;
                        }
                        operation.pop();
                    }
                }
            else {
                //)一直压栈直到遇到(,然后从continue把()扔了
                if (exp[i] == ')') {
                    while (operation.top() != '(') {
                        treeNode[++tot].id = tot;
                        treeNode[tot].ope = operation.top();
                        treeNode[tot].lson = treeNode[tot].rson = 0;
                        treeNode[tot].rson = expNode.top().id;
                        expNode.pop();
                        treeNode[tot].lson = expNode.top().id;
                        expNode.pop();
                        expNode.push(treeNode[tot]);
                        bigInteger a, b, c;
                        switch (operation.top()) {
                        case '+':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = a + b;
                            digitals.push(c);
                            break;
                        case '-':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = b - a;
                            digitals.push(c);
                            break;
                        case '*':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = a * b;
                            digitals.push(c);
                            break;
                        case '/':
                            a = digitals.top(); digitals.pop();
                            b = digitals.top(); digitals.pop();
                            c = b / a;
                            digitals.push(c);
                            break;
                        default:
                            break;
                        }
                        operation.pop();
                    }
                    operation.pop();
                    continue;
                }
            }
            operation.push(exp[i]);
        }
        else {
            // 不是操作符进行的操作
            digital += exp[i];
        }
    }

    if (digitals.size() != 1) {
        exp = "error";
    }
    else {
        head = expNode.top().id;
        exp = digitals.top().toString();
    }
    while(!operation.empty()) operation.pop();
    while(!digitals.empty()) digitals.pop();
}

int expressionTree::getHead() {return head;}

QString expressionTree::getVal()
{
    treeNode[head].toStr();
    return QString::fromStdString(treeNode[head].val);
}

void expressionTree::setHead(int root) { head = root; }

int expressionTree::getLson() { return treeNode[head].lson; }

int expressionTree::getRson() { return treeNode[head].rson; }

QString expressionTree::getExp()
{
    s = "";
    if(flag == 0){
        dfs0(head);
    }else if(flag == 1){
        dfs1(head);
//        flag=2;
    }else if(flag == 2){
        dfs2(head);
//        flag=0;
    }
    flag++;
    if(flag>=3) flag=0;
    return s;
}

void expressionTree::dfs0(int root)
{
    treeNode[root].toStr();
    s += QString::fromStdString(treeNode[root].val);
    if(treeNode[root].lson){
        dfs0(treeNode[root].lson);
    }
    if(treeNode[root].rson){
        dfs0(treeNode[root].rson);
    }
}

void expressionTree::dfs1(int root)
{

    if(treeNode[root].lson){
        dfs1(treeNode[root].lson);
    }
    treeNode[root].toStr();
    s += QString::fromStdString(treeNode[root].val);
    if(treeNode[root].rson){
        dfs1(treeNode[root].rson);
    }
}

void expressionTree::dfs2(int root)
{

    if(treeNode[root].lson){
        dfs2(treeNode[root].lson);
    }
    if(treeNode[root].rson){
        dfs2(treeNode[root].rson);
    }
    treeNode[root].toStr();
    s += QString::fromStdString(treeNode[root].val);
}

void expressionTree::clean()
{
    tot = head = flag = 0;
    while(!operation.empty()) operation.pop();
    while(!digitals.empty()) digitals.pop();
    while(!expNode.empty()) expNode.pop();
    exp.clear();
}
