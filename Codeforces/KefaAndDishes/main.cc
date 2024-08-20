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
vector<unsigned int> as;
vector<unsigned int> xs;
vector<unsigned int> ys;
vector<unsigned int> cs;

int n, m, k;
long long ans = 0;

int main()
{
    cin >> n >> m >> k;

    for (size_t i = 0; i < n; i++)
    {
        unsigned int a;
        cin >> a;
        as.push_back(a);
    }
    
    for (size_t i = 0; i < k; i++)
    {
        unsigned int x, y, c;
        xs.push_back(x - 1);
        ys.push_back(y - 1);
        cs.push_back(c);
    }

    // init
    unsigned int maxSt = (1 << n) - 1;

    int act = 0, nAct;
    memset(dp, -1, sizeof(dp));

    for (size_t i = 0; i < n; i++)
    {
        unsigned short st = 1 << i;
        dp[act][i][st] = as[i];
        if (ans < as[i])
        {
            ans = as[i];
        }
    }
    

    cout << ans << endl;

    return 0;
}
