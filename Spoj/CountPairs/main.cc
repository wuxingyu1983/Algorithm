// https://www.spoj.com/problems/ILD18ACP/en/

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

const int MAXNM = 100001;

vector<vector<int>> neighbors(MAXNM);
vector<bitset<MAXNM>> adj(MAXNM);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        if (u != v)
        {
            if (!adj[u][v])
            {
                neighbors[u].push_back(v);
                neighbors[v].push_back(u);

                adj[u][v] = 1;
                adj[v][u] = 1;
            }
        }
    }

    return 0;
}
