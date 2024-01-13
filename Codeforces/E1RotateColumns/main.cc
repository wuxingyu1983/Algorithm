// https://codeforces.com/problemset/problem/1209/E1

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
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

#define DEBUG 0
#define MAX_H 4
#define MAX_W 100

int cells[MAX_H][MAX_W];
int dp[MAX_H][MAX_H][MAX_W];
int h, w;

int main()
{
    int t;
    scanf("%d", &t);

    for (size_t iT = 0; iT < t; iT++)
    {
        scanf("%d %d", &h, &w);

        for (size_t row = 0; row < h; row++)
        {
            for (size_t col = 0; col < w; col++)
            {
                scanf("%d", &(cells[row][col]));
            }
        }

        // init
        if (0 < iT)
        {
            memset(dp, 0, sizeof(dp));
        }

        for (size_t i = 0; i < h; i++)
        {
            for (size_t j = 0; j < h; j++)
            {
                dp[i][j][0] = cells[(j + i) % h][0];
            }
        }

        for (size_t col = 1; col < w; col++)
        {
            for (size_t i = 0; i < h; i++)
            {
                for (size_t j = 0; j < h; j++)
                {
                    dp[i][j][col] = cells[j][col];
                    for (size_t k = 0; k < h; k++)
                    {
                        if (dp[i][j][col] < dp[k][j][col - 1])
                        {
                            dp[i][j][col] = dp[k][j][col - 1];
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (size_t i = 0; i < h; i++)
        {
            int tmp = 0;
            for (size_t j = 0; j < h; j++)
            {
                tmp += dp[i][j][w - 1];
            }
            if (tmp > ans)
            {
                ans = tmp;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
