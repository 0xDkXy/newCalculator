#include "fft.h"

fft::fft()
{

}

void fft::change(Complex y[], int len)
{
    int i, j, k;
    for (int i = 1, j = len / 2; i < len - 1; i++)
    {
        if (i < j)
            std::swap(y[i], y[j]);
        // 交换互为小标反转的元素，i<j 保证交换一次
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
        k = len / 2;
        while (j >= k)
        {
            j = j - k;
            k = k / 2;
        }
        if (j < k)
            j += k;
    }
}

void fft::fft_procession(Complex y[], int len, int on)
{
    change(y, len);
    for (int h = 2; h <= len; h <<= 1)
    {
        Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
        for (int j = 0; j < len; j += h)
        {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++)
            {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1)
    {
        for (int i = 0; i < len; i++)
        {
            y[i].x /= len;
        }
    }
}

std::string fft::calc(std::string str1, std::string str2)
{
    int len1 = str1.size(), len2 = str2.size(), len = 1;
            while (len < len1 * 2 || len < len2 * 2)
                len <<= 1;
            for (int i = 0; i < len1; i++)
                x1[i] = Complex(str1[len1 - 1 - i] - '0', 0);
            for (int i = len1; i < len; i++)
                x1[i] = Complex(0, 0);
            for (int i = 0; i < len2; i++)
                x2[i] = Complex(str2[len2 - 1 - i] - '0', 0);
            for (int i = len2; i < len; i++)
                x2[i] = Complex(0, 0);
            fft_procession(x1, len, 1);
            fft_procession(x2, len, 1);
            for (int i = 0; i < len; i++)
                x1[i] = x1[i] * x2[i];
            fft_procession(x1, len, -1);
            for (int i = 0; i < len; i++)
                sum[i] = int(x1[i].x + 0.5);
            for (int i = 0; i < len; i++)
            {
                sum[i + 1] += sum[i] / 10;
                sum[i] %= 10;
            }
            len = len1 + len2 - 1;
            while (sum[len] == 0 && len > 0)
                len--;
            std::string ans = "";
            for (int i = len; i >= 0; i--)
                ans += (char)(sum[i] + '0');
//            cout << "\n";
            return ans;
}
