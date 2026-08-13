// https://atcoder.jp/contests/abc321/tasks/abc321_f

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

const long long MOD = 998244353;
const int MAXK = 5001;
long long dp[MAXK];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        char op;
        int x;
        cin >> op >> x;

        if (op == '+')
        {
            for (int j = k; j >= x; j--)
            {
                dp[j] = (dp[j] + dp[j - x]) % MOD;
            }
            dp[x]++;
        }
        else
        {
            dp[x]--;
            for (int j = x; j <= k; j++)
            {
                if (0 < dp[j])
                    dp[j] = (MOD + dp[j] - dp[j - x]) % MOD;
            }
        }

        cout << dp[k] << "\n";
    }

    return 0;
}
