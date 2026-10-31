// https://atcoder.jp/contests/agc020/tasks/agc020_c

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

bitset<4000002> dp;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    dp[0] = 1;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        dp |= dp << a;
        sum += a;
    }

    if (1 == n)
    {
        cout << sum << "\n";
    }
    else
    {
        int ans = 0;

        for (int i = 1; i <= sum / 2; i++)
        {
            if (dp[i])
            {
                ans = sum - i;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
