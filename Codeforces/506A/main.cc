// https://codeforces.com/problemset/problem/506/A

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
#include <deque>

using namespace std;

const int MAXN = 30001;

int islands[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d;
    cin >> n >> d;

    for (int i = 0; i < n; i++)
    {
        int loc;
        cin >> loc;

        islands[loc] ++;
    }

    int left = d;
    int right = d;

    int curr = 0;
    while (curr <= 30000)
    {
        curr += right;
        right += 1;
    }

    curr = 0;
    while (curr <= 30000 && left > 0)
    {
        curr += left;
        left -= 1;
    }

    int ans = 0;
    vector<vector<int>> dp(30001, vector<int>(right - left + 1, -1));
    // init
    dp[d][d - left] = islands[d];
    ans = islands[d];

    for (int i = d + 1; i < MAXN; i++)
    {
        for (int j = 0; j <= right - left; j++)
        {
            int stp = left + j;

            if (0 <= i - stp)
            {
                if (0 <= dp[i - stp][j])
                {
                    dp[i][j] = max(dp[i][j], dp[i - stp][j] + islands[i]);
                    ans = max(ans, dp[i][j]);
                }

                if (j - 1 >= 0 && 0 <= dp[i - stp][j - 1])
                {
                    dp[i][j] = max(dp[i][j], dp[i - stp][j - 1] + islands[i]);
                    ans = max(ans, dp[i][j]);
                }

                if (j + 1 <= right - left && 0 <= dp[i - stp][j + 1])
                {
                    dp[i][j] = max(dp[i][j], dp[i - stp][j + 1] + islands[i]);
                    ans = max(ans, dp[i][j]);
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
