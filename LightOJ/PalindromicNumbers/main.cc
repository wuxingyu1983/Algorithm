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

#define DEBUG   0

// 最大位数 18 位
const int max_bits = 18;

// bit 位 回文数 的个数
unsigned long long cnt[max_bits];

unsigned long long fnCount(vector<int> &digits, int idx, int lo, int hi)
{
    unsigned long long ret = 0;

    int n = digits.size();

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
    
    if (0 <= digits[idx - 1] - 1)
    {
        int j = n - 2 * idx;
        if (0 > j)
        {
            ret += digits[idx - 1] - start;
        }
        else
        {
            for (; j >= 0; j -= 2)
            {
                ret += (digits[idx - 1] - start) * cnt[j];
            }
        }
    }

//    for (size_t i = start; i <= 9; i++)
    {
        int i = digits[idx - 1];
        int tmp_lo = lo;
        int tmp_hi = hi;

        if (i < digits[idx - 1] && idx < tmp_lo)  tmp_lo = idx;
        if (i < digits[n - idx] && n - idx + 1 < tmp_lo) tmp_lo = n - idx + 1;
        if (i > digits[idx - 1] && idx < tmp_hi)  tmp_hi = idx;
        if (i > digits[n - idx] && n - idx + 1 < tmp_hi) tmp_hi = n - idx + 1;

        ret += fnCount(digits, idx + 1, tmp_lo, tmp_hi);
    }

    return ret;
}

unsigned long long getCount(long long num)
{
    unsigned long long ret = 0;

    if (num < 10)
    {
        return num + 1;
    }

    unsigned long long tmp = num;
    vector<int> nums;

    for (unsigned long long i = 100000000000000000; i > 0; i /= 10)
    {
        unsigned long long n = tmp / i;
        if (0 == n)
        {
            if (0 < nums.size())
            {
                nums.push_back(n);
            }
        }
        else
        {
            nums.push_back(n);
        }

        tmp %= i;
    }

    ret += fnCount(nums, 1, nums.size() + 1, nums.size() + 1);

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
    cnt[1] = 10;    // 0 - 9
    cnt[2] = 9;     // 11 - 99
    for (int i = 3; i < max_bits; i++)
    {
        for (int j = i - 2; j >= 0; j -= 2)
        {
            cnt[i] += 9 * cnt[j];
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
        unsigned long long x, y;
#if DEBUG
        inFile >> x >> y;
#else
        cin >> x >> y;
#endif

        if (x > y)
        {
            unsigned long long tmp = x;
            x = y;
            y = tmp;
        }

        cout << "Case " << i + 1 << ": " << getCount(y) - getCount(x - 1) << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
