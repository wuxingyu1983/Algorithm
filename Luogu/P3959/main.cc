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

//int mps[MAX_N][MAX_2N][MAX_2N];
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
                        if (0 > v || (0 < length[pos][j] && v > length[pos][j]))
                        {
                            v = length[pos][j];
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

                        if (0 > mps[layer + 1][st1][newSt] || qs[mps[layer + 1][st1][newSt]].key != key)
                        {
                            int pInQ = qTail;
                            qs[pInQ].key = key;
                            qs[pInQ].layer = layer + 1;
                            qs[pInQ].st1 = st1;
                            qs[pInQ].st2 = newSt;
                            qs[pInQ].cost = cost;

                            mps[layer + 1][st1][newSt] = pInQ;

                            qTail++;
                            if (QS_SIZE <= qTail)
                                qTail -= QS_SIZE;
                            
                            if (IS_FULL)
                                cout << "FULL" << endl;
                        }
                        else
                        {
                            if (qs[mps[layer + 1][st1][newSt]].cost > cost)
                            {
                                qs[mps[layer + 1][st1][newSt]].cost = cost;
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

        if (0 == length[src][dst] || len < length[src][dst])
        {
            length[src][dst] = len;
            length[dst][src] = len;
        }
    }

    // init
    for (size_t i = 0, st = 1; i < n; i++, st <<= 1)
    {
        qs[qTail].key = st | (st << n);
        qs[qTail].st1 = qs[qTail].st2 = st;
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

        if (mps[layer])
        {
            delete[] mps[layer];
            mps[layer] = NULL;
        }

        if (NULL == mps[layer + 1])
        {
            mps[layer + 1] = new int[MAX_2N][MAX_2N];
            memset(mps[layer + 1], -1, sizeof(int) * MAX_2N * MAX_2N);
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
