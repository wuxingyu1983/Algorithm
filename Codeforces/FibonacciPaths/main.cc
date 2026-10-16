// https://codeforces.com/contest/2176/problem/D

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

const long long MOD = 998244353;

class Edge
{
public:
    int u, v;
    long long next;

    Edge(int _u, int _v, long long _next):u(_u), v(_v), next(_next){}
    Edge():u(0), v(0), next(0){}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<long long> a(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }

        vector<Edge> edges(m);
        for (int i = 0; i < m; i++)
        {
            // v --> u
            cin >> edges[i].v >> edges[i].u;
            edges[i].next = a[edges[i].v] + a[edges[i].u];
        }

        // sort
        sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2) {
            return e1.next < e2.next;
        });
        
        // init
        vector<map<long long, long long>> dp(n + 1);

        long long ans = 0;
        ans = m;

        for (int i = 0; i < m; i++)
        {
            int v = edges[i].v;
            int u = edges[i].u;
            long long need = a[u];

            long long paths = 0;
            if (dp[v].find(need) != dp[v].end())
            {
                paths = dp[v][need];
            }
            
            dp[u][a[v] + a[u]] = (dp[u][a[v] + a[u]] + paths + 1) % MOD;

            ans += paths;
            ans %= MOD;
        }       


        cout << ans << "\n";
    }

    return 0;
}
