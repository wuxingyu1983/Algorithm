// https://atcoder.jp/contests/agc024/tasks/agc024_b

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

const int MAX_N = 200002;
int P[MAX_N];
int dp[MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        cin >> P[i];
    }
    
    int ans = 0;

    for (size_t i = 0; i < n; i++)
    {
        dp[P[i]] = dp[P[i] - 1] + 1;
        ans = max(ans, dp[P[i]]);
    }

    cout << n - ans << "\n";

    return 0;
}
