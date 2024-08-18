// https://codeforces.com/problemset/problem/53/E#

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
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

#define DEBUG   0
#define MAX_N   10
#define MAX_2N  1024
#define MAX_M   46

#define getVal4St(ST, POS) (((ST) >> (POS)) & 1)

#define setVal4St(ST, POS, VAL) \
    ST &= ~(1 << (POS));        \
    if (VAL)                    \
        ST |= (VAL) << (POS);

int dp[MAX_M][MAX_2N][MAX_2N];     // [st1][st2], st1 : 1 - 已经包含了；st2 : 1 - dead ends

int n, m, k;

int main()
{
    cin >> n >> m >> k;

    int finalSt = (1 << n) - 1;

    // init
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (size_t iM = 1; iM <= m; iM++)
    {
        int v1, v2;
        cin >> v1 >> v2;

        v1 --;
        v2 --;

        for (size_t st1 = 0; st1 <= finalSt; st1++)
        {
            for (size_t st2 = 0; st2 <= finalSt; st2++)
            {
                if (dp[iM - 1][st1][st2])
                {
                    int newSt1 = st1;
                    int newSt2 = st2;

                    if (getVal4St(st1, v1) && getVal4St(st1, v2))
                    {
                        // v1, v2 都已经包含了，忽略该 road
                    }
                    else if (getVal4St(st1, v1))
                    {
                        // unset st2 : v1
                        setVal4St(newSt2, v1, 0);

                        // set st1,st2 : v2
                        setVal4St(newSt1, v2, 1);
                        setVal4St(newSt2, v2, 1);

                        dp[iM][newSt1][newSt2] += dp[iM - 1][st1][st2];
                    }
                    else if (getVal4St(st1, v2))
                    {
                        // unset st2 : v2
                        setVal4St(newSt2, v2, 0);

                        // set st1,st2 : v1
                        setVal4St(newSt1, v1, 1);
                        setVal4St(newSt2, v1, 1);

                        dp[iM][newSt1][newSt2] += dp[iM - 1][st1][st2];
                    }
                    else
                    {
                        // set st1,st2 : v1
                        setVal4St(newSt1, v1, 1);
                        setVal4St(newSt2, v1, 1);

                        // set st1,st2 : v2
                        setVal4St(newSt1, v2, 1);
                        setVal4St(newSt2, v2, 1);

                        dp[iM][newSt1][newSt2] += dp[iM - 1][st1][st2];
                    }
                }
            }
        }
    }

    int ans = 0;

    for (size_t st2 = 0; st2 <= finalSt; st2++)
    {
        if (dp[m][finalSt][st2])
        {
            int tmp = 0;

            for (size_t pos = 0; pos < n; pos ++)
            {
                if (getVal4St(st2, pos))
                {
                    tmp ++;
                }
            }

            if (k == tmp)
            {
                ans += dp[m][finalSt][st2];
            }
        }
    }

    cout << ans << endl;

    return 0;
}
