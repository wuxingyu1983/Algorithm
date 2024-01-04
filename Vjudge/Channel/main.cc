// https://vjudge.net/problem/UVALive-4789
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=257&page=show_problem&problem=3535

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
#define MAX_H 21
#define MAX_W 10
#define QS_SIZE 1000000

const unsigned int ST1_BITS = 2;
const unsigned long long ST1_MASK = 3;

#define getVal4St1(ST, POS) (((ST) >> ((POS) * ST1_BITS)) & ST1_MASK)

#define setVal4St1(ST, POS, VAL)             \
    ST &= ~(ST1_MASK << ((POS) * ST1_BITS)); \
    if (VAL)                                 \
        ST |= (VAL) << ((POS) * ST1_BITS);

#define getVal4St2(ST, POS) (((ST) >> (POS)) & 1)

#define setVal4St2(ST, POS, VAL) \
    ST &= ~(1 << (POS));         \
    if (VAL)                     \
        ST |= (VAL) << (POS);

class Record
{
public:
    unsigned int key;
    unsigned int state1;
    unsigned short state2;
    unsigned short len; 

    char cache[MAX_H][MAX_W];

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts;
int act = 0; // 当前生效的 queue 
int now_x, now_y;
unsigned short st2Mask;

#define addSts(ST1, ST2, LEN, CH, REC, IDX)                                                  \
    unsigned int key = (ST1 << (w + 1)) + ST2;                                               \
    unordered_map<unsigned int, unsigned int>::iterator it = cnts.find(key);                 \
    if (it == cnts.end() || it->second >= qTail[IDX] || key != qs[IDX][it->second].key)      \
    {                                                                                        \
        int pInQ = qTail[IDX];                                                               \
        qs[IDX][pInQ].key = key;                                                             \
        qs[IDX][pInQ].state1 = ST1;                                                          \
        qs[IDX][pInQ].state2 = ST2;                                                          \
        qs[IDX][pInQ].len = LEN;                                                             \
        memcpy(qs[IDX][pInQ].cache, REC.cache, sizeof(qs[IDX][pInQ].cache));                 \
        qs[IDX][pInQ].cache[now_x][now_y] = CH;                                              \
        cnts[key] = pInQ;                                                                    \
        qTail[IDX]++;                                                                        \
    }                                                                                        \
    else                                                                                     \
    {                                                                                        \
        if (LEN > qs[IDX][it->second].len)                                                   \
        {                                                                                    \
            memcpy(qs[IDX][it->second].cache, REC.cache, sizeof(qs[IDX][it->second].cache)); \
            qs[IDX][it->second].cache[now_x][now_y] = CH;                                    \
            qs[IDX][it->second].len = LEN;                                                   \
        }                                                                                    \
    }

#define forwardFunc(newSt, plusVal, minusVal, newVal) \
    {                                                 \
        int pos = now_y + 1;                          \
        int s = 1;                                    \
        while (pos <= w)                              \
        {                                             \
            int v = getVal4St1(newSt, pos);           \
            if (plusVal == v)                         \
                s++;                                  \
            else if (minusVal == v)                   \
            {                                         \
                s--;                                  \
                if (0 == s)                           \
                {                                     \
                    setVal4St1(newSt, pos, newVal);   \
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
            int v = getVal4St1(newSt, pos);            \
            if (plusVal == v)                          \
                s++;                                   \
            else if (minusVal == v)                    \
            {                                          \
                s--;                                   \
                if (0 == s)                            \
                {                                      \
                    setVal4St1(newSt, pos, newVal);    \
                    break;                             \
                }                                      \
            }                                          \
            pos--;                                     \
        }                                              \
    }

inline void init()
{
    act = 0;

    now_x = 0;
    now_y = w;

    st2Mask = (1 << w) - 1;

    cnts.clear();

    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].key = 0;
    qs[act][0].len = 0;
    memset(qs[act][0].cache, 0, sizeof(qs[act][0].cache));

    qTail[0] = 1;
    qTail[1] = 0;
}

int main()
{
    scanf("%d %d", &h, &w);

    if (0 < h && 0 < w)
    {
        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                scanf("%c", &(cells[row][col]));
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
                    // TBD

                    break;
                }
            }
            else
            {
                now_y++;
            }

            if ('#' == cells[now_x][now_y])
            {
                if (1 == now_y)
                {
                    for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        qs[act][iQ].state1 <<= ST1_BITS;
                        qs[act][iQ].state2 &= st2Mask;
                        qs[act][iQ].state2 <<= 1;
                        qs[act][iQ].key = (qs[act][iQ].state1 << (w + 1)) + qs[act][iQ].state2;

                        qs[act][iQ].cache[now_x][now_y] = '#';
                    }
                }
                else
                {
                    for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        qs[act][iQ].cache[now_x][now_y] = '#';
                    }
                }
            }
            else
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    unsigned int st1 = qs[act][iQ].state1;
                    unsigned short st2 = qs[act][iQ].state2;
                    unsigned short len = qs[act][iQ].len;

                    if (1 == now_y)
                    {
                        st1 <<= ST1_BITS;
                        st2 &= st2Mask;
                        st2 <<= 1;
                    }

                    unsigned int leftPlug = getVal4St1(st1, now_y - 1);
                    unsigned int upPlug = getVal4St1(st1, now_y);

                    unsigned short leftCell = 0;
                    if (1 < now_y)
                        leftCell = getVal4St2(st2, now_y - 2);
                    unsigned short leftUpCell = getVal4St2(st2, now_y - 1);
                    unsigned short upCell = getVal4St2(st2, now_y);
                    unsigned short rightUpCell = 0;
                    if (w > now_y)
                        rightUpCell = getVal4St2(st2, now_y + 1);

                    if (leftPlug && upPlug)
                    {
                        if (1 == leftUpCell || (h == now_x && w == now_y))
                        {
                            // 非法
                            continue;
                        }
                        else
                        {
                            unsigned int newSt1 = st1;
                            setVal4St1(newSt1, now_y - 1, 0);
                            setVal4St1(newSt1, now_y, 0);

                            unsigned short newSt2 = st2;
                            setVal4St2(newSt2, now_y - 1, 1);

                            if ((2 == leftPlug && 1 == upPlug) || (3 == leftPlug && 3 == upPlug))
                            {
                                // do nothing
                            }
                            else if (3 == leftPlug || 3 == upPlug)
                            {
                                if (1 == leftPlug || 1 == upPlug)
                                {
                                    forwardFunc(newSt1, 1, 2, 3);
                                }
                                else
                                {
                                    // 2 == leftPlug || 2 == upPlug
                                    backwardFunc(newSt1, 2, 1, 3);
                                }
                            }
                            else if (1 == leftPlug && 1 == upPlug)
                            {
                                forwardFunc(newSt1, 1, 2, 1);
                            }
                            else if (2 == leftPlug && 2 == upPlug)
                            {
                                backwardFunc(newSt1, 2, 1, 2);
                            }
                            else if (1 == leftPlug && 2 == upPlug)
                            {
                                // 非法
                                continue;
                            }
                            
                            addSts(newSt1, newSt2, (len + 1), 'C', qs[act][iQ], nAct);
                        }
                    }
                    else if (leftPlug)
                    {

                    }
                    else if (upPlug)
                    {

                    }
                    else
                    {
                        // 0 == leftPlug && 0 == upPlug
                        if (1 == now_x && 1 == now_y)
                        {
                            if (h > now_x && '.' == cells[now_x + 1][now_y])
                            {
                                unsigned int newSt1 = st1;
                                setVal4St1(newSt1, now_y - 1, 3);

                                unsigned short newSt2 = st2;
                                setVal4St2(newSt2, now_y - 1, 1);
                            
                                addSts(newSt1, newSt2, (len + 1), 'C', qs[act][iQ], nAct);
                            }

                            if (w > now_y && '.' == cells[now_x][now_y + 1])
                            {
                                unsigned int newSt1 = st1;
                                setVal4St1(newSt1, now_y, 3);

                                unsigned short newSt2 = st2;
                                setVal4St2(newSt2, now_y - 1, 1);
                            
                                addSts(newSt1, newSt2, (len + 1), 'C', qs[act][iQ], nAct);
                            }
                        }
                        else if (h == now_x && w == now_y)
                        {
                            // 非法
                            continue;
                        }
                        else
                        {
                            // 跳过
                            unsigned short newSt2 = st2;
                            setVal4St2(newSt2, now_y - 1, 0);

                            addSts(st1, newSt2, len, '.', qs[act][iQ], nAct);
                        }

                        if (0 == leftCell && 0 == leftUpCell && 0 == upCell)
                        {
                            // 合法
                            if (h > now_x && '.' == cells[now_x + 1][now_y] && w > now_y && '.' == cells[now_x][now_y + 1])
                            {
                                unsigned int newSt1 = st1;
                                setVal4St1(newSt1, now_y - 1, 1);
                                setVal4St1(newSt1, now_y, 2);

                                unsigned short newSt2 = st2;
                                setVal4St2(newSt2, now_y - 1, 1);
                            
                                addSts(newSt1, newSt2, (len + 1), 'C', qs[act][iQ], nAct);
                            }
                        }
                    }
                }

                qTail[act] = 0;
                act = nAct;
            }
        }
    }

    return 0;
}
