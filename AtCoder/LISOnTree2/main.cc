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

vector<vector<int>> vertices;
vector<int> subtrees;
long long minK = 0, maxK = 0;

int getSubtrees(int curr, int parent)
{
    int ret = 0;

    for (size_t i = 0; i < vertices[curr].size(); i++)
    {
        if (parent != vertices[curr][i])
        {
            ret += getSubtrees(vertices[curr][i], curr);
        }
    }

    ret += 1;
    subtrees[curr] = ret;
    maxK += ret;

    return ret;
}

void func(int curr, int parent, vector<int> &flags, long long &remain)
{
    if (subtrees[curr] == remain)
    {
        flags[curr] = 1;
        remain = 0;
    }
    else
    {
        if (subtrees[curr] < remain)
        {
            flags[curr] = 1;
            remain -= subtrees[curr];
        }

        for (size_t i = 0; i < vertices[curr].size(); i++)
        {
            if (parent != vertices[curr][i])
            {
                func(vertices[curr][i], curr, flags, remain);

                if (0 == remain)
                {
                    return;
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;

    cin >> n >> k;

    vertices.resize(n + 1);

    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        vertices[u].push_back(v);
        vertices[v].push_back(u);
    }

    subtrees.resize(n + 1, 0);

    getSubtrees(1, 0);
    minK = n;

    if (k < minK || k > maxK)
    {
        cout << "No\n";
    }
    else
    {
        long long remain = k;
        vector<int> flags(n + 1, 0);

        func(1, 0, flags, remain);
    }

    return 0;
}
