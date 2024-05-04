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
#define QS_SIZE 1000000

class Line
{
public:
    int connect;
    int length;

    Line(int _connect, int _length) : connect(_connect), length(_length) {}
};

int linesMask[MAX_N];
vector<Line> lines[MAX_N];

class Record
{
public:
    int state; // layer + st1 + st2;
    int cost;

    Record() {}
};

Record qs[QS_SIZE];
int qHead, qTail;

#define IS_EMPTY (qHead == qTail)
#define IS_FULL (qHead == ((qTail + 1) % QS_SIZE))

unordered_map<int, int> mps[MAX_N];

int n, m;
int ans;
int finalSt;

void procRecursively(int layer, int st1, int st2, int cost, int newSt, int startPos)
{
    for (size_t pos = startPos; pos < n; pos++)
    {
        if (0 == (st1 & (1 << pos)) && (st2 & linesMask[pos]))
        {
            // 在该 layer 可以挖掘该 pos
            // 不挖掘，留在以后
            procRecursively(layer, st1, st2, cost, newSt, pos + 1);

            // 挖掘
            {
                int v = -1;
                for (vector<Line>::iterator it = lines[pos].begin(); it != lines[pos].end(); it++)
                {
                    if (st2 & (1 << it->connect))
                    {
                        if (0 > v || v > it->length)
                        {
                            v = it->length;
                        }
                    }
                }

                st1 |= 1 << pos;
                newSt |= 1 << pos;
                cost += (layer + 1) * v;

                if (st1 == finalSt)
                {
                    if (0 > ans || ans > cost)
                    {
                        ans = cost;
                    }
                }
                else
                {
                    // add to queue
                    {
                        int key = ((layer + 1) << (2 * n)) | (st1 << n) | newSt;
                        unordered_map<int, int>::iterator it = mps[layer + 1].find(key);

                        if (it == mps[layer + 1].end() || qs[it->second].state != key)
                        {
                            int pInQ = qTail;
                            qs[pInQ].state = key;
                            qs[pInQ].cost = cost;

                            mps[layer + 1][key] = pInQ;

                            qTail++;
                            if (QS_SIZE <= qTail)
                                qTail -= QS_SIZE;
                        }
                        else
                        {
                            if (qs[it->second].cost > cost)
                            {
                                qs[it->second].cost = cost;
                            }
                        }
                    }

                    procRecursively(layer, st1, st2, cost, newSt, pos + 1);
                }
            }

            break;
        }
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
        src--;
        dst--;

        linesMask[src] |= 1 << dst;
        linesMask[dst] |= 1 << src;

        lines[src].push_back(Line(dst, len));
        lines[dst].push_back(Line(src, len));
    }

    // init
    for (size_t i = 0, st = 1; i < n; i++, st <<= 1)
    {
        qs[qTail].state = st | (st << n);
        qTail++;
    }
    ans = -1;
    finalSt = (1 << n) - 1;

    while (false == IS_EMPTY)
    {
        int layer = (qs[qHead].state >> (2 * n)) & 0xf;
        int st1 = (qs[qHead].state >> n) & ((1 << n) - 1);
        int st2 = qs[qHead].state & ((1 << n) - 1);
        int cost = qs[qHead].cost;

        if (0 < mps[layer].size())
        {
            mps[layer].clear();
        }

        // 递归处理
        procRecursively(layer, st1, st2, cost, 0, 0);

        qHead++;
        if (QS_SIZE <= qHead)
            qHead -= QS_SIZE;
    }

    if (0 > ans)
        ans = 0;

    cout << ans << endl;

    return 0;
}
