// https://atcoder.jp/contests/dp/tasks/dp_m

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

using namespace std;

const long long MOD = 1000000007;
const int MAXK = 100001;
const int MAXN = 100;

long long dp[MAXK];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        for (int j = k - 1; j >= 0; j--)
        {
            if (0 < dp[j])
            {
                for (int l = min(j + a, k); l > j; l--)
                {
                    dp[l] += dp[j];
                    dp[l] %= MOD;
                }
            }
        }
    }

    cout << dp[k] << "\n";

    return 0;
}
