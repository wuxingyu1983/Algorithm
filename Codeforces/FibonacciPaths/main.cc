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
            cin >> edges[i].u >> edges[i].v;
        }


    }

    return 0;
}
