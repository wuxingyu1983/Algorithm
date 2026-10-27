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
#include <bitset>

using namespace std;

bitset<2000002> dp;

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
        vector<int> v;
        for (int i = 2; i <= n; i++)
        {
            if (rings[i])
            {
                int sum = rings[i];
                int tmp = 1;

                v.push_back(tmp * i);
                sum -= tmp;
                tmp <<= 1;

                while (tmp <= sum)
                {
                    v.push_back(tmp * i);
                    sum -= tmp;
                    tmp <<= 1;
                }
                
                if (0 < sum)
                {
                    v.push_back(sum * i);
                }
            }
        }

        dp[0] = 1;

        for (int i = 0; i < v.size(); i++)
        {
            dp |= dp << v[i];
        }
       
        if (0 < dp[k])
            cout << k << " ";
        else
            cout << k + 1 << " ";
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
