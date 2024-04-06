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
#define QS_SIZE 90000

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
    unsigned char x, y;

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[QS_SIZE];
int qHead, qTail;

#define IS_EMPTY (qHead == qTail)
#define IS_FULL (qHead == ((qTail + 1) % QS_SIZE))

int h, w;
unordered_map<unsigned int, unsigned int> cnts;
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, TYPE, SCORE, REC, X, Y)                                                                \
    unordered_map<unsigned int, unsigned int>::iterator it = cnts.find(ST);                               \
    if (it != cnts.end() && ST == qs[it->second].state && X == qs[it->second].x && Y == qs[it->second].y) \
    {                                                                                                     \
        int pInQ = it->second;                                                                            \
        if (qs[pInQ].score > SCORE)                                                                       \
        {                                                                                                 \
            qs[pInQ].score = SCORE;                                                                       \
            memcpy(qs[pInQ].record, REC, sizeof(REC));                                                    \
            qs[pInQ].record[now_x >> 1] &= ~(3 << now_y);                                                 \
            if (TYPE)                                                                                     \
                qs[pInQ].record[now_x >> 1] |= TYPE << now_y;                                             \
        }                                                                                                 \
    }                                                                                                     \
    else                                                                                                  \
    {                                                                                                     \
        int pInQ = qTail;                                                                                 \
        qs[pInQ].state = ST;                                                                              \
        qs[pInQ].score = SCORE;                                                                           \
        qs[pInQ].x = X;                                                                                   \
        qs[pInQ].y = Y;                                                                                   \
        memcpy(qs[pInQ].record, REC, sizeof(REC));                                                        \
        qs[pInQ].record[now_x >> 1] &= ~(3 << now_y);                                                     \
        if (TYPE)                                                                                         \
            qs[pInQ].record[now_x >> 1] |= TYPE << now_y;                                                 \
        cnts[ST] = pInQ;                                                                                  \
        qTail++;                                                                                          \
        if (QS_SIZE <= qTail)                                                                             \
            qTail -= QS_SIZE;                                                                             \
    }

#define forwardFunc(newSt, plusVal, minusVal, newVal) \
    {                                                 \
        int pos = (now_y >> 1) + 1;                   \
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
        int pos = (now_y >> 1) - 2;                    \
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
    now_x = 0;
    now_y = w - 1;

    qs[qTail].state = 0;
    qs[qTail].score = 0;
    qs[qTail].x = now_x;
    qs[qTail].y = now_y;

    qTail++;

    while (false == IS_EMPTY)
    {
        unsigned int st = qs[qHead].state;
        unsigned short score = qs[qHead].score;
        now_x = qs[qHead].x;
        now_y = qs[qHead].y;

        if ((w - 1) == now_y)
        {
            now_x += 2;
            now_y = 2;

            if (h < now_x)
            {
                if (0 == qs[qHead].state)
                {
                    cout << qs[qHead].score << endl;

                    for (size_t row = 1; row <= (h >> 1); row++)
                    {
                        for (size_t col = 1; col <= (w >> 1); col++)
                        {
                            int tmp = (qs[qHead].record[row] >> (2 * col)) & 3;
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

        if (2 == now_y)
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
                qHead++;
                if (QS_SIZE <= qHead)
                    qHead -= QS_SIZE;
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
                    qHead++;
                    if (QS_SIZE <= qHead)
                        qHead -= QS_SIZE;
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

                addSts(newSt, addEnd, (score + 2), qs[qHead].record, now_x, now_y);
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

                addSts(newSt, addEnd, (score + 1), qs[qHead].record, now_x, now_y);
            }
            else
            {
                if (' ' == cells[now_x + 1][now_y])
                {
                    unsigned int newSt = st;
                    setVal4St(newSt, (now_y >> 1) - 1, val);
                    setVal4St(newSt, (now_y >> 1), 0);

                    addSts(newSt, addDown, (score + 2), qs[qHead].record, now_x, now_y);
                }

                if (' ' == cells[now_x][now_y + 1])
                {
                    unsigned int newSt = st;
                    setVal4St(newSt, (now_y >> 1) - 1, 0);
                    setVal4St(newSt, (now_y >> 1), val);

                    addSts(newSt, addRight, (score + 2), qs[qHead].record, now_x, now_y);
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

                    addSts(newSt, addDown, (score + 1), qs[qHead].record, now_x, now_y);
                }

                if (' ' == cells[now_x][now_y + 1])
                {
                    unsigned int newSt = st;
                    setVal4St(newSt, (now_y >> 1), 3);

                    addSts(newSt, addRight, (score + 1), qs[qHead].record, now_x, now_y);
                }
            }
            else
            {
                unsigned int newSt = st;

                // do nonthing
                addSts(newSt, addEnd, score, qs[qHead].record, now_x, now_y);

                if (' ' == cells[now_x + 1][now_y] && ' ' == cells[now_x][now_y + 1])
                {
                    setVal4St(newSt, (now_y >> 1) - 1, 1);
                    setVal4St(newSt, (now_y >> 1), 2);

                    addSts(newSt, addDownAndRight, (score + 2), qs[qHead].record, now_x, now_y);
                }
            }
        }

        qHead ++;
        if (QS_SIZE <= qHead)
            qHead -= QS_SIZE;
    }

    return 0;
}
