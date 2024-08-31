// https://codeforces.com/problemset/problem/165/E
// SOS DP
// https://codeforces.com/blog/entry/45223

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

#define MAX_N 1000000
#define MAX_A 4194304

#define ST_BITS 1
#define ST_MASK 1

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

int dp[MAX_A];

int n;
vector<int> as;

int main()
{
    cin >> n;

    // init
    memset(dp, -1, sizeof(dp));

    int maxNum = (1 << 22) - 1;

    for (size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        as.push_back(a);

        dp[a] = a;
    }

    for (int i = 1; i <= 22; ++i)
    {
        for (int mask = 0; mask <= maxNum; ++mask)
        {
            if (mask & (1 << (i - 1)))
            {
                if (0 <= dp[mask ^ (1 << (i - 1))])
                {
                    dp[mask] = dp[mask ^ (1 << (i - 1))];
                }
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        cout << dp[maxNum - as[i]] << ' ';
    }
    cout << endl;

    return 0;
}
