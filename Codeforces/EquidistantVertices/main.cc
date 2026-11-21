// https://codeforces.com/problemset/problem/1551/F

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

const long long MOD = 1000000007;
const int MAXN = 101;
long long C[MAXN][MAXN];

void init()
{
    for (size_t n = 0; n < MAXN; n++)
    {
        for (size_t m = 0; m <= n; m++)
        {
            if (0 == m || m == n)
            {
                C[n][m] = 1;
            }
            else
            {
                C[n][m] = C[n - 1][m] + C[n - 1][m - 1];
                C[n][m] %= MOD;
            }
        }
    }
}

void bfs(vector<vector<int>> &inVec, vector<vector<int>> &outVec, vector<bool> &flags)
{

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int t;
    cin >> t;

    while (t --)
    {
        string empty;
        getline(cin, empty);

        int n, k;
        cin >> n >> k;

        vector<vector<int>> edges(n + 1);
        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;

            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        long long ans = 0;

        if (2 == k)
        {
            ans = C[n][2];
        }
        else
        {
            vector<vector<int>> groups[2];
            for (int node = 1; node <= n; node++)
            {
                // init
                vector<bool> flags(n + 1, false);
                flags[node] = true;
                int curr = 1;
                groups[curr].clear();
                for (int i = 0; i < edges[node].size(); i++)
                {
                    groups[curr].push_back(vector<int>(1, edges[node][i]));
                    flags[edges[node][i]] = true;
                }

                if (k <= groups[curr].size())
                {
                    ans += C[groups[curr].size()][k];
                }

                for (int len = 1; len <= n; len++)
                {
                    if (k > groups[curr].size())
                    {
                        break;
                    }

                    groups[1 - curr].clear();

                    bfs(groups[curr], groups[1 - curr], flags);

                    curr = 1 - curr;
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
