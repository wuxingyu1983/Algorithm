// https://codeforces.com/contest/1078/problem/B

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

using namespace std;

int dp[101][10005];
char flag[101][10005];
int cnt[101];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int sum = 0;
    int diff = 0;
    vector<int> a;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        sum += tmp;

        cnt[tmp]++;
        if (1 == cnt[tmp])
        {
            a.push_back(tmp);
            diff++;
        }
    }

    sort(a.begin(), a.end());

    if (diff < n)
    {
        for (int i = 0; i < a.size(); i++)
        {
            for (int j = i; j >= 1; j--)
            {
                for (int k = 1; k < sum; k++)
                {
                    if (0 < dp[j][k])
                    {
                        for (int l = 1; l <= cnt[a[i]]; l++)
                        {
                            dp[j + l][k + l * a[i]] += dp[j][k];

                            dp[j + l][k + l * a[i]] = min(10, dp[j + l][k + l * a[i]]);
                        }
                    }
                }
            }

            for (int l = 1; l <= cnt[a[i]]; l++)
            {
                dp[l][l * a[i]] +=1;

                dp[l][l * a[i]] = min(dp[l][l * a[i]], 10);
            }
        }
    }

    int ans = 1;

    if (2 == diff)
    {
        ans = n;
    }
    else
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (1 < cnt[a[i]])
            {
                for (int j = cnt[a[i]]; j > 1; j--)
                {
                    if (1 == dp[j][j * a[i]])
                    {
                        ans = max(ans, j);
                        break;
                    }
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
