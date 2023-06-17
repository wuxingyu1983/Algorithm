// http://poj.org/problem?id=2411

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

#define DEBUG       0
#define MAX_HW      11
#define MAX_2HW     2048
long long dp[MAX_HW + 1][MAX_HW + 1][MAX_2HW];      // dp[row][col][MAX_2HW]

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    // init
    for (size_t col = 1; col <= MAX_HW; col++)
    {
        dp[1][col][0] = 1;

        if (2 <= col)
        {
            int mask = 3;

            for (size_t i = 0; i < (1 << col) - (mask << (col - 2)); i++)
            {
                dp[1][col][i + (mask << (col - 2))] = dp[1][col][i];
            }
        }
    }

    for (size_t row = 2; row <= MAX_HW; row++)
    {
        for (size_t col = 1; col <= MAX_HW; col++)
        {
            for (size_t i = 0; i < (1 << col); i++)
            {
                int last_idx = (~i) & ((1 << col) - 1);

                dp[row][col][i] = dp[row][col][last_idx];

                if (2 <= col)
                {
                    int mask = 3;
                    while (mask > i)
                    {
                        if (mask == (mask & i))
                        {
                            dp[row][col][i] += dp[row][col][i - mask];
                        }

                        mask <<= 1;
                    }
                }
            }
        }
    }

    int h, w;
    while (true)
    {
#if DEBUG
        fscanf(fp, "%d %d", &h, &w);
#else
        scanf("%d %d", &h, &w);
#endif
        if (0 == h && 0 == w)
        {
            break;
        }

        cout << dp[h][w][(1 << w) - 1] << endl;
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
