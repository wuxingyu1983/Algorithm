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

int dp[32][33];     // dp[第几位][1的个数]
vector<int> a;

int dfs(int pos, int ones, bool limit)
{
    if (0 > pos)
    {
        if (ones <= a.size() / 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int ret = 0;

    if (limit)
    {
        int up = limit ? a[pos] : 1;

        for (size_t i = 0; i <= up; i++)
        {
            if (0 == i)
            {
                ret += dfs(pos - 1, ones, limit && i == up);
            }
            else
            {
                ret += dfs(pos - 1, ones + 1, limit && i == up);
            }
        }
    }
    else
    {
        if (0 == ones)
        {
            // 高位还没有1出现过
            for (size_t p = 0; p <= pos; p++)
            {
                int max_ones = (p + 1) / 2;
                for (size_t i = 0; i <= max_ones; i++)
                {
                    ret += dp[p][i];
                }
            }
        }
        else
        {
            // 高位已经有1出现过
            int max_ones = a.size() / 2 - ones;
            if (0 <= max_ones)
            {
                for (size_t p = 0; p <= pos; p++)
                {
                    for (size_t i = 0; i <= max_ones; i++)
                    {
                        ret += dp[p][i];
                    }
                }
            }
        }
    }

    return ret;
}

int solve(int x)
{
    int ret = 0;

    a.clear();

    while (x)
    {
        a.push_back(x % 2);
        x /= 2;
    }

    ret = dfs(a.size() - 1, 0, true);

    return ret;
}

int main()
{
    int start, finish;
    cin >> start >> finish;

    dp[0][0] = 1;
    dp[0][1] = 1;

    for (size_t pos = 1; pos < 32; pos++)
    {
        for (size_t i = 1; i <= pos + 1; i++)
        {
            for (size_t j = 0; j < pos; j++)
            {
                dp[pos][i] += dp[j][i - 1];
            }
        }
    }

    cout << solve(finish) - solve(start - 1) << endl;
}
