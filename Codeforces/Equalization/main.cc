// https://codeforces.com/problemset/problem/2075/D

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>

using namespace std;

class Item
{
public:
    long long xy;
    int left; // xy 最高位的位置

    Item() {}
};

Item dp[65][65];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        long long x, y;
        cin >> x >> y;

        memset(dp, 0, sizeof(dp));

        long long ans = 0;

        if (x == y)
        {
            cout << 0 << "\n";
        }
        else if (0 == x || 0 == y)
        {

        }
        else
        {
            int maxI = 63, eqI = -1;
            for (; maxI >= 0; maxI--)
            {
                if (x & ((long long)1 << maxI))
                {
                    eqI = maxI;
                    break;
                }
            }

            int maxJ = 63, eqJ = -1;
            for (; maxJ >= 0; maxJ--)
            {
                if (y & ((long long)1 << maxJ))
                {
                    eqJ = maxJ;
                    break;
                }
            }

            for (;;)
            {
                if (0 >= eqI || 0 >= eqJ)
                {
                    break;
                }

                if (0 != (x & (1 << (eqI - 1))) && 0 == (y & (1 << (eqJ - 1))))
                {
                    break;
                }

                if (0 == (x & (1 << (eqI - 1))) && 0 != (y & (1 << (eqJ - 1))))
                {
                    break;
                }

                eqI--;
                eqJ--;
            }

            // init
            {
                for (int i = 1; i <= maxI + 1; i++)
                {
                    dp[i][0].left = i;
                    dp[i][0].xy = (long long)1 << i;

                    if (i >= eqI && 0 >= eqJ)
                    {
                        if (0 == ans || ans > dp[i][0].xy)
                        {
                            ans = dp[i][0].xy;
                        }
                    }
                }

                for (int j = 1; j <= maxJ + 1; j++)
                {
                    dp[0][j].left = j;
                    dp[0][j].xy = (long long)1 << j;

                    if (0 >= eqI && j >= eqJ)
                    {
                        if (0 == ans || ans > dp[0][j].xy)
                        {
                            ans = dp[0][j].xy;
                        }
                    }
                }
            }

            for (int j = 0; j <= 57; j++)
            {
                for (int i = 0; i <= 57; i++)
                {
                    if (0 < dp[i][j].xy)
                    {
                        for (int l = dp[i][j].left + 1; l < 63; l++)
                        {
                            if (63 > i + l)
                            {
                                long long tmp = dp[i][j].xy | ((long long)1 << l);

                                if (0 == dp[i + l][j].xy || tmp < dp[i + l][j].xy)
                                {
                                    dp[i + l][j].xy = tmp;
                                    dp[i + l][j].left = l;

                                    if (i + l >= eqI && j >= eqJ)
                                    {
                                        if (0 == ans || ans > dp[i + l][j].xy)
                                        {
                                            ans = dp[i + l][j].xy;
                                        }
                                    }
                                }
                            }

                            if (63 > j + l)
                            {
                                long long tmp = dp[i][j].xy | ((long long)1 << l);

                                if (0 == dp[i][j + l].xy || tmp < dp[i + l][j + l].xy)
                                {
                                    dp[i][j + l].xy = tmp;
                                    dp[i][j + l].left = l;

                                    if (i >= eqI && j + l >= eqJ)
                                    {
                                        if (0 == ans || ans > dp[i][j + l].xy)
                                        {
                                            ans = dp[i][j + l].xy;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            cout << ans << "\n";
        }
    }

    return 0;
}
