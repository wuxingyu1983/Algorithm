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

        cout << ans << "\n";
    }

    return 0;
}
