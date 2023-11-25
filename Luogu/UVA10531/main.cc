// https://www.luogu.com.cn/problem/UVA10531

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
#define MAX_H 6
#define MAX_W 7
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int total;
    unsigned char minUnused;
    unsigned int cnt[31];

    Record() {}
};

unsigned int output[MAX_H][MAX_W];
float cells[MAX_H][MAX_W];
char flags[MAX_H][MAX_W];       // 0 - 概率为0，1 - 概率为1，2 - 概率为其他
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

// 最小表示法重编码
#define recode(ST, UNUSED)             \
    int bb[10];                        \
    memset(bb, -1, sizeof(bb));        \
    int bn = 2;                        \
    bb[0] = 0;                         \
    bb[1] = 1;                         \
    for (int i = 1; i <= w; i++)       \
    {                                  \
        int tmp = getVal4St(ST, i);    \
        if (1 < tmp)                   \
        {                              \
            if (0 > bb[tmp])           \
            {                          \
                bb[tmp] = bn++;        \
            }                          \
            setVal4St(ST, i, bb[tmp]); \
        }                              \
    }                                  \
    UNUSED = bn;

#define getColorCnt(CNT, ST, PLUG)      \
    for (size_t i = 1; i <= w; i++)     \
    {                                   \
        if (PLUG == (getVal4St(ST, i))) \
        {                               \
            CNT++;                      \
        }                               \
    }

inline void addSts(unsigned int st, unsigned total, Record &rec, int idx, bool blocked)
{
    unsigned int newSt = st;
    unsigned char minUnused = 0;

    recode(newSt, minUnused)

    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(newSt);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = newSt;
        qs[idx][pInQ].total = total;
        qs[idx][pInQ].minUnused = minUnused;

        memcpy(&(qs[idx][pInQ].cnt[1]), &(rec.cnt[1]), sizeof(unsigned int) * now_x * now_y);

        if (blocked)
        {
            qs[idx][pInQ].cnt[now_x * now_y] = total;
        }
        else
        {
            qs[idx][pInQ].cnt[now_x * now_y] = 0;
        }        

        cnts[idx][newSt] = pInQ;
        qTail[idx]++;
    }
    else
    {
        qs[idx][it->second].total += total;

        for (size_t i = 1; i < (now_x * now_y); i++)
        {
            qs[idx][it->second].cnt[i] += rec.cnt[i];
        }

        if (blocked)
        {
            qs[idx][it->second].cnt[now_x * now_y] += total;
        }
    }
}

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 1;
    now_y = 1;

    qs[act][0].state = 1 << ST_BITS;
    qs[act][0].total = 1;
    qs[act][0].minUnused = 2;
    memset(qs[act][0].cnt, 0, sizeof(qs[act][0].cnt));

    memset(output, 0, sizeof(output));

    qTail[act]++;
}

int main()
{
    int t;
    cin >> t;

    for (size_t iT = 0; iT < t; iT ++)
    {
        cin >> h >> w;

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
                if (fabsf(cells[row][col] - 1.0f) < 0.000001)
                {
                    flags[row][col] = 1;
                }
                else if (fabsf(cells[row][col] - 0.0f) < 0.000001)
                {
                    flags[row][col] = 0;
                }
                else
                {
                    flags[row][col] = 2;
                }
            }
        }

        init();

        while (0 < qTail[act])
        {
            int nAct = 1 - act;

            if (w == now_y)
            {
                now_x++;
                now_y = 1;

                if (h < now_x)
                {
                    // finished
                    unsigned int one = 1 << (w * ST_BITS);
                    unsigned int mask = ST_MASK << (w * ST_BITS);
                    unsigned int total = 0;

                    for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        unsigned int st = qs[act][iQ].state;

                        if (one == (st & mask))
                        {
                            total += qs[act][iQ].total;

                            for (size_t row = 1; row <= h; row++)
                            {
                                for (size_t col = 1; col <= w; col++)
                                {
                                    output[row][col] += qs[act][iQ].cnt[w * (row - 1) + col];
                                }
                            }
                        }
                    }

                    for (size_t row = 1; row <= h; row++)
                    {
                        for (size_t col = 1; col <= w; col++)
                        {
                            double p = output[row][col];
                            p /= (double)total;

                            if (col < w)
                            {
                                printf("%.6f ", p);
                            }
                            else
                            {
                                printf("%.6f\n", p);
                            }
                        }
                    }

                    printf("\n");

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
                unsigned int total = qs[act][iQ].total;
                unsigned char minUnused = qs[act][iQ].minUnused;

                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                if (up)
                {
                    if (0 != flags[now_x][now_y])
                    {
                        // 存在障碍物的可能性，障碍物
                        if (1 == up)
                        {
                            int oneCnt = 0;
                            getColorCnt(oneCnt, st, 1);
                            if (1 < oneCnt)
                            {
                                unsigned int newSt = st;
                                setVal4St(newSt, now_y, 0);

                                addSts(newSt, total, qs[act][iQ], nAct, true);
                            }
                        }
                        else
                        {
                            unsigned int newSt = st;
                            setVal4St(newSt, now_y, 0);

                            addSts(newSt, total, qs[act][iQ], nAct, true);
                        }
                    }

                    if (1 != flags[now_x][now_y])
                    {
                        // 不一定百分百障碍物，非障碍物
                        unsigned int newSt = st;

                        if (left && left != up)
                        {
                            if (left > up)
                            {
                                swap(left, up);
                            }

                            // left < up, up ==> left
                            for (size_t i = 1; i <= w; i++)
                            {
                                if (up == (getVal4St(newSt, i)))
                                {
                                    setVal4St(newSt, i, left);
                                }
                            }
                        }

                        addSts(newSt, total, qs[act][iQ], nAct, false);
                    }
                }
                else
                {
                    // 0 == up
                    if (0 != flags[now_x][now_y])
                    {
                        // 存在障碍物的可能性，障碍物
                        unsigned int newSt = st;

                        addSts(newSt, total, qs[act][iQ], nAct, true);
                    }

                    if (1 != flags[now_x][now_y])
                    {
                        // 不一定百分百障碍物，非障碍物
                        unsigned int newSt = st;

                        if (left)
                        {
                            setVal4St(newSt, now_y, left);
                        }
                        else
                        {
                            setVal4St(newSt, now_y, minUnused);
                        }

                        addSts(newSt, total, qs[act][iQ], nAct, false);
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }
    }

    return 0;
}
