// https://codeforces.com/problemset/problem/914/C

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
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

#pragma GCC target("popcnt")

const int mod = 1000000007;

int C[1001][1001];
int ops[1001];          // ops[num], num 到 1 需要的 op 数
int dp[1001][1001];

int main()
{
    string strN;
    int k;

    cin >> strN;
    cin >> k;

    // init
    {
        for (size_t i = 2; i <= 1000; i++)
        {
            ops[i] = 1 + ops[__builtin_popcount(i)];
        }
        
        for (size_t n = 1; n <= 1000; n++)
        {
            for (size_t m = 0; m <= n; m++)
            {
                if (0 == m || m == n)
                {
                    C[n][m] = 1;
                }
                else
                {
                    C[n][m] = C[n - 1][m] + C[n - 1][m-1];
                    C[n][m] %= mod;
                }
            }
        }
    }

    return 0;
}
