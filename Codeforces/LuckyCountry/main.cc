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
    for (int v : roads[u])
    {
        if (v != parent && belong[v] == 0)
        {
            belong[v] = group_id;
            groups[group_id].insert(v);
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

        roads[u].push_back(v);
        roads[v].push_back(u);
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
    

    return 0;
}
