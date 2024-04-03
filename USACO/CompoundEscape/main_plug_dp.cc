// https://usaco.org/index.php?page=viewproblem2&cpid=949&lang=zh
// https://hydro.ac/d/loj/p/P3769
// https://www.luogu.com.cn/problem/P5422

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

using namespace std;

#define DEBUG 0
#define MAX_H 30001
#define MAX_W 7
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 6000000
#define MOD 1000000007
#define MIN_START 2

class Record
{
public:
    unsigned int state; // 轮廓线段状态

    unsigned long long sum;
    unsigned long long count;
    unsigned char minUnused;

    Record() {}
};

unsigned long long rowGate[MAX_H][MAX_W];
unsigned long long colGate[MAX_W][MAX_H];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
int cnts[2097200];
int act = 0; // 当前生效的 map
int now_x, now_y;

class StMap
{
public:
    unsigned int recode;
    unsigned char minUnused;

    StMap() {}
};

StMap stMap[2097200];

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

// 最小表示法重编码
#define recode(ST, UNUSED)                    \
    if (0 == stMap[ST].minUnused)             \
    {                                         \
        int tmpSt = ST;                       \
        int bb[10];                           \
        int occ[10];                          \
        memset(bb, -1, sizeof(bb));           \
        memset(occ, 0, sizeof(occ));          \
        int bn = MIN_START;                   \
        bb[0] = 0;                            \
        int oneCnt = 0;                       \
        for (int i = 0; i <= w; i++)          \
        {                                     \
            int tmp = getVal4St(ST, i);       \
            if (1 < tmp)                      \
            {                                 \
                if (0 > bb[tmp])              \
                {                             \
                    bb[tmp] = bn++;           \
                }                             \
                setVal4St(ST, i, bb[tmp]);    \
                occ[bb[tmp]]++;               \
                if (1 == occ[bb[tmp]])        \
                    oneCnt++;                 \
                else if (2 == occ[bb[tmp]])   \
                    oneCnt--;                 \
            }                                 \
        }                                     \
        UNUSED = bn;                          \
        if (0 < oneCnt)                       \
        {                                     \
            for (int i = 0; i <= w; i++)      \
            {                                 \
                int tmp = getVal4St(ST, i);   \
                if (1 < tmp && 1 == occ[tmp]) \
                {                             \
                    setVal4St(ST, i, 1);      \
                }                             \
            }                                 \
        }                                     \
        stMap[tmpSt].recode = ST;             \
        stMap[tmpSt].minUnused = UNUSED;      \
    }                                         \
    else                                      \
    {                                         \
        UNUSED = stMap[ST].minUnused;         \
        ST = stMap[ST].recode;                \
    }

#define addSts(ST, SUM, CNT, IDX)                                                                            \
    unsigned char unused;                                                                                    \
    unsigned int recodedSt = ST;                                                                             \
    recode(recodedSt, unused);                                                                               \
    if (0 > cnts[recodedSt] || qTail[IDX] <= cnts[recodedSt] || qs[IDX][cnts[recodedSt]].state != recodedSt) \
    {                                                                                                        \
        int pInQ = qTail[IDX];                                                                               \
        qs[IDX][pInQ].state = recodedSt;                                                                     \
        qs[IDX][pInQ].sum = SUM;                                                                             \
        qs[IDX][pInQ].count = CNT;                                                                           \
        qs[IDX][pInQ].minUnused = unused;                                                                    \
        cnts[recodedSt] = pInQ;                                                                              \
        qTail[IDX]++;                                                                                        \
    }                                                                                                        \
    else                                                                                                     \
    {                                                                                                        \
        if (qs[IDX][cnts[recodedSt]].sum > SUM)                                                              \
        {                                                                                                    \
            qs[IDX][cnts[recodedSt]].sum = SUM;                                                              \
            qs[IDX][cnts[recodedSt]].count = CNT;                                                            \
        }                                                                                                    \
        else if (qs[IDX][cnts[recodedSt]].sum == SUM)                                                        \
        {                                                                                                    \
            qs[IDX][cnts[recodedSt]].count += CNT;                                                           \
            if (MOD <= qs[IDX][cnts[recodedSt]].count)                                                       \
                qs[IDX][cnts[recodedSt]].count -= MOD;                                                       \
        }                                                                                                    \
    }

int main()
{
    scanf("%d %d", &h, &w);

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col < w; col++)
        {
            scanf("%llu", &(rowGate[row][col]));
        }
    }

    for (size_t col = 1; col <= w; col++)
    {
        for (size_t row = 1; row < h; row++)
        {
            scanf("%llu", &(colGate[col][row]));
        }
    }

    // init
    act = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].sum = 0;
    qs[act][0].count = 1;
    qs[act][0].minUnused = MIN_START;

    memset(cnts, -1, sizeof(cnts));

    qTail[act]++;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;

        if (w == now_y)
        {
            now_x++;
            now_y = 1;

            if (h < now_x)
            {
                if (1 == qTail[act] && 0 == qs[act][0].state)
                {
                    printf("%llu\n", qs[act][0].count);
                }
                break;
            }
        }
        else
        {
            now_y++;
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st = qs[act][iQ].state;
            unsigned long long sum = qs[act][iQ].sum;
            unsigned long long cnt = qs[act][iQ].count;
            unsigned char newVal = qs[act][iQ].minUnused; // 延伸的值

            if (1 == now_y)
            {
                st <<= ST_BITS;
            }

            unsigned int left = getVal4St(st, now_y - 1);
            unsigned int up = getVal4St(st, now_y);

            bool flag = true;
            if (left && up)
            {
                // 就此打住
                if (1 == left && 1 == up)
                {
                    // 不延伸，只在最后一个 cell 有效
                    if (h == now_x && w == now_y)
                    {
                    }
                    else
                    {
                        // 非法，必须延伸
                        flag = false;
                    }
                }
                else if (1 == left || 1 == up)
                {
                    // 不延伸，不做任何操作
                    newVal = left + up - 1;
                }
                else
                {
                    // left 和 up 都不为 1
                    // 不延伸
                    if (left == up)
                    {
                        // 形成环了，延伸也不行
                        continue;
                    }

                    // up ==> left
                    for (int i = 0; i <= w; i++)
                    {
                        int tmp = getVal4St(st, i);
                        if (tmp == up)
                        {
                            setVal4St(st, i, left);
                        }
                    }

                    newVal = left;
                }

                if (flag)
                {
                    setVal4St(st, now_y - 1, 0);
                    setVal4St(st, now_y, 0);

                    addSts(st, sum, cnt, nAct);
                }
            }
            else if (left || up)
            {
                // 就此打住
                unsigned int val = left + up;

                if (1 == val)
                {
                    // 只在最后一个 cell 有效
                    if (h == now_x && w == now_y)
                    {
                    }
                    else
                    {
                        flag = false;
                    }
                }
                else
                {
                    newVal = val;
                }

                if (flag)
                {
                    if (left)
                    {
                        setVal4St(st, now_y - 1, 0);
                    }
                    else
                    {
                        setVal4St(st, now_y, 0);
                    }

                    addSts(st, sum, cnt, nAct);
                }
            }
            else
            {
                // 0 == left && 0 == up
                // 不能就此打住
            }

            if (false == flag)
            {
                if (left)
                {
                    setVal4St(st, now_y - 1, 0);
                }

                if (up)
                {
                    setVal4St(st, now_y, 0);
                }
            }

            // 扩展到其他 cell
            if (h > now_x)
            {
                unsigned int newSt = st;

                setVal4St(newSt, now_y - 1, newVal);

                addSts(newSt, (sum + colGate[now_y][now_x]), cnt, nAct);
            }

            if (w > now_y)
            {
                unsigned int newSt = st;

                setVal4St(newSt, now_y, newVal);

                addSts(newSt, (sum + rowGate[now_x][now_y]), cnt, nAct);
            }

            if (h > now_x && w > now_y)
            {
                unsigned int newSt = st;

                setVal4St(newSt, now_y - 1, newVal);
                setVal4St(newSt, now_y, newVal);

                addSts(newSt, (sum + colGate[now_y][now_x] + rowGate[now_x][now_y]), cnt, nAct);
            }
        }

        qTail[act] = 0;
        act = nAct;
    }

    return 0;
}
