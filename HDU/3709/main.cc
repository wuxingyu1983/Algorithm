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

#define MID     153

// dp[pos][pivot][0——153 (17位全是9)]
long long dp[18][18][154];

vector<int> a;

long long dfs(int pos, int pre, long long sta, bool limit)
{
    long long ret = 0;

    int up = limit ? a[pos] : 9;
    long long tmp = 0;
    for (size_t i = 0; i <= up; i++)
    {
        tmp = sta * 10 + i;
        if (limit && i == up)
        {
            ret += dfs(pos - 1, pre, tmp, limit);
        }
        else
        {
            for (size_t pivot = 0; pivot <= pos; pivot++)
            {
                if (pivot == pos)
                {
                    ret += dp[pos][pivot][0];
                }
                else
                {
                    ret += dp[pos - 1][pivot][tmp * (pos - pivot)];
                }
            }
        }
    }

    return 0;
}

int main()
{
    dp[0][0][0] = 10;
    for (size_t pivot = 1; pivot < 18; pivot++)
    {
        for (size_t i = 0; i < 154; i++)
        {
            if (0 < dp[pivot - 1][pivot - 1][i])
            {
                for (size_t num = 0; num < 10; num++)
                {
                    dp[pivot][pivot][i + num * pivot] += dp[pivot - 1][pivot - 1][i];
                }
            }
        }
    }

    for (size_t pivot = 0; pivot < 18; pivot++)
    {
        for (size_t pos = pivot + 1; pos < 18; pos++)
        {
            for (size_t i = 0; i < 154; i++)
            {
                if (0 < dp[pos - 1][pivot][i])
                {
                    for (size_t num = 0; num < 10; num++)
                    {
                        if (0 <= (i - num * (pos - pivot)))
                        {
                            dp[pos][pivot][i - num * (pos - pivot)] += dp[pos - 1][pivot][i];
                        }
                        else
                        {
                            break;        
                        }
                    }
                }
            }
        }
    }

    int t;
    cin >> t;

    for (size_t i = 0; i < t; i++)
    {
        long x, y;
        cin >> x >> y;

        long long cnt_x = 0;
        long long cnt_y = 0;

        if (0 < x)
        {
            x -= 1;

            a.clear();

            while (x)
            {
                a.push_back(x % 10);
                x /= 10;
            }

            int len = a.size();

            cnt_x = dfs(len - 1, -1, 0, true);
        }

        if (0 < y)
        {
            if (1000000000000000000 == y)
            {
                y -= 1;
            }

            a.clear();

            while (y)
            {
                a.push_back(y % 10);
                y /= 10;
            }

            int len = a.size();

            cnt_y = dfs(len - 1, -1, 0, true);
        }

        cout << (cnt_y - cnt_x) << endl;
    }

    return 0;
}
