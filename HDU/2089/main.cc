#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// 最多 6 位
const int digits = 6;

// dp[d][0] -- 最高位 2 的数量
// dp[d][1] -- 最高位 不是 2 或 4 的数量
unsigned int dp[digits][2];

unsigned int getCount(unsigned int x)
{
    unsigned int uiRet = 0;
    unsigned int prev = 0;

    for (unsigned int i = 100000, d = 5; i >= 1; i = i / 10, d--)
    {
        unsigned int digit = x / i;
        digit %= 10;

        if (1 == i)
        {
            if (6 == prev)
            {
                if (4 <= digit)
                {
                    uiRet += digit + 1 - 2;
                }
                else if (2 <= digit)
                {
                    uiRet += digit + 1 - 1;
                }
                else
                {
                    uiRet += digit + 1;
                }
            }
            else
            {
                if (4 <= digit)
                {
                    uiRet += digit + 1 - 1;
                }
                else
                {
                    uiRet += digit + 1;
                }
            }
        }
        else
        {
            for (unsigned int j = 0; j < digit; j++)
            {
                if (4 == j)
                {
                }
                else if (6 == prev && 2 == j)
                {
                }
                else if (6 == j)
                {
                    uiRet += dp[d - 1][1];
                }
                else
                {
                    uiRet += dp[d - 1][0] + dp[d - 1][1];
                }
            }

            if (4 == digit)
            {
                break;
            }
            else if (2 == digit && 6 == prev)
            {
                break;
            }
            else
            {
                prev = digit;
            }
        }
    }

    return uiRet;
}

int main()
{
    unsigned int m, n;

    // init dp array
    dp[0][0] = 1;
    dp[0][1] = 8;

    for (size_t i = 1; i < digits; i++)
    {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][1] = 7 * (dp[i - 1][0] + dp[i - 1][1]) + dp[i - 1][1];
    }

    while (true)
    {
        cin >> n >> m;

        if (0 == n && 0 == m)
        {
            break;
        }

        unsigned int count = getCount(m) - getCount(n - 1);

        cout << count << endl;

    }

    return 0;
}
