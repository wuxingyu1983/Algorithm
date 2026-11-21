// https://codeforces.com/problemset/problem/1551/F

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
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

const long long MOD = 1000000007;
const int MAXN = 101;
long long C[MAXN][MAXN];

void init()
{
    for (size_t n = 0; n < MAXN; n++)
    {
        for (size_t m = 0; m <= n; m++)
        {
            if (0 == m || m == n)
            {
                C[n][m] = 1;
            }
            else
            {
                C[n][m] = C[n - 1][m] + C[n - 1][m - 1];
                C[n][m] %= MOD;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int t;
    cin >> t;

    while (t --)
    {
        string empty;
        getline(cin, empty);

        int n, k;
        cin >> n >> k;


    }

    return 0;
}
