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

class Node
{
public:
    int idx;
    int subtree;

    Node()
    {
        idx = subtree = 0;
    }
};

bool cmp(Node &a, Node &b)
{
    if (a.subtree <= b.subtree)
        return false;
    else
        return true;
}

vector<Node> nodes;

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
    nodes[curr].idx = curr;
    nodes[curr].subtree = ret;
    maxK += ret;

    return ret;
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
    nodes.resize(n + 1);

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
        sort(nodes.begin(), nodes.end(), cmp);

        long long remain = k;
        vector<int> flags(n + 1, 0);

        // greedy
        int ones = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (nodes[i].subtree == remain)
            {
                flags[nodes[i].idx] = 1;
                ones ++;
                remain = 0;
                break;
            }
            else if (nodes[i].subtree < remain)
            {
                flags[nodes[i].idx] = 1;
                ones ++;
                remain -= nodes[i].subtree;
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
