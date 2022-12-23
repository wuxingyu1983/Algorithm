#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#define DEBUG 0

// 最大位数 45 位
const int max_bits = 45;

// bit 位 回文数 的个数
unsigned long long cnt[max_bits];

unsigned long long fnCount(string &digits, int idx, int lo, int hi)
{
    unsigned long long ret = 0;

    int n = digits.length();

    if (idx == 1 + ceil(((float)n) / 2.0))
    {
        if (lo <= hi)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int start = 0;
    if (1 == idx)
    {
        start = 1;

        // 0
        for (size_t i = 1; i < n; i++)
        {
            ret += cnt[i];
        }
    }

    if (0 <= digits[idx - 1] - '0' - 1)
    {
        int j = n - 2 * idx;
        if (0 > j)
        {
            if (8 < digits[idx - 1] - '0')
            {
                ret += 3 - start;
            }
            else if (1 < digits[idx - 1] - '0')
            {
                ret += 2 - start;
            }
            else
            {
                ret += 1 - start;
            }
        }
        else
        {
            for (; j >= 0; j -= 2)
            {
                if (8 < digits[idx - 1] - '0')
                {
                    ret += (3 - start) * cnt[j];
                }
                else if (1 < digits[idx - 1] - '0')
                {
                    ret += (2 - start) * cnt[j];
                }
                else
                {
                    ret += (1 - start) * cnt[j];
                }
            }
        }
    }

    //    for (size_t i = start; i <= 9; i++)
    if ('0' == digits[idx - 1] || '1' == digits[idx - 1] || '8' == digits[idx - 1])
    {
        char i = digits[idx - 1];
        int tmp_lo = lo;
        int tmp_hi = hi;

        if (i < digits[idx - 1] && idx < tmp_lo)
            tmp_lo = idx;
        if (i < digits[n - idx] && n - idx + 1 < tmp_lo)
            tmp_lo = n - idx + 1;
        if (i > digits[idx - 1] && idx < tmp_hi)
            tmp_hi = idx;
        if (i > digits[n - idx] && n - idx + 1 < tmp_hi)
            tmp_hi = n - idx + 1;

        ret += fnCount(digits, idx + 1, tmp_lo, tmp_hi);
    }

    return ret;
}

unsigned long long getCount(string num)
{
    unsigned long long ret = 0;

    if (1 == num.length())
    {
        if ('8' <= num[0])
        {
            return 3;
        }
        else if ('1' <= num[0])
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    ret += fnCount(num, 1, num.length() + 1, num.length() + 1);

    return ret;
}

bool isMirrorNumber(string num)
{
    bool ret = true;

    int n = num.length();

    for (size_t i = 0; i <= n / 2; i++)
    {
        if (num[i] == num[n - 1 - i])
        {
            if ('0' != num[i] && '1' != num[i] && '8' != num[i])
            {
                ret = false;
                break;
            }
        }
        else
        {
            ret = false;
            break;
        }
    }

    return ret;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    // init cnt[max_bits]
    cnt[0] = 1;
    cnt[1] = 3; // 0,1,8
    cnt[2] = 2;  // 11,88
    for (int i = 3; i < max_bits; i++)
    {
        for (int j = i - 2; j >= 0; j -= 2)
        {
            cnt[i] += 2 * cnt[j];
        }
    }

    unsigned int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
#endif

    for (size_t i = 0; i < t; i++)
    {
        string a, b;
#if DEBUG
        inFile >> a >> b;
#else
        cin >> a >> b;
#endif

        unsigned long long num = getCount(b) - getCount(a);

        if (isMirrorNumber(a))
        {
            num += 1;
        }

        cout << num << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
