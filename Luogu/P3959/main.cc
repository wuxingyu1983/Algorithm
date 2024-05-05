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
#define QS_SIZE 3000000

typedef int (*PPTR)[MAX_2N];

int linesMask[MAX_N];
int length[MAX_N][MAX_N];

class Record
{
public:
    int key; // layer + st1 + st2;
    unsigned char layer;
    short st1, st2;
    int cost;

    Record() {}
};

Record qs[QS_SIZE];
int qHead, qTail;

#define IS_EMPTY (qHead == qTail)
#define IS_FULL (qHead == ((qTail + 1) % QS_SIZE))

//unordered_map<int, int> mps[MAX_N];
PPTR mps[MAX_N];

int n, m;
int ans;
int finalSt;

void procRecursively(int layer, int st1, int st2, int cost, int newSt, int startPos)
{
    for (size_t pos = startPos; pos < n; pos++)
    {
        if (0 == (st1 & (1 << pos)) && (st2 & linesMask[pos]))
        {
            if (NULL == mps[layer])
            {
                mps[layer] = new int[MAX_2N][MAX_2N];
                memset(mps[layer], -1, sizeof(int) * MAX_2N * MAX_2N);
            }

            // 在该 layer 可以挖掘该 pos
            // 不挖掘，留在以后
            procRecursively(layer, st1, st2, cost, newSt, pos + 1);

            // 挖掘
            {
                int v = -1;

                for (size_t j = 0; j < n; j++)
                {
                    if (st2 & (1 << j))
                    {
                        if (0 > v || (0 <= length[pos][j] && v > length[pos][j]))
                        {
                            v = length[pos][j];
                        }
                    }
                }

                st1 |= 1 << pos;
                newSt |= 1 << pos;
                cost += layer * v;

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
                        int key = (layer << (2 * n)) | (st1 << n) | newSt;

//                        unordered_map<int, int>::iterator it = mps[layer].find(key);

//                        if (it == mps[layer + 1].end() || qs[it->second].key != key)
                        if (0 > mps[layer][st1][newSt] || qs[mps[layer][st1][newSt]].key != key)
                        {
                            int pInQ = qTail;
                            qs[pInQ].key = key;
                            qs[pInQ].layer = layer;
                            qs[pInQ].st1 = st1;
                            qs[pInQ].st2 = newSt;
                            qs[pInQ].cost = cost;

//                            mps[layer][key] = pInQ;
                            mps[layer][st1][newSt] = pInQ;

                            qTail++;
                            if (QS_SIZE <= qTail)
                                qTail -= QS_SIZE;

                            if (IS_FULL)
                                cout << "FULL" << endl;
                        }
                        else
                        {

                            if (qs[mps[layer][st1][newSt]].cost > cost)
                            {
                                qs[mps[layer][st1][newSt]].cost = cost;
                            }
/*
                            if (qs[it->second].cost > cost)
                            {
                                qs[it->second].cost = cost;
                            }
*/
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

    memset(length, -1, sizeof(length));

    for (size_t i = 0; i < m; i++)
    {
        int src, dst, len;
        cin >> src >> dst >> len;

        // start from 0
        src--;
        dst--;

        linesMask[src] |= 1 << dst;
        linesMask[dst] |= 1 << src;

        if (0 > length[src][dst] || len < length[src][dst])
        {
            length[src][dst] = len;
            length[dst][src] = len;
        }
    }

    // init
    for (size_t i = 0, st = 1; i < n; i++, st <<= 1)
    {
        qs[qTail].st1 = st;
        qs[qTail].st2 = st;
        qs[qTail].key = st | (st << n);
        qTail++;
    }
    ans = -1;
    finalSt = (1 << n) - 1;

    while (false == IS_EMPTY)
    {
        int layer = qs[qHead].layer;
        int st1 = qs[qHead].st1;
        int st2 = qs[qHead].st2;
        int cost = qs[qHead].cost;
        /*
                if (0 < mps[layer].size())
                {
                    mps[layer].clear();
                }
        */
        if (mps[layer])
        {
            delete[] mps[layer];
            mps[layer] = NULL;
        }

        // 递归处理
        procRecursively(layer + 1, st1, st2, cost, 0, 0);

        qHead++;
        if (QS_SIZE <= qHead)
            qHead -= QS_SIZE;
    }

    if (0 > ans)
        ans = 0;

    cout << ans << endl;

    return 0;
}
