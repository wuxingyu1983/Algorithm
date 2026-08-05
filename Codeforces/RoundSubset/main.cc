// https://codeforces.com/contest/837/problem/D

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

const int MAXN = 201;
const int mask = 16383;
const int DIGITS = 14;
vector<int> cnt2, cnt5;
unordered_set<int> dp[MAXN];      // dp[k]
unordered_map<int, int> idxs;
int offset2[MAXN][12800];           // 个数k的子集，cnt2 - cnt5 = offset，相同 offset 下最大的 cnt2 和 cnt5 的组合
int offset5[MAXN][12800];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        long long a;
        cin >> a;

        long long tmp = a;
        int c2 = 0;
        while (tmp % 2 == 0)
        {
            c2++;
            tmp /= 2;
        }
        
        tmp = a;
        int c5 = 0;
        while (tmp % 5 == 0)
        {
            c5++;
            tmp /= 5;
        }

        if (0 < c2 || 0 < c5)
        {
            cnt2.push_back(c2);
            cnt5.push_back(c5);
        }
    }

    int ans = 0;
    int n1 = cnt2.size();
    int n0 = n - n1;
    for (int i = 0; i < n1; i++)
    {
        for (int j = min(k - 1, i); j >= max(k - n0 + i - n1, 0); j--)
        {
            for (auto it = dp[j].begin(); it != dp[j].end(); it++)
            {
                int old2 = *it >> DIGITS;
                int old5 = *it & mask;
                int new2 = old2 + cnt2[i];
                int new5 = old5 + cnt5[i];
                int newKey = new2 << DIGITS | new5;

                if (new2 - new5 >= 0)
                {
                    if (offset2[j + 1][new2 - new5] >= newKey)
                    {
                        continue;
                    }
                    else
                    {
                        if (0 < offset2[j + 1][new2 - new5])
                        {
                            dp[j + 1].erase(offset2[j + 1][new2 - new5]);
                        }
                    }
                }
                else
                {
                    if (offset5[j + 1][new5 - new2] >= newKey)
                    {
                        continue;
                    }
                    else
                    {
                        if (0 < offset5[j + 1][new5 - new2])
                        {
                            dp[j + 1].erase(offset5[j + 1][new5 - new2]);
                        }
                    }
                }

                if (0 == idxs.count(newKey) || idxs[newKey] > j + 1)
                {
                    if (0 < idxs.count(newKey))
                    {
                        dp[idxs[newKey]].erase(newKey);
                    }

                    idxs[newKey] = j + 1;
                    if (j + 1 < k)
                    {
                        dp[j + 1].insert(newKey);

                        if (new2 - new5 >= 0)
                        {
                            offset2[j + 1][new2 - new5] = newKey;
                        }
                        else
                        {
                            offset5[j + 1][new5 - new2] = newKey;
                        }
                    }
                    if (j + 1 + n0 >= k)
                    {
                        ans = max(ans, min(new2, new5));
                    }
                }
            }

            if (0 == j)
            {
                // Add the current number as a new subset of size 1
                int newKey = (cnt2[i] << DIGITS) + cnt5[i];
                if (0 == idxs.count(newKey) || idxs[newKey] > j + 1)
                {
                    if (0 < idxs.count(newKey))
                    {
                        dp[idxs[newKey]].erase(newKey);
                    }

                    idxs[newKey] = j + 1;
                    if (j + 1 < k)
                    {
                        dp[j + 1].insert(newKey);
                    }
                    if (j + 1 + n0 >= k)
                    {
                        ans = max(ans, min(cnt2[i], cnt5[i]));
                    }
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
