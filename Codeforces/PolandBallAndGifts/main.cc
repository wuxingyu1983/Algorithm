// https://codeforces.com/contest/755/problem/F

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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }

    vector<char> flags(n + 1, 0);
    vector<int> rings(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        if (0 == flags[i])
        {
            int cnt = 0;
            int j = i;
            while (0 == flags[j])
            {
                flags[j] = 1;
                cnt++;

                j = p[j];
            }

            rings[cnt]++;
        }
    }

    // minimum
    {
        vector<int> dp(k + 1, -1);
        dp[k] = 0;
        for (int i = 2; i <= n; i++)
        {
            if (rings[i])
            {
                for (int j = 1; j <= k; j++)
                {
                    if (0 <= dp[j])
                    {
                        for (int r = 0; r < rings[i]; r++)
                        {
                            if (r * i > j)
                            {
                                break;
                            }

                            for (int l = 1; l <= i; l++)
                            {
                                if (l + r * i > j)
                                {
                                    break;
                                }

                                int tmp = dp[j] + r * i;
                                if (l == i)
                                {
                                    tmp += l;
                                }
                                else
                                {
                                    tmp += l + 1;
                                }

                                if (0 > dp[j - l - r * i] || dp[j - l - r * i] > tmp)
                                {
                                    dp[j - l - r * i] = tmp;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        cout << dp[0] << " ";
    }

    // maximum
    {
        // greedy
        int ans = 0;
        int tmp = k;
        int i = 2;
        while (tmp > 0)
        {
            while (n >= i && 0 == rings[i])
            {
                i ++;
            }

            if (n < i)
            {
                break;
            }

            {
                if ((i / 2) * rings[i] <= tmp)
                {
                    ans += (i / 2) * 2 * rings[i];
                    tmp -= (i / 2) * rings[i];
                }
                else
                {
                    ans += tmp * 2;
                    tmp = 0;
                }

                i ++;
            }
        }

        ans += min(tmp, n - ans);
        
        cout << ans << "\n";
    }

    return 0;
}
