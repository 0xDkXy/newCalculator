#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <QObject>
#include <QString>
#include <string>
#include "biginteger.h"
#include <stack>

class expressionTree : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ getExpression WRITE setExpression)
    Q_PROPERTY(bool value READ isRight)
    Q_PROPERTY(int value READ getHead)
    Q_PROPERTY(QString value READ getVal)
    Q_PROPERTY(int value WRITE setHead)
    Q_PROPERTY(int value READ getLson)
    Q_PROPERTY(int value READ getRson)
    Q_PROPERTY(QString value READ getExp)
//    Q_PROPERTY(void value READ clean)

public:
    expressionTree();
    //node
    struct node{
        bigInteger dig0 = bigInteger();
        double dig1 = 0;
        int x,y,id,lson,rson;
        char ope = '?';
        std::string val = "";
        void toStr()
        {
            val.clear();
            if (ope != '?') val += ope;
            else val = dig0.toString();
        }
    };
    node *treeNode = new node[3010];
    int tot,head;
    int flag = 0;
    Q_INVOKABLE void setExpression(QString getExp);
    Q_INVOKABLE QString getExpression();
    Q_INVOKABLE bool isRight();
    Q_INVOKABLE int getHead();
    Q_INVOKABLE QString getVal();
    Q_INVOKABLE void setHead(int root);
    Q_INVOKABLE int getLson();
    Q_INVOKABLE int getRson();
    Q_INVOKABLE QString getExp();
    Q_INVOKABLE void clean();

signals:


private:
    std::stack<char>operation;
    std::stack<bigInteger>digitals;
    std::stack<node>expNode;
    std::string exp;
    void solveExp();
    void dfs0(int root);
    void dfs1(int root);
    void dfs2(int root);
    QString s;
};

#endif // EXPRESSIONTREE_H
