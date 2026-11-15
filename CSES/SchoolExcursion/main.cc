// https://cses.fi/problemset/task/1706/

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
vector<vector<int>> children(MAXN);
vector<unordered_set<int>> groups(MAXN);
vector<int> belong(MAXN, 0);

void dfs(int u, int parent, int group_id)
{
    if (0 == belong[u])
    {
        belong[u] = group_id;
        groups[group_id].insert(u);
    }

    for (int v : children[u])
    {
        if (v != parent && belong[v] == 0)
        {
            dfs(v, u, group_id);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        children[a].push_back(b);
        children[b].push_back(a);
    }

    int group_id = 1;
    for (int i = 1; i <= n; i++)
    {
        if (0 == belong[i])
        {
            belong[i] = group_id;
            groups[group_id].insert(i);

            for (int j : children[i])
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
    bitset<MAXN> dp;
    dp[0] = 1;

    int pre = 0;
    int cnt = 0;
    for (int i = 0; i < group_sizes.size(); i++)
    {
        if (pre != group_sizes[i])
        {
            int step = 1;
            while (step <= cnt)
            {
                dp |= (dp << (step * pre));
                
                cnt -= step;
                step <<= 1;
            }

            if (0 < cnt)
            {
                dp |= (dp << (cnt * pre));
            }

            pre = group_sizes[i];
            cnt = 1;
        }
        else
        {
            cnt ++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (dp[i])
        {
            cout << "1";
        }
        else
        {
            cout << "0";
        }
    }
    cout << "\n";

    return 0;
}
