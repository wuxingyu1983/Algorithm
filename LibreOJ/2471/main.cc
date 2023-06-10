// https://loj.ac/p/2471

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
#define MAX_N   11
#define MAX_M   11

int n, m;
int ff[MAX_N][MAX_M];   // feifei
int nn[MAX_N][MAX_M];   // niuniu 
vector<long long> dp(1048576, LLONG_MIN);

long long dfs(int now, int player)
{
    if (LLONG_MIN == dp[now])
    {
        int x = n, y = 0;

        for (size_t i = 0; i < n + m - 1; i++)
        {
            if (now & (1 << i))
            {
                x --;
            }
            else
            {
                y ++;
            }

            if ((1 << i) == (now & (3 << i)))
            {
                long long tmp = dfs(now ^ (3 << i), 1 - player);
                if (player) 
                {
                    tmp += ff[x][y];

                    if (tmp > dp[now])
                    {
                        dp[now] = tmp;
                    }
                }
                else
                {
                    tmp -= nn[x][y];

                    if (LLONG_MIN == dp[now] || tmp < dp[now])
                    {
                        dp[now] = tmp;
                    }
                }
            }
        }
        
    }

    return dp[now];
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

#if DEBUG
    fscanf(fp, "%d %d", &n, &m);
#else
    scanf("%d %d", &n, &m);
#endif

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            int sc;
#if DEBUG
            fscanf(fp, "%d", &sc);
#else
            scanf("%d", &sc);
#endif
            ff[i][j] = sc;
        }
    }
    
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            int sc;
#if DEBUG
            fscanf(fp, "%d", &sc);
#else
            scanf("%d", &sc);
#endif
            nn[i][j] = sc;
        }
    }

    int start = 0, end = 0;

    start = (1 << n) - 1;
    end = start << m;

    dp[end] = 0;

    dfs(start, 1);

    cout << dp[start] << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
