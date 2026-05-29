// https://atcoder.jp/contests/arc175/tasks/arc175_d

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
#include <unordered_map>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;

    cin >> n >> k;

    vector<vector<int>> vertices(n + 1);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        vertices[u].push_back(v);
        vertices[v].push_back(u);
    }

    return 0;
}
