// https://codeforces.com/problemset/problem/11/D

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
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

using namespace std;

#define DEBUG 0
#define MAX_N 19
#define MAX_2N 524288
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 1000000

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

class Record
{
public:
    unsigned int state;
    unsigned char head;  // 该 path 的起点
    unsigned char tail;    // 该 path 的终点
    unsigned long long cnt;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
int cnts[2][MAX_2N][MAX_N];
int act = 0; // 当前生效的 map

int n, m;

char edges[MAX_N][MAX_N];

inline void addSts(unsigned int st, unsigned char head, unsigned char tail, unsigned long long cnt, int idx)
{
    int it = cnts[idx][st][tail];
    if (0 > it)
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = st;
        qs[idx][pInQ].head = head;
        qs[idx][pInQ].tail = tail;
        qs[idx][pInQ].cnt = cnt;

        cnts[idx][st][tail] = pInQ;
        qTail[idx]++;
    }
    else
    {
        qs[idx][it].cnt += cnt;
    }
}

int main()
{
    cin >> n >> m;

    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a --;
        b --;

        edges[a][b] = 1;
        edges[b][a] = 1;
    }
    
    // init
    qTail[0] = 0;
    qTail[1] = 0;
    memset(cnts, -1, sizeof(cnts));

    for (size_t pos = 0; pos < n; pos++)
    {
        addSts(1 << pos, pos, pos, 1, act);
    }

    int maxLen = 0;
    int round = 0;

    unsigned long long ans = 0;

    while (qTail[act])
    {
/*
        printf("round %d => %d\n", round ++, qTail[act]);
        if (maxLen < qTail[act])
        {
            maxLen = qTail[act];
        }
*/
        int nAct = 1 - act;

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st = qs[act][iQ].state;
            unsigned char head = qs[act][iQ].head;
            unsigned char tail = qs[act][iQ].tail;
            unsigned long long cnt = qs[act][iQ].cnt;

            if (head != tail)
            {
                if (edges[head][tail])
                {
                    ans += cnt;
                }
            }

            for (size_t v = head + 1; v < n; v++)
            {
                if (edges[tail][v] && 0 == getVal4St(st, v, ST_BITS, ST_MASK))
                {
                    addSts(st | (1 << v), head, v, cnt, nAct);
                }
            }
            
        }

        qTail[act] = 0;
        memset(cnts[act], -1, sizeof(cnts[act]));
        act = nAct;
    }

    cout << (ans - m) / 2 << endl;
//    cout << maxLen << endl;

    return 0;
}
