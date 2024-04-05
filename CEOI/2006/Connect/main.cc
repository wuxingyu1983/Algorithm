// https://oj.uz/problem/view/CEOI06_connect

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
#define MAX_H 80
#define MAX_W 26
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 600000

enum AddType
{
    addNothing,
    addDown,
    addRight,
    addDownAndRight
};

class Record
{
public:
    unsigned int state;
    unsigned int score;
    char record[MAX_H][MAX_W];

    Record() {}
};

char cells[MAX_H][MAX_W];
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

#define addSts(ST, TYPE, SCORE, REC, IDX)                                        \
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX].find(ST); \
    if (it == cnts[IDX].end())                                                   \
    {                                                                            \
        int pInQ = qTail[IDX];                                                   \
        qs[IDX][pInQ].state = ST;                                                \
        qs[IDX][pInQ].score = SCORE;                                             \
        memcpy(qs[IDX][pInQ].record, REC, sizeof(REC));                          \
        if (TYPE == addDown)                                                     \
        {                                                                        \
            if ('X' != qs[IDX][pInQ].record[now_x][now_y])                       \
                qs[IDX][pInQ].record[now_x][now_y] = '.';                        \
            qs[IDX][pInQ].record[now_x + 1][now_y] = '.';                        \
        }                                                                        \
        else if (TYPE == addRight)                                               \
        {                                                                        \
            if ('X' != qs[IDX][pInQ].record[now_x][now_y])                       \
                qs[IDX][pInQ].record[now_x][now_y] = '.';                        \
            qs[IDX][pInQ].record[now_x][now_y + 1] = '.';                        \
        }                                                                        \
        else if (TYPE == addDownAndRight)                                        \
        {                                                                        \
            qs[IDX][pInQ].record[now_x][now_y] = '.';                            \
            qs[IDX][pInQ].record[now_x + 1][now_y] = '.';                        \
            qs[IDX][pInQ].record[now_x][now_y + 1] = '.';                        \
        }                                                                        \
        cnts[IDX][ST] = pInQ;                                                    \
        qTail[IDX]++;                                                            \
    }                                                                            \
    else                                                                         \
    {                                                                            \
        int pInQ = it->second;                                                   \
        if (qs[IDX][pInQ].score > SCORE)                                         \
        {                                                                        \
            qs[IDX][pInQ].score = SCORE;                                         \
            memcpy(qs[IDX][pInQ].record, REC, sizeof(REC));                      \
            if (TYPE == addDown)                                                 \
            {                                                                    \
                if ('X' != qs[IDX][pInQ].record[now_x][now_y])                   \
                    qs[IDX][pInQ].record[now_x][now_y] = '.';                    \
                qs[IDX][pInQ].record[now_x + 1][now_y] = '.';                    \
            }                                                                    \
            else if (TYPE == addRight)                                           \
            {                                                                    \
                if ('X' != qs[IDX][pInQ].record[now_x][now_y])                   \
                    qs[IDX][pInQ].record[now_x][now_y] = '.';                    \
                qs[IDX][pInQ].record[now_x][now_y + 1] = '.';                    \
            }                                                                    \
            else if (TYPE == addDownAndRight)                                    \
            {                                                                    \
                qs[IDX][pInQ].record[now_x][now_y] = '.';                        \
                qs[IDX][pInQ].record[now_x + 1][now_y] = '.';                    \
                qs[IDX][pInQ].record[now_x][now_y + 1] = '.';                    \
            }                                                                    \
        }                                                                        \
    }

int main()
{
    bool bSwitch = false;

    cin >> h >> w;

    if (h < w)
    {
        swap(h, w);
        bSwitch = true;

        for (size_t col = 1; col <= w; col++)
        {
            for (size_t row = 1; row <= h; row++)
            {
                cin >> cells[row][col];
            }
        }
    }
    else
    {
        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
            }
        }
    }

    // init
    act = 0;

    now_x = 2;
    now_y = 2;

    qs[act][0].state = 0;
    qs[act][0].score = 0;
    memcpy(qs[act]->record, cells, sizeof(cells));

    qTail[act]++;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;

        if ((w - 1) == now_y)
        {
            now_x += 2;
            now_y = 2;

            if (h < now_x)
            {
                // TBD
                break;
            }
        }
        else
        {
            now_y += 2;
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st = qs[act][iQ].state;
            unsigned int score = qs[act][iQ].score;

            if (1 == (now_y >> 1))
            {
                st <<= ST_BITS;
            }

            unsigned int left = getVal4St(st, (now_y >> 1) - 1);
            unsigned int up = getVal4St(st, (now_y >> 1));

            if (left && up)
            {
                if ('X' == cells[now_x][now_y])
                {
                    // invalid
                }
                else
                {

                }
            }
            else if (left || up)
            {
                if ('X' == cells[now_x][now_y])
                {
                }
                else
                {
                }
            }
            else
            {
                // 0 == left && 0 == up
                if ('X' == cells[now_x][now_y])
                {
                    if ('-' != cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, (now_y >> 1) - 1, 3);

                        addSts(newSt, addDown, (score + 1), qs[act][iQ].record, nAct);
                    }

                    if ('|' != cells[now_x][now_y])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, (now_y >> 1), 3);

                        addSts(newSt, addRight, (score + 1), qs[act][iQ].record, nAct);
                    }
                }
                else
                {
                    unsigned int newSt = st;

                    // do nonthing
                    addSts(newSt, addNothing, score, qs[act][iQ].record, nAct);

                    if ('-' != cells[now_x + 1][now_y] && '|' != cells[now_x][now_y])
                    {
                        setVal4St(newSt, (now_y >> 1) - 1, 1);
                        setVal4St(newSt, (now_y >> 1), 2);

                        addSts(newSt, addDownAndRight, (score + 2), qs[act][iQ].record, nAct);
                    }
                }
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
