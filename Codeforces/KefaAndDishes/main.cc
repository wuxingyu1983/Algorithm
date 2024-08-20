// https://codeforces.com/problemset/problem/580/D

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

#define DEBUG 0
#define MAX_NM 18
#define MAX_2N 262144
#define ST_BITS 1
#define ST_MASK 1

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

long long dp[2][MAX_NM][MAX_2N];
vector<long long> as;
long long cs[MAX_NM][MAX_NM];

int n, m, k;
long long ans = 0;

int main()
{
    cin >> n >> m >> k;

    for (size_t i = 0; i < n; i++)
    {
        long long a;
        cin >> a;
        as.push_back(a);
    }
    
    for (size_t i = 0; i < k; i++)
    {
        unsigned int x, y;
        long long c;

        cin >> x >> y >> c;

        cs[x - 1][y - 1] = c;
    }

    // init
    unsigned int maxSt = (1 << n) - 1;

    int act = 0, nAct;
    memset(dp, -1, sizeof(dp));

    for (size_t i = 0; i < n; i++)
    {
        unsigned int st = 1 << i;
        dp[act][i][st] = as[i];
        if (ans < as[i])
        {
            ans = as[i];
        }
    }


    for (size_t i = 1; i < m; i++)
    {
        nAct = 1 - act;

        for (size_t lastDish = 0; lastDish < n; lastDish++)
        {
            for (size_t st = 0; st <= maxSt; st++)
            {
                if (0 <= dp[act][lastDish][st])
                {
                    for (size_t dish = 0; dish < n; dish++)
                    {
                        if (0 == getVal4St(st, dish, ST_BITS, ST_MASK))
                        {
                            unsigned int newSt = st;
                            long long tmp = dp[act][lastDish][st];

                            setVal4St(newSt, dish, 1, ST_BITS, ST_MASK);

                            tmp += as[dish];
                            tmp += cs[lastDish][dish];

                            if (tmp > dp[nAct][dish][newSt])
                            {
                                dp[nAct][dish][newSt] = tmp;
                                if (ans < tmp)
                                {
                                    ans = tmp;
                                }
                            }
                        }
                    }
                }
            }
        }

        memset(dp[act], -1, sizeof(dp[act]));
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
