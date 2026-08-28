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

    Item()
    {
        xy = left = 0;
    }
};

Item dp[65][65];

long long record1[65];           // record1[maxI]
long long record2[65][65][65];       // record2[maxI][maxJ][eqI];

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
        }
        else if (0 == x || 0 == y)
        {
            long long tmp = x + y;
            int maxT = 63;
            for (; maxT >= 0; maxT--)
            {
                if (tmp & ((long long)1 << maxT))
                {
                    break;
                }
            }

            if (record1[maxT])
            {
                ans = record1[maxT];
            }
            else
            {
                vector<Item> odp(64);
                for (int i = 0; i <= maxT + 1; i++)
                {
                    if (0 == i || 0 < odp[i].xy)
                    {
                        for (int l = odp[i].left + 1; l + i < 63; l++)
                        {
                            long long newXY = odp[i].xy | ((long long)1 << l);
                            if (0 == odp[l + i].xy || newXY < odp[l + i].xy)
                            {
                                odp[l + i].xy = newXY;
                                odp[l + i].left = l;

                                if (l + i > maxT)
                                {
                                    if (0 == ans || ans > newXY)
                                    {
                                        ans = newXY;
                                    }
                                }
                            }
                        }
                    }
                }

                record1[maxT] = ans;
            }
        }
        else
        {
            if (x > y)
            {
                swap(x, y);
            }

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

            if (record2[maxI][maxJ][eqI])
            {
                ans = record2[maxI][maxJ][eqI];
            }
            else
            {
                // init
                {
                    for (int i = 1; i <= maxI + 1; i++)
                    {
                        dp[i][0].left = i;
                        dp[i][0].xy = (long long)1 << i;

                        if (i == eqI && 0 == eqJ)
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

                        if (0 == eqI && j == eqJ)
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

                                        if ((i + l > maxI && j > maxJ) || (i + l - j == eqI - eqJ && j >= eqJ))
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

                                    if (0 == dp[i][j + l].xy || tmp < dp[i][j + l].xy)
                                    {
                                        dp[i][j + l].xy = tmp;
                                        dp[i][j + l].left = l;

                                        if ((i > maxI && j + l > maxJ) || (i >= eqI && j + l - i == eqJ - eqI))
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

                record2[maxI][maxJ][eqI] = ans;
            }
        }
        
        cout << ans << "\n";
    }

    return 0;
}
