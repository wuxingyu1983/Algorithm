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

void func1(int curr, int parent, int &one, int &zero, vector<int> &flags, vector<int> &ans)
{
    if (1 == flags[curr])
        ans[curr] = one ++;
    else
        ans[curr] = zero --;

    for (size_t i = 0; i < vertices[curr].size(); i++)
    {
        if (parent != vertices[curr][i])
            func1(vertices[curr][i], curr, one, zero, flags, ans);
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

        int ones = 0;
        for (size_t i = 1; i <= n; i++)
        {
            if (flags[i])
            {
                ones ++;
            }
        }
        
        int one = n - ones + 1;
        int zero = n - ones;

        vector<int> ans(n + 1, 0);

        func1(1, 0, one, zero, flags, ans);

        cout << "Yes\n";
        for (size_t i = 1; i <= n; i++)
        {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
