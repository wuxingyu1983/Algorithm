// https://codeforces.com/contest/95/problem/E

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

const int MAXN = 1e5 + 1;
vector<bool> is_lucky(MAXN, true);
vector<vector<int>> roads(MAXN);
vector<unordered_set<int>> groups(MAXN);
vector<int> belong(MAXN, 0);

void dfs(int u, int parent, int group_id)
{
    if (0 == belong[u])
    {
        belong[u] = group_id;
        groups[group_id].insert(u);
    }

    for (int v : roads[u])
    {
        if (v != parent && belong[v] == 0)
        {
            dfs(v, u, group_id);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        if (u != v)
        {
            roads[u].push_back(v);
            roads[v].push_back(u);
        }
    }

    // init
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        while (x > 0)
        {
            int digit = x % 10;
            if (digit != 4 && digit != 7)
            {
                is_lucky[i] = false;
                break;
            }
            x /= 10;
        }
    }

    int group_id = 1;
    for (int i = 1; i <= n; i++)
    {
        if (0 == belong[i])
        {
            belong[i] = group_id;
            groups[group_id].insert(i);

            for (int j : roads[i])
            {
                dfs(j, i, group_id);
            }

            group_id ++;
        }
    }

    vector<int> group_sizes;
    for (int i = 1; i < group_id; i++)
    {
        group_sizes.push_back(groups[i].size());
    }

    sort(group_sizes.begin(), group_sizes.end());
    group_sizes.push_back(0); // sentinel

    vector<int> dp(n + 1, -1);
    int ans = -1;
    dp[0] = 0;

    int pre = 0;
    int cnt = 0;
    for (int i = 0; i < group_sizes.size(); i++)
    {
        if (pre != group_sizes[i])
        {
            int step = 1;
            while (step <= cnt)
            {
                for (int j = n; j >= 0; j--)
                {
                    if (0 <= dp[j])
                    {
                        int x = j + step * pre;
                        if (x <= n)
                        {
                            if (-1 == dp[x])
                            {
                                if (0 == j)
                                {
                                    dp[x] = step - 1;
                                }
                                else
                                {
                                    dp[x] = dp[j] + step;
                                }
                            }
                            else
                            {
                                if (0 == j)
                                {
                                    dp[x] = min(dp[x], step - 1);
                                }
                                else
                                {
                                    dp[x] = min(dp[x], dp[j] + step);
                                }
                            }

                            if (is_lucky[x])
                            {
                                if (-1 == ans)
                                {
                                    ans = dp[x];
                                }
                                else
                                {
                                    ans = min(ans, dp[x]);
                                }
                            }
                        }
                    }
                }
                
                cnt -= step;
                step <<= 1;
            }

            if (0 < cnt)
            {
                for (int j = n; j >= 0; j--)
                {
                    if (0 <= dp[j])
                    {
                        int x = j + cnt * pre;
                        if (x <= n)
                        {
                            if (-1 == dp[x])
                            {
                                if (0 == j)
                                {
                                    dp[x] = cnt - 1;
                                }
                                else
                                {
                                    dp[x] = dp[j] + cnt;
                                }
                            }
                            else
                            {
                                if (0 == j)
                                {
                                    dp[x] = min(dp[x], cnt - 1);
                                }
                                else
                                {
                                    dp[x] = min(dp[x], dp[j] + cnt);
                                }
                            }

                            if (is_lucky[x])
                            {
                                if (-1 == ans)
                                {
                                    ans = dp[x];
                                }
                                else
                                {
                                    ans = min(ans, dp[x]);
                                }
                            }
                        }
                    }
                }
            }

            pre = group_sizes[i];
            cnt = 1;
        }
        else
        {
            cnt++;
        }
    }

    cout << ans << "\n";

    return 0;
}
