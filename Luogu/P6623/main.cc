// https://www.luogu.com.cn/problem/P6623

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

const int MAX_N = 525100;
const int MAX_NODES = 20 * MAX_N;
const int MAXH = 20;
int ch[MAX_NODES][2], w[MAX_NODES], xorv[MAX_NODES];
int tot = 0;

int vs[MAX_N];
vector<int> children[MAX_N];

int mknode()
{
    ++tot;
    ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
    return tot;
}

void maintain(int o)
{
    w[o] = xorv[o] = 0;
    if (ch[o][0])
    {
        w[o] += w[ch[o][0]];
        xorv[o] ^= xorv[ch[o][0]] << 1;
    }
    if (ch[o][1])
    {
        w[o] += w[ch[o][1]];
        xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
    }
    w[o] = w[o] & 1;
}

void insert(int &o, int x, int dp)
{
    if (!o)
        o = mknode();
    if (dp > MAXH)
        return (void)(w[o]++);
    insert(ch[o][x & 1], x >> 1, dp + 1);
    maintain(o);
}

void addall(int o)
{
    swap(ch[o][0], ch[o][1]);
    if (ch[o][0])
        addall(ch[o][0]);
    maintain(o);
}

int merge(int a, int b)
{
    if (!a)
        return b; // 如果 a 没有这个位置上的结点，返回 b
    if (!b)
        return a; // 如果 b 没有这个位置上的结点，返回 a
    /*
      如果 `a`, `b` 都存在，
      那就把 `b` 的信息合并到 `a` 上．
    */
    w[a] = w[a] + w[b];
    xorv[a] ^= xorv[b];
    /* 不要使用 maintain()，
      maintain() 是合并a的两个儿子的信息
      而这里需要 a b 两个节点进行信息合并
     */
    ch[a][0] = merge(ch[a][0], ch[b][0]);
    ch[a][1] = merge(ch[a][1], ch[b][1]);
    return a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (size_t i = 1; i <= n; i++)
    {
        cin >> vs[i];
    }
    
    for (size_t i = 2; i <= n; i++)
    {
        int parent;
        cin >> parent;

        children[parent].push_back(i);
        children[i].push_back(parent);
    }
    


    return 0;
}
