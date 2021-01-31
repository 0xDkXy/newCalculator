#ifndef FFT_H
#define FFT_H
#include<cmath>
#include<algorithm>
#include<string>

class fft
{
public:
    fft();
    const double PI = acos(-1);
    const int maxn = 1010;
    std::string calc(std::string str1, std::string str2);
private:
    struct Complex
    {
        double x, y;
        Complex(double _x = 0.0, double _y = 0.0) { x = _x, y = _y; }

        Complex operator-(const Complex &b) const { return Complex(x - b.x, y - b.y); }
        Complex operator+(const Complex &b) const { return Complex(x + b.x, y + b.y); }
        Complex operator*(const Complex &b) const { return Complex(x * b.x - y * b.y, x * b.y + y * b.x); }
    };

    void change(Complex y[], int len);


    void fft_procession(Complex y[], int len, int on);

    Complex x1[1010], x2[1010];
    std::string str1, str2;
    int sum[1010];
};

#endif // FFT_H
