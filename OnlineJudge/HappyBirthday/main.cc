// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3153

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

const int MAX_N = 501;
int dp[MAX_N][MAX_N];     // dp[bottom][top]
char flag[MAX_N];

void deduplication(vector<int> &vec)
{
    sort(vec.begin(), vec.end());               // 先对vector进行排序
    auto last = unique(vec.begin(), vec.end()); // 去除重复的元素
    vec.erase(last, vec.end());                 // 删除多余的元素
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> ks, tmps;
    ks.reserve(MAX_N);
    tmps.reserve(MAX_N);

    for (;;)
    {
        int n;
        cin >> n;

        if (0 == n)
            break;
        
        ks.clear();
        tmps.clear();
        for (size_t i = 0; i < n; i++)
        {
            int k;
            cin >> k;

            ks.push_back(k);
            tmps.push_back(k);
        }

        deduplication(tmps);

        for (size_t i = 0; i < n; i++)
        {
            auto it = lower_bound(tmps.begin(), tmps.end(), ks[i]);
            ks[i] = it - tmps.begin() + 1;
        }

        memset(dp, 0, sizeof(dp));
        memset(flag, 0, sizeof(flag));

        // init
        int maxK = tmps.size();
        dp[ks[0]][ks[0]] = 1;
        flag[ks[0]] = 1;

        int ans = 1;

        for (size_t i = 1; i < n; i++)
        {
            for (int bottom = maxK; bottom >= ks[i]; bottom--)
            {
                if (flag[bottom])
                {
                    // dp[bottom][top] => dp[bottom][ks[i]]
                    if (dp[bottom][ks[i]])
                        dp[bottom][ks[i]] += 1;
                    
                    for (int top = ks[i] + 1; top <= bottom; top++)
                    {
                        if (dp[bottom][top])
                            dp[bottom][ks[i]] = max(dp[bottom][ks[i]], dp[bottom][top] + 1);
                    }
                    
                    if (ans < dp[bottom][ks[i]])
                        ans = dp[bottom][ks[i]];
                }
            }

            for (int bottom = ks[i] - 1; bottom >= 1; bottom--)
            {
                if (flag[bottom])
                {
                    // dp[bottom][top] => dp[ks[i]][top]
                    for (int top = 1; top <= bottom; top++)
                    {
                        if (dp[bottom][top])
                        {
                            dp[ks[i]][top] = max(dp[ks[i]][top], dp[bottom][top] + 1);
                            if (ans < dp[ks[i]][top])
                                ans = dp[ks[i]][top];
                        }
                    }

                    flag[ks[i]] = 1;
                }
            }
        }
        
        cout << ans << "\n";
    }

    return 0;
}
