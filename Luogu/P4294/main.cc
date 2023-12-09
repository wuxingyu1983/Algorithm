// https://www.luogu.com.cn/problem/P4294

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
#define MAX_W 11
#define MAX_H 11
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 1000000

#define getVal4St(ST, POS) (((ST) >> ((POS) * ST_BITS)) & ST_MASK)

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

class Record
{
public:
    unsigned long long state; // 轮廓线cell状态
    unsigned int cnt;
    char recd[MAX_H][MAX_W];

    unsigned char minUnused;

    Record() {}
};

int cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;
int last_x, last_y; // 最后一个景点的位置

// 最小表示法重编码
#define recode(ST, UNUSED)             \
    int bb[10];                        \
    memset(bb, -1, sizeof(bb));        \
    int bn = 1;                        \
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
    UNUSED = bn;

#define addSts(ST, CNT, ADD, REC, IDX)                                                        \
    unsigned char unused;                                                                     \
    unsigned long long recodedSt = ST;                                                        \
    recode(recodedSt, unused);                                                                \
    unordered_map<unsigned long long, unsigned int>::iterator it = cnts[IDX].find(recodedSt); \
    if (it == cnts[IDX].end())                                                                \
    {                                                                                         \
        int pInQ = qTail[IDX];                                                                \
        qs[IDX][pInQ].state = recodedSt;                                                      \
        qs[IDX][pInQ].cnt = CNT + ADD;                                                        \
        qs[IDX][pInQ].minUnused = unused;                                                     \
        memcpy(qs[IDX][pInQ].recd, REC.recd, sizeof(REC.recd));                               \
        if (0 == ADD)                                                                         \
        {                                                                                     \
            if (cells[now_x][now_y])                                                          \
                qs[IDX][pInQ].recd[now_x][now_y] = '_';                                       \
            else                                                                              \
                qs[IDX][pInQ].recd[now_x][now_y] = 'x';                                       \
        }                                                                                     \
        else                                                                                  \
            qs[IDX][pInQ].recd[now_x][now_y] = 'o';                                           \
        cnts[IDX][recodedSt] = pInQ;                                                          \
        qTail[IDX]++;                                                                         \
    }                                                                                         \
    else                                                                                      \
    {                                                                                         \
        if (qs[IDX][it->second].cnt > (CNT + ADD))                                            \
        {                                                                                     \
            qs[IDX][it->second].cnt = CNT + ADD;                                              \
            memcpy(qs[IDX][it->second].recd, REC.recd, sizeof(REC.recd));                     \
            if (0 == ADD)                                                                     \
            {                                                                                 \
                if (cells[now_x][now_y])                                                      \
                    qs[IDX][it->second].recd[now_x][now_y] = '_';                             \
                else                                                                          \
                    qs[IDX][it->second].recd[now_x][now_y] = 'x';                             \
            }                                                                                 \
            else                                                                              \
                qs[IDX][it->second].recd[now_x][now_y] = 'o';                                 \
        }                                                                                     \
    }

void init()
{
    act = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].minUnused = 1;

    qTail[act]++;
}

int main()
{
    cin >> h >> w;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            cin >> cells[row][col];
            if (0 == cells[row][col])
            {
                last_x = row;
                last_y = col;
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
                unsigned int ans = INT_MAX;
                unsigned int idx = 0;
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    if (2 >= qs[act][iQ].minUnused)
                    {
                        if (ans > qs[act][iQ].cnt)
                        {
                            ans = qs[act][iQ].cnt;
                            idx = iQ;
                        }
                    }
                }

                cout << ans << endl;
                for (size_t row = 1; row <= h; row++)
                {
                    for (size_t col = 1; col <= w; col++)
                    {
                        cout << qs[act][idx].recd[row][col];
                    }
                    cout << endl;
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
            unsigned long long st = qs[act][iQ].state;
            unsigned int cnt = qs[act][iQ].cnt;
            unsigned char minUnused = qs[act][iQ].minUnused;

            unsigned int left = getVal4St(st, now_y - 1);
            unsigned int up = getVal4St(st, now_y);

            if (cells[now_x][now_y])
            {
                // 非景点，跳过
                int upCnt = 0;
                if (up)
                {
                    for (size_t i = 1; i <= w; i++)
                    {
                        if (up == getVal4St(st, i))
                        {
                            upCnt++;
                        }
                    }
                }

                if (0 == up || 1 < upCnt || (2 == minUnused && (now_x > last_x || (now_x == last_x && now_y > last_y))))
                {
                    // 有效
                    unsigned long long newSt = st;
                    if (up)
                    {
                        setVal4St(newSt, now_y, 0);
                    }

                    // add st
                    addSts(newSt, cnt, 0, qs[act][iQ], nAct);
                }
            }

            if (left && up)
            {
                unsigned long long newSt = st;

                if (left != up)
                {
                    // left ==> up
                    for (size_t i = 1; i <= w; i++)
                    {
                        if (left == getVal4St(newSt, i))
                        {
                            setVal4St(newSt, i, up);
                        }
                    }
                }

                // add st
                addSts(newSt, cnt, cells[now_x][now_y], qs[act][iQ], nAct);
            }
            else if (left || up)
            {
                unsigned long long newSt = st;

                if (left)
                {
                    setVal4St(newSt, now_y, left);
                }

                // add st
                addSts(newSt, cnt, cells[now_x][now_y], qs[act][iQ], nAct);
            }
            else
            {
                // 0 == left && 0 == up
                if (2 >= minUnused && (now_x > last_x || (now_x == last_x && now_y > last_y)))
                {
                    // 已经过了最后一个景点，并且轮廓线上都为0或者只有1, 跳过即可
                }
                else
                {
                    unsigned long long newSt = st;

                    setVal4St(newSt, now_y, minUnused);

                    // add st
                    addSts(newSt, cnt, cells[now_x][now_y], qs[act][iQ], nAct);
                }
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
