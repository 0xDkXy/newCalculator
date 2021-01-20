#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <QString>
#include <string>
#include <iostream>
#include <vector>

class bigInteger
{
public:
    bigInteger();
    bigInteger(int b);
    bigInteger(const std::string& s);
    bigInteger(const bigInteger& b);

    friend int abscompare(const bigInteger& b1,const bigInteger& b2);
    friend bool operator == (const bigInteger& b1,const bigInteger& b2);
    friend bool operator < (const bigInteger& b1,const bigInteger& b2);
    friend bool operator > (const bigInteger& b1,const bigInteger& b2);
    friend bool operator >= (const bigInteger& b1, const bigInteger& b2);


    bigInteger operator - ();    //负号
    bigInteger& operator += (const bigInteger& b);
    bigInteger& operator -= (const bigInteger& b);
    bigInteger& operator *= (const bigInteger& b);
    bigInteger& operator /= (const bigInteger& b);

    friend void carry(bigInteger& b);
    friend bigInteger operator + (const bigInteger& b1,const bigInteger& b2);
    friend bigInteger operator - (const bigInteger& b1,const bigInteger& b2);
    friend bigInteger operator * (const bigInteger& b1,const bigInteger& b2);
    friend bigInteger operator / (const bigInteger& b1,const bigInteger& b2);
    friend bigInteger divmod (bigInteger &a, const bigInteger &b);
    void print();
    int size() const {return digits.size();}
    std::string toString();
    void assign(int num, int val);
    void back(int val);

private:
    std::vector<char> digits;
    bool sign;
};

#endif // BIGINTEGER_H
