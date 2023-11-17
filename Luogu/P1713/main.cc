// https://www.luogu.com.cn/problem/P1713

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
#define MAX_HW 11
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int max, min;

    Record() {}
};

char cells[MAX_HW][MAX_HW];
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

#define addSts(ST, MAX, MIN, IDX)                                                    \
    {                                                                                \
        unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX].find(ST); \
        if (it == cnts[IDX].end())                                                   \
        {                                                                            \
            int pInQ = qTail[IDX];                                                   \
            qs[IDX][pInQ].state = ST;                                                \
            qs[IDX][pInQ].max = MAX;                                                 \
            qs[IDX][pInQ].min = MIN;                                                 \
            cnts[IDX][ST] = pInQ;                                                    \
            qTail[IDX]++;                                                            \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            if (MIN < qs[IDX][it->second].min)                                       \
                qs[IDX][it->second].min = MIN;                                       \
            if (MAX > qs[IDX][it->second].max)                                       \
                qs[IDX][it->second].max = MAX;                                       \
        }                                                                            \
    }

#define forwardFunc(newSt, plusVal, minusVal, newVal) \
    {                                                 \
        int pos = now_y + 1;                          \
        int s = 1;                                    \
        while (pos <= w)                              \
        {                                             \
            int v = getVal4St(newSt, pos);            \
            if (plusVal == v)                         \
                s++;                                  \
            else if (minusVal == v)                   \
            {                                         \
                s--;                                  \
                if (0 == s)                           \
                {                                     \
                    setVal4St(newSt, pos, newVal);    \
                    break;                            \
                }                                     \
            }                                         \
            pos++;                                    \
        }                                             \
    }

#define backwardFunc(newSt, plusVal, minusVal, newVal) \
    {                                                  \
        int pos = now_y - 2;                           \
        int s = 1;                                     \
        while (0 <= pos)                               \
        {                                              \
            int v = getVal4St(newSt, pos);             \
            if (plusVal == v)                          \
                s++;                                   \
            else if (minusVal == v)                    \
            {                                          \
                s--;                                   \
                if (0 == s)                            \
                {                                      \
                    setVal4St(newSt, pos, newVal);     \
                    break;                             \
                }                                      \
            }                                          \
            pos--;                                     \
        }                                              \
    }

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state = 3 << ((w - 1) * ST_BITS);
    qs[act][0].max = 0;
    qs[act][0].min = 0;

    qTail[act]++;
}

int main()
{
    int m;
    cin >> h >> m;

    w = h;

    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        cells[x][y] = 1;
    }

    init();

    int max = 0, min = 200;

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
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    if (0 == qs[act][iQ].state)
                    {
                        if (min > qs[act][iQ].min)
                        {
                            min = qs[act][iQ].min;
                        }

                        if (max < qs[act][iQ].max)
                        {
                            max = qs[act][iQ].max;
                        }
                    }
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
            unsigned int max = qs[act][iQ].max;
            unsigned int min = qs[act][iQ].min;

            if (1 == now_y)
            {
                st <<= ST_BITS;
            }

            int left = getVal4St(st, now_y - 1);
            int up = getVal4St(st, now_y);

            if (h == now_x && 1 == now_y && 0 == cells[now_x][now_y])
            {
                if (0 == left && 0 == up && 0 == cells[now_x][now_y + 1])
                {
                    unsigned int newSt = st;
                    setVal4St(newSt, now_y, 3);

                    addSts(newSt, max + 1, min + 1, nAct);
                }
                else
                {
                    if (up)
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 0);

                        if (3 == up)
                        {
                            // do nothin
                        }
                        else if (2 == up)
                        {
                            backwardFunc(newSt, 2, 1, 3);
                        }
                        else
                        {
                            // 1 == up
                            forwardFunc(newSt, 1, 2, 3);
                        }

                        addSts(newSt, max + 1, min + 1, nAct);
                    }
                }
            }
            else
            {
                if (1 == cells[now_x][now_y])
                {
                    // 障碍物
                    addSts(st, max, min, nAct);
                }
                else
                {
                    if (left && up)
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 0);

                        if (3 == left && 3 == up)
                        {
                            // do nothing
                        }
                        else if (3 == left || 3 == up)
                        {
                            if (1 == left || 1 == up)
                            {
                                forwardFunc(newSt, 1, 2, 3);
                            }
                            else if (2 == left || 2 == up)
                            {
                                backwardFunc(newSt, 2, 1, 3);
                            }
                            else
                            {
                                // 非法
                                continue;
                            }
                        }
                        else if (1 == left && 1 == up)
                        {
                            forwardFunc(newSt, 1, 2, 1);
                        }
                        else if (2 == left && 2 == up)
                        {
                            backwardFunc(newSt, 2, 1, 2);
                        }
                        else if (2 == left && 1 == up)
                        {
                            // do nothin
                        }
                        else
                        {
                            // 1 == left && 2 == up
                            // 非法
                            continue;
                        }

                        addSts(newSt, max + 1, min + 1, nAct);
                    }
                    else if (left || up)
                    {
                        int val = left + up;

                        if (h > now_x && 0 == cells[now_x + 1][now_y])
                        {
                            unsigned int newSt = st;
                            setVal4St(newSt, now_y - 1, val);
                            setVal4St(newSt, now_y, 0);

                            addSts(newSt, max + 1, min + 1, nAct);
                        }

                        if (w > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            unsigned int newSt = st;
                            setVal4St(newSt, now_y - 1, 0);
                            setVal4St(newSt, now_y, val);

                            addSts(newSt, max + 1, min + 1, nAct);
                        }
                    }
                    else
                    {
                        // 0 == left && 0 == up
                        // do nothin
                        addSts(st, max, min, nAct);

                        if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            unsigned int newSt = st;
                            setVal4St(newSt, now_y - 1, 1);
                            setVal4St(newSt, now_y, 2);

                            addSts(newSt, max + 1, min + 1, nAct);
                        }
                    }
                }
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    cout << (max - min) << endl;

    return 0;
}
