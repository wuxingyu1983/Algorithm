// https://hydro.ac/p/bzoj-P1954

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
#include <map>

using namespace std;

const int MAX_NODES = 3000000;
const int MAX_N = 100005;

int cnt;
int nex[MAX_NODES][2];

void insert(const int w)
{ // 插入字符串
    int p = 0;
    for (int i = 30; i >= 0; i--)
    {
        int c = (w >> i) & 1;
        if (!nex[p][c])
            nex[p][c] = ++cnt; // 如果没有，就添加结点
        p = nex[p][c];
    }
}

int findMax(const int w)
{
    int ret = 0;
    int p = 0;
    for (int i = 30; i >= 0; i--)
    {
        int c = (w >> i) & 1;
        if (0 == nex[p][1 - c])
        {
            p = nex[p][c];
        }
        else
        {
            ret |= 1 << i;
            p = nex[p][1 - c];
        }
    }

    return ret;
}

vector<int> children[MAX_N];
vector<int> weights[MAX_N];
int lenToRoot[MAX_N];

void getLen(int curr, int parent)
{
    for (size_t i = 0; i < children[curr].size(); i++)
    {
        int child = children[curr][i];
        if (child != parent)
        {
            int w = weights[curr][i];
            lenToRoot[child] = lenToRoot[curr] ^ w;

            getLen(child, curr);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (size_t i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        children[u].push_back(v);
        children[v].push_back(u);

        weights[u].push_back(w);
        weights[v].push_back(w);
    }

    int root = 1;
    getLen(root, 0);

    for (size_t i = 2; i <= n; i++)
    {
        insert(lenToRoot[i]);
    }

    int max = 0;

    for (size_t i = 2; i <= n; i++)
    {
        int tmp = lenToRoot[i];
        if (tmp > max)
            max = tmp;
        tmp = findMax(lenToRoot[i]);
        if (tmp > max)
            max = tmp;
    }

    cout << max << "\n";

    return 0;
}
