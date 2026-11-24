// https://atcoder.jp/contests/abc221/tasks/abc221_g

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

const int MAXN = 2001;
// 2000 x 7200000 / 8 太大了，超过 1GB 了，分段计算
vector<bitset<7200001>> dp(1001);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;

    int sum = 0;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
        sum += d[i];
    }

    if (sum < abs(a) + abs(b))
    {
        cout << "No" << "\n";
        return 0;
    }

    int p = a + b + 3600000;
    int q = a - b + 3600000;
    vector<char> ans;
    if (1000 < n)
    {
        // 2 段
        dp[0][3600000] = 1;
        for (int i = 1; i <= n - 1000; i++)
        {
            dp[i] = dp[i - 1] << d[i];
            dp[i] |= dp[i - 1] >> d[i];
        }

        dp[0] = dp[n - 1000];
        for (int i = 1; i <= 1000; i++)
        {
            int j = i + n - 1000;
            dp[i] = dp[i - 1] << d[j];
            dp[i] |= dp[i - 1] >> d[j];
        }
 
        if (dp[1000][p] && dp[1000][q])
        {
            int preP = p;
            int preQ = q;

            for (int i = 1000; i > 0; i--)
            {
                int j = i + n - 1000;
                int type = 0;
                if (0 <= preP - d[j] && dp[i - 1][preP - d[j]])
                {
                    preP -= d[j];
                    type += 0;
                }
                else if (7200000 >= preP + d[j] && dp[i - 1][preP + d[j]])
                {
                    preP += d[j];
                    type += 1;
                }

                if (0 <= preQ - d[j] && dp[i - 1][preQ - d[j]])
                {
                    preQ -= d[j];
                    type += 0;
                }
                else if (7200000 >= preQ + d[j] && dp[i - 1][preQ + d[j]])
                {
                    preQ += d[j];
                    type += 2;
                }

                switch (type)
                {
                case 0:
                    ans.push_back('R');
                    break;
                case 1:
                    ans.push_back('D');
                    break;
                case 2:
                    ans.push_back('U');
                    break;
                case 3:
                default:
                    ans.push_back('L');
                    break;
                }
            }

            dp[0].reset();
            dp[0][3600000] = 1;
            for (int i = 1; i <= n - 1000; i++)
            {
                dp[i] = dp[i - 1] << d[i];
                dp[i] |= dp[i - 1] >> d[i];
            }

            for (int i = n - 1000; i > 0; i--)
            {
                int type = 0;
                if (0 <= preP - d[i] && dp[i - 1][preP - d[i]])
                {
                    preP -= d[i];
                    type += 0;
                }
                else if (7200000 >= preP + d[i] && dp[i - 1][preP + d[i]])
                {
                    preP += d[i];
                    type += 1;
                }

                if (0 <= preQ - d[i] && dp[i - 1][preQ - d[i]])
                {
                    preQ -= d[i];
                    type += 0;
                }
                else if (7200000 >= preQ + d[i] && dp[i - 1][preQ + d[i]])
                {
                    preQ += d[i];
                    type += 2;
                }

                switch (type)
                {
                case 0:
                    ans.push_back('R');
                    break;
                case 1:
                    ans.push_back('D');
                    break;
                case 2:
                    ans.push_back('U');
                    break;
                case 3:
                default:
                    ans.push_back('L');
                    break;
                }
            }
        }
    }
    else
    {
        dp[0][3600000] = 1;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = dp[i - 1] << d[i];
            dp[i] |= dp[i - 1] >> d[i];
        }

        if (dp[n][p] && dp[n][q])
        {
            int preP = p;
            int preQ = q;

            for (int i = n; i > 0; i--)
            {
                int type = 0;
                if (0 <= preP - d[i] && dp[i - 1][preP - d[i]])
                {
                    preP -= d[i];
                    type += 0;
                }
                else if (7200000 >= preP + d[i] && dp[i - 1][preP + d[i]])
                {
                    preP += d[i];
                    type += 1;
                }

                if (0 <= preQ - d[i] && dp[i - 1][preQ - d[i]])
                {
                    preQ -= d[i];
                    type += 0;
                }
                else if (7200000 >= preQ + d[i] && dp[i - 1][preQ + d[i]])
                {
                    preQ += d[i];
                    type += 2;
                }

                switch (type)
                {
                case 0:
                    ans.push_back('R');
                    break;
                case 1:
                    ans.push_back('D');
                    break;
                case 2:
                    ans.push_back('U');
                    break;
                case 3:
                default:
                    ans.push_back('L');
                    break;
                }
            }
        }
    }

    if (0 == ans.size())
    {
        cout << "No" << "\n";
    }
    else
    {
        cout << "Yes" << "\n";
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i];
        }
        cout << "\n";
    }

    return 0;
}
