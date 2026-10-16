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

    Edge(int _u, int _v):u(_u), v(_v){}
    Edge():u(0), v(0){}
};

class Vertex
{
public:
    int id;
    long long value;

    Vertex(int _id, long long _value):id(_id), value(_value){}
};

class Item
{
public:
    int curr;
    long long need;

    Item(int _curr, long long _need):curr(_curr), need(_need){}

    bool operator<(const Item& other) const {
        if (curr != other.curr)
            return curr < other.curr;
        return need < other.need;
    }
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
        vector<vector<Vertex>> vertices(n + 1);
        for (int i = 0; i < m; i++)
        {
            cin >> edges[i].v >> edges[i].u;

            vertices[edges[i].v].push_back(Vertex(edges[i].u, a[edges[i].u]));
        }

        // sort
        for (int i = 1; i <= n; i++)
        {
            if (0 < vertices[i].size())
            {
                sort(vertices[i].begin(), vertices[i].end(), [](const Vertex &v1, const Vertex &v2)
                     { return v1.value < v2.value; });
            }
        }

        long long ans = 0;

        // init
        vector<map<Item, long long>> dp(2);
        int act = 0;

        for (int i = 0; i < m; i++)
        {
            auto vit = lower_bound(vertices[edges[i].u].begin(), vertices[edges[i].u].end(), Vertex(0, a[edges[i].u] + a[edges[i].v]), [](const Vertex &v1, const Vertex &v2)
                               { return v1.value < v2.value; });

            if (vit == vertices[edges[i].u].end() || vit->value != a[edges[i].u] + a[edges[i].v])
            {
                continue;
            }

            Item key(edges[i].u, a[edges[i].u] + a[edges[i].v]);

            auto it = dp[act].find(key);

            if (it == dp[act].end())
            {
                dp[act][key] = 1;
            }
            else
            {
                it->second++;
            }
        }

        ans = m;

        act = 1 - act;

        while (dp[1 - act].size())
        {
            dp[act].clear();

            for (auto it = dp[1 - act].begin(); it != dp[1 - act].end(); it++)
            {
                int curr = it->first.curr;
                long long need = it->first.need;
                long long count = it->second;

                auto vit = lower_bound(vertices[curr].begin(), vertices[curr].end(), Vertex(0, need), [](const Vertex &v1, const Vertex &v2)
                                       { return v1.value < v2.value; });

                while (vit != vertices[curr].end() && vit->value == need)
                {
                    ans += count;
                    ans %= MOD;

                    auto tmpit = lower_bound(vertices[vit->id].begin(), vertices[vit->id].end(), Vertex(0, need + a[curr]), [](const Vertex &v1, const Vertex &v2)
                                       { return v1.value < v2.value; });

                    if (tmpit == vertices[vit->id].end() || tmpit->value != need + a[curr])
                    {
                        vit++;
                        continue;
                    }

                    Item key(vit->id, need + a[curr]);

                    auto it2 = dp[act].find(key);

                    if (it2 == dp[act].end())
                    {
                        dp[act][key] = count;
                    }
                    else
                    {
                        it2->second += count;
                        dp[act][key] %= MOD;
                    }

                    vit++;
                }
            }

            act = 1 - act;
        }

        cout << ans << "\n";
    }

    return 0;
}
