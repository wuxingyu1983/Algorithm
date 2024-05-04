// https://www.luogu.com.cn/problem/P3959
// 状压DP

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>
#include <cstring>

using namespace std;

#define MAX_N 12
#define MAX_2N 4096
#define MAX_M 1000
#define QS_SIZE 100000

class Line
{
public:
    int connect;
    int length;

    Line(int _connect, int _length) : connect(_connect), length(_length) {}
};

short lines[MAX_N];

class Record
{
public:
    int state;  // layer + st1 + st2;
    int cost;
    
    Record() {}
};

Record qs[QS_SIZE];
int qHead, qTail;

#define IS_EMPTY (qHead == qTail)
#define IS_FULL (qHead == ((qTail + 1) % QS_SIZE))

unordered_map<int, int> mps[MAX_N];

int n, m;

void porcRecursively(int layer, int st1, int st2, int newSt, int startPos)
{
    if (startPos < n)
    {

    }
}

int main()
{
    cin >> n >> m;

    for (size_t i = 0; i < m; i++)
    {
        int src, dst, len;
        cin >> src >> dst >> len;

        // start from 0
        src --;
        dst --;

        lines[src] |= 1 << dst;
        lines[dst] |= 1 << src;
    }

    // init
    for (size_t i = 0, st = 1; i < n; i++, st <<= 1)
    {
        qs[qTail].state = st | (st << n);
        qTail++;
    }

    while (false == IS_EMPTY)
    {
        int layer = (qs[qHead].state >> (2 * n)) & 0xf;
        int st1 = (qs[qHead].state >> n) & ((1 << n) - 1);
        int st2 = qs[qHead].state & ((1 << n) - 1);

        if (0 < layer && 0 > mps[layer - 1].size())
        {
            mps[layer - 1].clear();
        }

        // 递归处理
        porcRecursively(layer, st1, st2, 0, 0);

        qHead++;
        if (QS_SIZE <= qHead)
            qHead -= QS_SIZE;
    }

    int ans = -1;

    cout << ans << endl;

    return 0;
}
