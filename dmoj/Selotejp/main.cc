// https://dmoj.ca/problem/coci20c3p4

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
#include <unordered_map>
#include <utility>

using namespace std;

const int MAX_N = 1000;
const int MAX_M = 10;
const int ST_BITS = 1;
const int ST_MASK = 1;

char calendar[MAX_N][MAX_M];
int dp[2][1024];
char flag[2][1024];

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (size_t row = 0; row < n; row++)
    {
        for (size_t col = 0; col < m; col++)
        {
            cin >> calendar[row][col];
        }

        cin.ignore();
    }
    
    int ans = 10000;

    int maxSt = (1 << m) - 1;
    int act = 0;

    for (size_t row = 0; row < n; row++)
    {
        for (size_t col = 0; col < m; col++)
        {
            // state = 0 => | or blocked
            // state = 1 => --

            memset(flag[act], 0, 1024);
            memset(dp[act], 0, sizeof(int) * 1024);

            if (0 == row && 0 == col)
            {
                if ('#' == calendar[row][col])
                {
                    dp[act][0] = 1;
                    flag[act][0] = 1;

                    dp[act][1] = 1;
                    flag[act][1] = 1;

                    if (row == n - 1 && col == m - 1 && ans > 1)
                        ans = 1;
                }
                else
                {
                    // blocked
                    flag[act][0] = 1;
                }
            }
            else if (0 == row)
            {
                for (size_t st = 0; st <= maxSt; st++)
                {
                    if (flag[1 - act][st])
                    {
                        int newSt = st;
                        if ('#' == calendar[row][col])
                        {
                            int leftSt = getVal4St(st, col - 1);
                            if (1 == leftSt)
                            {
                                setVal4St(newSt, col, 1);
                                if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                                {
                                    dp[act][newSt] = dp[1 - act][st];
                                    flag[act][newSt] = 1;

                                    if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                        ans = dp[act][newSt];
                                }
                            }
                            else
                            {
                                // 0
                                setVal4St(newSt, col, 0);
                                if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st] + 1)
                                {
                                    dp[act][newSt] = dp[1 - act][st] + 1;
                                    flag[act][newSt] = 1;

                                    if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                        ans = dp[act][newSt];
                                }

                                // 1
                                setVal4St(newSt, col, 1);
                                if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st] + 1)
                                {
                                    dp[act][newSt] = dp[1 - act][st] + 1;
                                    flag[act][newSt] = 1;

                                    if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                        ans = dp[act][newSt];
                                }
                            }
                        }
                        else
                        {
                            setVal4St(newSt, col, 0);
                            if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                            {
                                dp[act][newSt] = dp[1 - act][st];
                                flag[act][newSt] = 1;

                                if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                    ans = dp[act][newSt];
                            }
                        }
                    }
                }
            }
            else if (0 == col)
            {
                for (size_t st = 0; st <= maxSt; st++)
                {
                    if (flag[1 - act][st])
                    {
                        int newSt = st;
                        if ('#' == calendar[row][col])
                        {
                            int upSt = getVal4St(st, col);
                            if (0 == upSt && '#' == calendar[row - 1][col])
                            {
                                if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                                {
                                    dp[act][newSt] = dp[1 - act][st];
                                    flag[act][newSt] = 1;

                                    if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                        ans = dp[act][newSt];
                                }
                            }
                            else
                            {
                                // 0
                                setVal4St(newSt, col, 0);
                                if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st] + 1)
                                {
                                    dp[act][newSt] = dp[1 - act][st] + 1;
                                    flag[act][newSt] = 1;

                                    if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                        ans = dp[act][newSt];
                                }

                                // 1
                                setVal4St(newSt, col, 1);
                                if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st] + 1)
                                {
                                    dp[act][newSt] = dp[1 - act][st] + 1;
                                    flag[act][newSt] = 1;

                                    if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                        ans = dp[act][newSt];
                                }
                            }
                        }
                        else
                        {
                            setVal4St(newSt, col, 0);
                            if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                            {
                                dp[act][newSt] = dp[1 - act][st];
                                flag[act][newSt] = 1;

                                if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                    ans = dp[act][newSt];
                            }
                        }
                    }
                }
            }
            else
            {
                for (size_t st = 0; st <= maxSt; st++)
                {
                    if (flag[1 - act][st])
                    {
                        int newSt = st;
                        if ('#' == calendar[row][col])
                        {
                            int upSt = getVal4St(st, col);
                            int leftSt = getVal4St(st, col - 1);

                            if (0 == leftSt)
                            {
                                if (0 == upSt && '#' == calendar[row - 1][col])
                                {
                                    if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                                    {
                                        dp[act][newSt] = dp[1 - act][st];
                                        flag[act][newSt] = 1;

                                        if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                            ans = dp[act][newSt];
                                    }
                                }
                                else
                                {
                                    // 0
                                    setVal4St(newSt, col, 0);
                                    if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st] + 1)
                                    {
                                        dp[act][newSt] = dp[1 - act][st] + 1;
                                        flag[act][newSt] = 1;

                                        if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                            ans = dp[act][newSt];
                                    }

                                    // 1
                                    setVal4St(newSt, col, 1);
                                    if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st] + 1)
                                    {
                                        dp[act][newSt] = dp[1 - act][st] + 1;
                                        flag[act][newSt] = 1;

                                        if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                            ans = dp[act][newSt];
                                    }
                                }
                            }
                            else
                            {
                                // 1 == leftSt
                                setVal4St(newSt, col, 1);
                                if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                                {
                                    dp[act][newSt] = dp[1 - act][st];
                                    flag[act][newSt] = 1;

                                    if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                        ans = dp[act][newSt];
                                }

                                if (0 == upSt && '#' == calendar[row - 1][col])
                                {
                                    setVal4St(newSt, col, 0);
                                    if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                                    {
                                        dp[act][newSt] = dp[1 - act][st];
                                        flag[act][newSt] = 1;

                                        if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                            ans = dp[act][newSt];
                                    }
                                }
                            }
                        }
                        else
                        {
                            setVal4St(newSt, col, 0);
                            if (0 == flag[act][newSt] || dp[act][newSt] > dp[1 - act][st])
                            {
                                dp[act][newSt] = dp[1 - act][st];
                                flag[act][newSt] = 1;

                                if (row == n - 1 && col == m - 1 && ans > dp[act][newSt])
                                    ans = dp[act][newSt];
                            }
                        }
                    }
                }
            }

            act = 1 - act;
        }
    }

    cout << ans << "\n";

    return 0;
}
