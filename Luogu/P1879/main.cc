// https://www.luogu.com.cn/problem/P1879

#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define DEBUG   0
#define MAX_MN  4098
#define MOD     100000000

int dp[MAX_MN][MAX_MN];
unsigned int flags[MAX_MN];
int barren[12];     // 贫瘠的地块
int sum[12];
vector<int> vec[MAX_MN];

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    int m, n;
#if DEBUG
    fscanf(fp, "%d %d", &m, &n);
#else
    scanf("%d %d", &m, &n);
#endif

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            int c;
#if DEBUG
            fscanf(fp, "%d", &c);
#else
            scanf("%d", &c);
#endif

            if (0 == c)
            {
                barren[i] |= 1 << j;
            }
        }
    }

    // pre proc
    int max_n = (1 << n) - 1;
    for (size_t i = 1; i <= max_n; i++)
    {
        int f = 3;
        for (size_t j = 0; j <= 10; j++)
        {
            f = 3 << j;
            if ((i & f) == f)
            {
                flags[i] = 1;
                break;
            }
        }
    }

    for (size_t i = 1; i <= max_n; i++)
    {
        if (0 == flags[i])
        {
            for (size_t j = 1; j <= max_n; j++)
            {
                if (i & j)
                {
                    vec[i].push_back(j);
                }
            }
        }
    }
    
    // proc
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j <= max_n; j++)
        {
            if (0 == flags[j] && 0 == (j & barren[i]))
            {
                if (0 == i)
                {
                    dp[i][j] = 1;
                }
                else
                {
                    dp[i][j] = sum[i - 1];
                    for (vector<int>::iterator it = vec[j].begin(); it != vec[j].end(); it++)
                    {
                        dp[i][j] -= dp[i - 1][*it];
                        dp[i][j] += MOD;
                        dp[i][j] %= MOD;
                    }
                }

                sum[i] += dp[i][j];
                sum[i] %= MOD;
            }
        }
    }

    cout << sum[m - 1] << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
