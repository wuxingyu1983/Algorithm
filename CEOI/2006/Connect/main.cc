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
#include <cstring>

using namespace std;

#define MAX_H 80
#define MAX_W 26
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 80000

enum AddType
{
    addEnd = 0,
    addDown = 1,
    addRight = 2,
    addDownAndRight
};

class Record
{
public:
    unsigned int state;
    unsigned short score;
    unsigned int record[40];

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts;
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, TYPE, SCORE, REC, IDX)                                   \
    unordered_map<unsigned int, unsigned int>::iterator it = cnts.find(ST); \
    if (it == cnts.end())                                                   \
    {                                                                       \
        int pInQ = qTail[IDX];                                              \
        qs[IDX][pInQ].state = ST;                                           \
        qs[IDX][pInQ].score = SCORE;                                        \
        memcpy(qs[IDX][pInQ].record, REC, sizeof(REC));                     \
        qs[IDX][pInQ].record[now_x >> 1] &= ~(3 << now_y);                  \
        qs[IDX][pInQ].record[now_x >> 1] |= TYPE << now_y;                  \
        cnts[ST] = pInQ;                                                    \
        qTail[IDX]++;                                                       \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        int pInQ = it->second;                                              \
        if (qs[IDX][pInQ].score > SCORE)                                    \
        {                                                                   \
            qs[IDX][pInQ].score = SCORE;                                    \
            memcpy(qs[IDX][pInQ].record, REC, sizeof(REC));                 \
            qs[IDX][pInQ].record[now_x >> 1] &= ~(3 << now_y);              \
            qs[IDX][pInQ].record[now_x >> 1] |= TYPE << now_y;              \
        }                                                                   \
    }

#define forwardFunc(newSt, plusVal, minusVal, newVal) \
    {                                                 \
        int pos = now_y + 1;                          \
        int s = 1;                                    \
        while (pos <= (w >> 1))                       \
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

int main()
{
    bool bSwitch = false;

    scanf("%d %d\n", &h, &w);

    if (h < w)
    {
        bSwitch = true;
    }

    for (int i = 1; i <= h; i++)
    {
        string s;
        getline(cin, s);

        for (int j = 1; j <= w; j++)
        {
            if (bSwitch)
            {
                cells[j][i] = s.at(j - 1);
            }
            else
            {
                cells[i][j] = s.at(j - 1);
            }
        }
    }

    if (bSwitch)
    {
        swap(h, w);
    }

    // init
    act = 0;

    now_x = 0;
    now_y = w - 1;

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
                if (1 == qTail[act] && 0 == qs[act][0].state)
                {
                    cout << qs[act][0].score << endl;

                    for (size_t row = 1; row <= (h >> 1); row++)
                    {
                        for (size_t col = 1; col <= (w >> 1); col++)
                        {
                            int tmp = (qs[act][0].record[row] >> (2 * col)) & 3;
                            if (addEnd == tmp)
                            {
                                if ('X' != cells[row << 1][col << 1])
                                {
                                    if ('.' == cells[(row << 1) - 1][col << 1] || '.' == cells[row << 1][(col << 1) - 1])
                                    {
                                        cells[row << 1][col << 1] = '.';
                                    }
                                }
                            }
                            else if (addDown == tmp)
                            {
                                if ('X' != cells[row << 1][col << 1])
                                {
                                    cells[row << 1][col << 1] = '.';
                                }
                                cells[(row << 1) + 1][col << 1] = '.';
                            }
                            else if (addRight == tmp)
                            {
                                if ('X' != cells[row << 1][col << 1])
                                {
                                    cells[row << 1][col << 1] = '.';
                                }
                                cells[row << 1][(col << 1) + 1] = '.';
                            }
                            else
                            {
                                cells[row << 1][col << 1] = '.';
                                cells[(row << 1) + 1][col << 1] = '.';
                                cells[row << 1][(col << 1) + 1] = '.';
                            }
                        }
                    }

                    if (bSwitch)
                    {
                        for (size_t col = 1; col <= w; col++)
                        {
                            for (size_t row = 1; row <= h; row++)
                            {
                                cout << cells[row][col];
                            }
                            cout << endl;
                        }
                    }
                    else
                    {
                        for (size_t row = 1; row <= h; row++)
                        {
                            for (size_t col = 1; col <= w; col++)
                            {
                                cout << cells[row][col];
                            }
                            cout << endl;
                        }
                    }
                }
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
            unsigned short score = qs[act][iQ].score;

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
                    continue;
                }
                else
                {
                    unsigned int newSt = st;

                    setVal4St(newSt, (now_y >> 1) - 1, 0);
                    setVal4St(newSt, (now_y >> 1), 0);

                    if (3 == left || 3 == up)
                    {
                        if (1 == left || 1 == up)
                        {
                            // 1, 3
                            forwardFunc(newSt, 1, 2, 3);
                        }
                        else if (2 == left || 2 == up)
                        {
                            // 2, 3
                            backwardFunc(newSt, 2, 1, 3);
                        }
                        else
                        {
                            // 3, 3
                            // do nothing
                        }
                    }
                    else if (1 == left && 1 == up)
                    {
                        forwardFunc(newSt, 1, 2, 1);
                    }
                    else if (1 == left && 2 == up)
                    {
                        // invalid
                        continue;
                    }
                    else if (2 == left && 1 == up)
                    {
                        // do nothin
                    }
                    else
                    {
                        // 2 == left && 2 == up
                        backwardFunc(newSt, 2, 1, 2);
                    }

                    addSts(newSt, addEnd, (score + 2), qs[act][iQ].record, nAct);
                }
            }
            else if (left || up)
            {
                unsigned int val = left + up;
                if ('X' == cells[now_x][now_y])
                {
                    unsigned int newSt = st;

                    setVal4St(newSt, (now_y >> 1) - 1, 0);
                    setVal4St(newSt, (now_y >> 1), 0);

                    if (3 == val)
                    {
                    }
                    else if (1 == val)
                    {
                        forwardFunc(newSt, 1, 2, 3);
                    }
                    else
                    {
                        // 2 == val
                        backwardFunc(newSt, 2, 1, 3);
                    }

                    addSts(newSt, addEnd, (score + 1), qs[act][iQ].record, nAct);
                }
                else
                {
                    if (' ' == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, (now_y >> 1) - 1, val);
                        setVal4St(newSt, (now_y >> 1), 0);

                        addSts(newSt, addDown, (score + 2), qs[act][iQ].record, nAct);
                    }

                    if (' ' == cells[now_x][now_y + 1])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, (now_y >> 1) - 1, 0);
                        setVal4St(newSt, (now_y >> 1), val);

                        addSts(newSt, addRight, (score + 2), qs[act][iQ].record, nAct);
                    }
                }
            }
            else
            {
                // 0 == left && 0 == up
                if ('X' == cells[now_x][now_y])
                {
                    if (' ' == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, (now_y >> 1) - 1, 3);

                        addSts(newSt, addDown, (score + 1), qs[act][iQ].record, nAct);
                    }

                    if (' ' == cells[now_x][now_y + 1])
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
                    addSts(newSt, addEnd, score, qs[act][iQ].record, nAct);

                    if (' ' == cells[now_x + 1][now_y] && ' ' == cells[now_x][now_y + 1])
                    {
                        setVal4St(newSt, (now_y >> 1) - 1, 1);
                        setVal4St(newSt, (now_y >> 1), 2);

                        addSts(newSt, addDownAndRight, (score + 2), qs[act][iQ].record, nAct);
                    }
                }
            }
        }

        qTail[act] = 0;
        cnts.clear();
        act = nAct;
    }

    return 0;
}
