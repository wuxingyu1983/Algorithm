// https://pintia.cn/problem-sets/91827364500/exam/problems/91827369832?type=7&page=28

#include <cmath>
#include <cstdio>
#include <vector>
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

#define DEBUG 0
#define MAX_N 501

#define getVal4St(ST, POS) ((ST) >> (POS)) & 1

#define setVal4St(ST, POS, VAL) \
    ST &= ~(1 << (POS));        \
    if (VAL)                    \
        ST |= (VAL) << (POS);

int l;
int dp[MAX_N][8193];
int roads[MAX_N];
unsigned char pos[17];

void init()
{
    memset(dp, 0xff, sizeof(dp));

    dp[0][0] = 0;
}

int main()
{
    pos[2] = 1;
    pos[4] = 2;
    pos[8] = 3;
    pos[16] = 4;

    int t;
    cin >> t;

    for (size_t iT = 0; iT < t; iT++)
    {
        cin >> l;

        for (size_t i = 1; i <= l; i++)
        {
            cin >> roads[i];
        }

        init();
        int ans = -1;

        for (size_t i = 1; i <= l; i++)
        {
            int idx = pos[roads[i]];

            for (size_t st = 0; st <= 8192; st++)
            {
                if (0 <= dp[i - 1][st])
                {
                    // not dig it
                    {
                        if (dp[i - 1][st] > dp[i][st])
                        {
                            dp[i][st] = dp[i - 1][st];
                            if (l == i && dp[i][st] > ans)
                            {
                                ans = dp[i][st];
                            }
                        }
                    }

                    // dig it
                    {
                        int sum = roads[i] + dp[i - 1][st];

                        if (0 == (st & ((1 << idx) - 1)))
                        {
                            unsigned int newSt = st;
                            int bonus = 2 * roads[i];

                            for (size_t p = idx; p <= 12; p++)
                            {
                                if (getVal4St(st, p))
                                {
                                    sum += bonus;

                                    setVal4St(newSt, p, 0);
                                    bonus *= 2;
                                }
                                else
                                {
                                    setVal4St(newSt, p, 1);
                                    break;
                                }
                            }

                            if (sum > dp[i][newSt])
                            {
                                dp[i][newSt] = sum;

                                if (l == i && dp[i][newSt] > ans)
                                {
                                    ans = dp[i][newSt];
                                }
                            }
                        }
                        else
                        {
                            unsigned int newSt = 1 << idx;

                            if (sum > dp[i][newSt])
                            {
                                dp[i][newSt] = sum;

                                if (l == i && dp[i][newSt] > ans)
                                {
                                    ans = dp[i][newSt];
                                }
                            }
                        }
                    }
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}
