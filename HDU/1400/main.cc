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

long long func(int row, int i, int start, int col)
{
    long long ret = 0;
    
    int last_idx = (~i) & ((1 << col) - 1);

    ret = dp[row - 1][col][last_idx];
 
    int mask = 3;
    for (int pos = start; pos < col; pos++)
    {
        if ((mask << pos) == (i & (mask << pos)))
        {
            ret += func(row, i - (mask << pos), pos + 2, col);
        }
    }
    
    return ret;
}

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
            
            for (int i = 0; i < col - 1; i++)
            {
                for (int j = 0; j < (1 << i); j++)
                {
                    dp[1][col][j + (mask << i)] = dp[1][col][j];
                }
            }
        }
    }

    for (size_t row = 2; row <= MAX_HW; row++)
    {
        for (size_t col = 1; col <= MAX_HW; col++)
        {
            for (size_t i = 0; i < (1 << col); i++)
            {
                dp[row][col][i] = func(row, i, 0, col);
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
