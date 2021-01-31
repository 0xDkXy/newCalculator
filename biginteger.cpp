#include "biginteger.h"


bigInteger::bigInteger() {
    sign=true;
}

bigInteger::bigInteger(int b) {
    if (b<0) { sign=false; b=-b; }
    else sign=true;
    while (b) {
        digits.push_back(char('0'+b%10));
        b/=10;
    }
}

bigInteger::bigInteger(const std::string& s) {
    int start=0,len=s.length();
    if (s[0]=='-') { start=1; sign=false; }
    else { start=0; sign=true; }

    for (int i=len-1;i>=start;i--)
        digits.push_back(s[i]);
}

bigInteger::bigInteger(const bigInteger& b) {
    sign=b.sign;
    digits=b.digits;
}

void bigInteger::print() {
    if (!sign) std::cout<<"-";
    for (int i=digits.size()-1;i>=0;i--)
        std::cout<<digits[i];
    //cout<<endl;
}

std::string bigInteger::toString()
{
    std::string res = "";
    if (!sign) res += '-';
    for (int i = digits.size() - 1; i >= 0; --i)
        res += digits[i];
    return res;
}

bigInteger bigInteger::operator - () {
    bigInteger tmp=*this;
    tmp.sign=1-tmp.sign;
    return tmp;
}

//比较b1和b2的绝对值大小，b1>b2返回1，b1==b2返回0，b1<b2返回-1
int abscompare(const bigInteger& b1,const bigInteger& b2) {
    if (b1.digits.size()>b2.digits.size()) return 1;
    if (b1.digits.size()<b2.digits.size()) return -1;
    bool bigger=0,smaller=0;
    int len=b1.digits.size();
    for (int i=len-1;i>=0;i--) {
        if (b1.digits[i]>b2.digits[i]) { bigger=true; break; }
        if (b1.digits[i]<b2.digits[i]) { smaller=true; break; }
    }
    if (bigger) return 1;
    else if (smaller) return -1;
    else return 0;
}

bool operator == (const bigInteger& b1,const bigInteger& b2) {
    if (b1.sign!=b2.sign) return false;
    return (abscompare(b1,b2)==0);
}

bool operator < (const bigInteger& b1,const bigInteger& b2) {
    if (b1.sign==true && b2.sign==false) return false;
    if (b1.sign==false && b2.sign==true) return true;
    int cmp=abscompare(b1,b2);
    if (b1.sign==true)
        if (cmp>=0) return false;
        else return true;
    if (b1.sign==false)
        if (cmp<=0) return true;
        else return false;
}

bool operator > (const bigInteger& b1,const bigInteger& b2) {
    if (b1.sign==true && b2.sign==false) return true;
    if (b1.sign==false && b2.sign==true) return false;
    int cmp=abscompare(b1,b2);
    if (b1.sign==true)
        if (cmp<=0) return false;
        else return true;
    if (b1.sign==false)
        if (cmp>0) return true;
        else return false;
}

bool operator >= (const bigInteger& b1, const bigInteger& b2)
{
    if(b1.sign && !b2.sign) return true;
    if(!b1.sign && b2.sign) return false;
    int cmp = abscompare(b1, b2);
    if (b1.sign)
        if (cmp < 0) return false;
        else return true;
    if (!b1.sign)
        if (cmp > 0) return false;
        else return true;
}

void carry(bigInteger &b) {
    int len=b.digits.size();
    for (int i=0;i<len-1;i++) {
        b.digits[i+1]+=(b.digits[i]-'0')/10;
        b.digits[i]=(b.digits[i]-'0')%10+'0';
    }
    while (b.digits[b.digits.size()-1]>='0'+10) {
        int t=b.digits.size()-1;
        b.digits.push_back((b.digits[t]-'0')/10+'0');
        b.digits[t]=(b.digits[t]-'0')%10+'0';
    }
}

void bigInteger::assign(int num, int val)
{
    while(num){
        digits.push_back('0' + val);
        num--;
    }
}

void bigInteger::back(int val)
{
    digits.back() = '0' + val;
}

bigInteger operator + (const bigInteger& b1,const bigInteger& b2) {
    if (b1.sign!=b2.sign) {
        bigInteger newb1(b1),newb2(b2);
        if (b1.sign==true && b2.sign==false) return (newb1-(-newb2));
        else return newb2-(-newb1);
    }
    int maxlen=std::max(b1.digits.size(),b2.digits.size());
    bigInteger ret;
    for (int i=0;i<maxlen;i++)
        if (b1.digits.size()-1>=i && b2.digits.size()-1>=i) ret.digits.push_back(b1.digits[i]+b2.digits[i]-'0');
        else if (b1.digits.size()-1>=i) ret.digits.push_back(b1.digits[i]);
        else ret.digits.push_back(b2.digits[i]);
    carry(ret);
    ret.sign=b1.sign;
    return ret;
}

bigInteger operator - (const bigInteger& b1,const bigInteger& b2) {        //待完善
    if (b1.sign!=b2.sign) {
        bigInteger newb1(b1),newb2(b2);
        return (newb1+(-newb2));
    }
    if (b1.sign==false && b2.sign==false) {
        bigInteger newb1(b1),newb2(b2);
        return (-newb2)-(-newb1);
    }
    if (b1<b2) {
        bigInteger newb1(b1),newb2(b2);
        return -(newb2-newb1);
    }

    bigInteger ret;
    int maxlen=std::max(b1.digits.size(),b2.digits.size());
    for (int i=0;i<maxlen;i++)
        if (b1.digits.size()-1>=i && b2.digits.size()-1>=i) ret.digits.push_back(b1.digits[i]-b2.digits[i]);
        else ret.digits.push_back(b1.digits[i]-'0');
    for (int i=0;i<maxlen;i++)
        if (ret.digits[i]<0) {
            ret.digits[i+1]--;
            ret.digits[i]+=10;
        }
    while (ret.digits.size()>1 && ret.digits[ret.digits.size()-1]==0) ret.digits.pop_back();
    for (int i=0;i<ret.digits.size();i++) ret.digits[i]+='0';
    return ret;
}

bigInteger operator * (const bigInteger& b1,const bigInteger& b2) {
    bigInteger ret;
    ret.sign=(b1.sign==b2.sign);
    int len1=b1.digits.size(),len2=b2.digits.size();
    std::vector<int> tmp(len1+len2,0);
    for (int i=0;i<len1;i++)
        for (int j=0;j<len2;j++)
            tmp[i+j]+=(b1.digits[i]-'0')*(b2.digits[j]-'0');
    for (int i=0;i<(len1+len2-1);i++) {
        tmp[i+1]+=tmp[i]/10;
        tmp[i]%=10;
    }
    while (tmp[tmp.size()-1]>=10) {
        tmp.push_back(tmp[tmp.size()-1]/10);
        tmp[tmp.size()-2]%=10;
    }
    for (int i=0;i<tmp.size();i++)
        ret.digits.push_back(tmp[i]+'0');
    while (ret.digits.size()>1 && ret.digits[ret.digits.size()-1]=='0') ret.digits.pop_back();
    return ret;
}

bigInteger& bigInteger::operator +=(const bigInteger& b) {
    *this=*this+b;
    return *this;
}

bigInteger& bigInteger::operator -=(const bigInteger& b) {
    *this=*this-b;
    return *this;
}

bigInteger& bigInteger::operator *=(const bigInteger& b) {
    *this=*this*b;
    return *this;
}

bigInteger divmod(const bigInteger &aa, const bigInteger &b)
{
    bigInteger a = aa;
    bigInteger ans("0");
    for (int t = a.size() - b.size(); a >= b; --t) {
        bigInteger d("0");
        d.assign(t + 1, 0);
        d.back(1);
        bigInteger c = b * d;
        while(a >= c) {
            a -= c;
            ans += d;
        }
    }
    return ans;
}

bigInteger operator / (const bigInteger& b1, const bigInteger& b2)
{
    return divmod(b1, b2);
}

bigInteger fft_mul (bigInteger& b1, bigInteger& b2)
{
    std::string s1 = b1.toString(), s2 = b2.toString();
    bool sign1,sign2;
    sign1 = sign2 = 1;
    if (s1[0] == '-'){
        sign1 = 0;
        s1.erase(0,1);
    }
    if (s2[0] == '-'){
        sign2 = 0;
        s2.erase(0,1);
    }
    bool ansSign = ~(sign1 ^ sign2);
    fft f1 = fft();
    std::string strAns = f1.calc(s1, s2);
    bigInteger ans = bigInteger(strAns);
    ans.setSign(ansSign);
    return ans;
}

void bigInteger::setSign(bool _sign)
{
    sign = _sign;
}

