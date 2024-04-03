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
#define MIN_START 1

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
#define recode(ST, UNUSED)                 \
    if (0 == stMap[ST].minUnused)          \
    {                                      \
        int tmpSt = ST;                    \
        int bb[10];                        \
        memset(bb, -1, sizeof(bb));        \
        int bn = MIN_START;                \
        bb[0] = 0;                         \
        for (int i = 1; i <= w; i++)       \
        {                                  \
            int tmp = getVal4St(ST, i);    \
            if (tmp)                       \
            {                              \
                if (0 > bb[tmp])           \
                {                          \
                    bb[tmp] = bn++;        \
                }                          \
                setVal4St(ST, i, bb[tmp]); \
            }                              \
        }                                  \
        UNUSED = bn;                       \
        stMap[tmpSt].recode = ST;          \
        stMap[tmpSt].minUnused = UNUSED;   \
    }                                      \
    else                                   \
    {                                      \
        UNUSED = stMap[ST].minUnused;      \
        ST = stMap[ST].recode;             \
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
                unsigned int finalSt = 0;
                for (size_t i = 1; i <= w; i++)
                {
                    setVal4St(finalSt, i, 1);
                }

                printf("%llu\n", qs[act][cnts[finalSt]].count);
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

            unsigned int left = getVal4St(st, now_y - 1);
            unsigned int up = getVal4St(st, now_y);

            if (left && up)
            {
                // up 的延伸
                {
                    unsigned int newSt = st;
                    addSts(newSt, (sum + colGate[now_y][now_x]), cnt, nAct);
                }

                int upCnt = 0;
                for (int i = 1; i <= w; i++)
                {
                    int tmp = getVal4St(st, i);
                    if (tmp == up)
                    {
                        upCnt++;
                        if (1 < upCnt)
                            break;
                    }
                }

                // left 的延伸
                {
                    if (1 < upCnt)
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y, left);
                        addSts(newSt, (sum + rowGate[now_x][now_y]), cnt, nAct);
                    }
                }

                // 联通 left 和 up
                {
                    // up ==> left
                    unsigned int newSt = st;
                    for (int i = 1; i <= w; i++)
                    {
                        int tmp = getVal4St(newSt, i);
                        if (tmp == up)
                        {
                            setVal4St(newSt, i, left);
                        }
                    }
                    addSts(newSt, (sum + rowGate[now_x][now_y] + colGate[now_y][now_x]), cnt, nAct);
                }

                // 新的联通
                {
                    if (1 < upCnt)
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y, newVal);
                        addSts(newSt, sum, cnt, nAct);
                    }
                }
            }
            else if (left || up)
            {
                if (left)
                {
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y, left);
                        addSts(newSt, (sum + rowGate[now_x][now_y]), cnt, nAct);
                    }

                    // 新的联通块
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y, newVal);
                        addSts(newSt, sum, cnt, nAct);
                    }
                }
                else
                {
                    {
                        unsigned int newSt = st;
                        addSts(newSt, (sum + colGate[now_y][now_x]), cnt, nAct);
                    }

                    // 新的联通块
                    {
                        int upCnt = 0;
                        for (int i = 1; i <= w; i++)
                        {
                            int tmp = getVal4St(st, i);
                            if (tmp == up)
                            {
                                upCnt++;
                                if (1 < upCnt)
                                    break;
                            }
                        }

                        if (1 < upCnt)
                        {
                            unsigned int newSt = st;
                            setVal4St(newSt, now_y, newVal);
                            addSts(newSt, sum, cnt, nAct);
                        }
                    }
                }
            }
            else
            {
                // 0 == left && 0 == up
                // 第一个 cell，新的联通块
                unsigned int newSt = st;
                setVal4St(newSt, now_y, newVal);
                addSts(newSt, sum, cnt, nAct);
            }
        }

        qTail[act] = 0;
        act = nAct;
    }

    return 0;
}
