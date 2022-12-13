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

// 在数中的个数
unsigned int dp[10][10];
// 起始的数中的个数
unsigned int cnt[10][10];

unsigned int getWindyCount(unsigned int num)
{
    unsigned int uiRet = 0;

    if (0 == num)
    {
        uiRet = 1;
        return uiRet;
    }
    
    int digit = 0;
    int prev = -2;

    for (size_t i = 1000000000, idx = 9; i >= 1; i /= 10, idx --)
    {
        digit = num / i;
        
        if (0 < digit)
        {
            digit %= 10;
            
            for (int j = 0; j < digit; j++)
            {
                if (1 < abs(prev - j))
                {
                    if (0 > prev && 0 == j)
                    {
                        uiRet += cnt[idx][j];
                    }
                    else
                    {
                        uiRet += dp[idx][j];
                    }
                }
            }
            
            // j == digit
            if (1 >= abs(prev - digit))
            {
                break;
            }
            else
            {
                if (0 == idx)
                {
                    uiRet += 1;
                }
                else
                {
                    prev = digit;
                }
            }
        }
    }

    return uiRet;
}

int main()
{
    unsigned int a, b;

    cin >> a >> b;

    // init dp, cnt
    for (size_t j = 0; j < 10; j++)
    {
        dp[0][j] = 1;
        cnt[0][j] = 1;
    }

    for (size_t i = 1; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                if (1 < abs(k - j))
                {
                    dp[i][j] += dp[i - 1][k];
                }
            }
            
            cnt[i][j] = dp[i][j];
        }
    }

    for (size_t i = 1; i < 10; i++)
    {
        cnt[i][0] = 0;
        for (size_t j = 0; j < 10; j++)
        {
            cnt[i][0] += cnt[i - 1][j];
        }
    }

    cout << getWindyCount(b) - getWindyCount(a - 1) << endl;

    return 0;
}
