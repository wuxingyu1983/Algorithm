#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <stack>

using namespace std;

int dp[9][4600];    // dp[pos][weight]: 从0位到pos位，weight 的个数

int F(int x)
{
    int ret = 0;
    int p = 1;

    while (x)
    {
        ret += p * (x % 10);
        x /= 10;
        p *= 2;
    }

    return ret;
}

int dfs(vector<int> &digit, int pos, int remain, bool limit)
{
    int ret = 0;

    if (limit)
    {
        int up = digit[pos];
        if (0 == pos)
        {
            ret += dp[0][remain < up ? remain : up];
        }
        else {
            for (int i = 0; i <= up; i++)
            {
                if (remain < i * pow(2, pos))
                {
                    break;
                }
                else
                {
                    ret += dfs(digit, pos - 1, remain - i * pow(2, pos), limit && i == up);
                }
            }
        }
    }
    else
    {
        ret = dp[pos][remain];
    }
    
    return ret;
}

int main()
{
    // 计算 dp
    for (int pos = 0 , p = 1; pos < 9; pos++)
    {
        for (size_t w = 0; w < 10; w++)
        {
            if (0 == pos)
            {
                dp[pos][w] = 1;
            }
            else
            {
                int tmp = p * w;

                for (size_t i = 0; i < 4600; i++)
                {
                    if (tmp + i < 4600)
                    {
                        dp[pos][tmp + i] += dp[pos - 1][i];
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        p *= 2;
    }

    for (size_t pos = 0; pos < 9; pos++)
    {
        for (size_t i = 1; i < 4600; i++)
        {
            dp[pos][i] += dp[pos][i - 1];
        }
    }

    int t;
    cin >> t;

    for (size_t i = 1; i <= t; i++)
    {
        int a, b;
        cin >> a >> b;

        int fa = F(a);

        vector<int> digit;
        int x = b;

        while (x)
        {
            digit.push_back(x % 10);
            x /= 10;
        }

        int len = digit.size();

        int ans = dfs(digit, len - 1, fa, true);

        printf("Case #%d: %d\n", i, ans);
    }

    return 0;
}
