// https://codeforces.com/problemset/problem/845/F
// https://www.luogu.com.cn/problem/CF845F

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
#define MAX_W 17
#define MAX_H 17
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 600000
#define MOD 1000000007

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST1, ST2, CNT0, CNT1, IDX)                                             \
    {                                                                                 \
        unsigned int key = (ST1 << (w + 1)) + ST2;                                    \
        unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX].find(key); \
        if (it == cnts[IDX].end())                                                    \
        {                                                                             \
            int pInQ = qTail[IDX];                                                    \
            qs[IDX][pInQ].state1 = ST1;                                               \
            qs[IDX][pInQ].state2 = ST2;                                               \
            qs[IDX][pInQ].cnt[0] = CNT0;                                              \
            qs[IDX][pInQ].cnt[1] = CNT1;                                              \
            cnts[IDX][key] = pInQ;                                                    \
            qTail[IDX]++;                                                             \
        }                                                                             \
        else                                                                          \
        {                                                                             \
            qs[IDX][it->second].cnt[0] += CNT0;                                       \
            if (MOD <= qs[IDX][it->second].cnt[0])                                    \
                qs[IDX][it->second].cnt[0] %= MOD;                                    \
            qs[IDX][it->second].cnt[1] += CNT1;                                       \
            if (MOD <= qs[IDX][it->second].cnt[1])                                    \
                qs[IDX][it->second].cnt[1] %= MOD;                                    \
        }                                                                             \
    }

class Record
{
public:
    unsigned int state1; // 轮廓线插头状态
    unsigned int state2; // 轮廓线cell状态
    unsigned int cnt[2]; // missed = 0 / 1 的个数

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

inline void init()
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state1 = 0;
    qs[act][0].state2 = (1 << (w + 1)) - 1;
    qs[act][0].cnt[0] = 1;

    qTail[act]++;
}

int main()
{
    cin >> h >> w;

    if (h < w)
    {
        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[col][row];
            }
        }

        swap(h, w);
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

    init();

    unsigned int ans = 0;

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
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    if (0 == qs[act][iQ].state1)
                    {
                        ans += qs[act][iQ].cnt[0];
                        ans %= MOD;

                        ans += qs[act][iQ].cnt[1];
                        ans %= MOD;
                    }
                }

                break;
            }
        }
        else
        {
            now_y++;
        }

        if ('x' == cells[now_x][now_y])
        {
            if (1 == now_y)
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    qs[act][iQ].state1 <<= ST_BITS;
                    setVal4St(qs[act][iQ].state2, now_y, 1);
                }
            }
            else
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    setVal4St(qs[act][iQ].state2, now_y, 1);
                }
            }

            continue;
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st1 = qs[act][iQ].state1;
            unsigned int st2 = qs[act][iQ].state2;
            unsigned int cnt0 = qs[act][iQ].cnt[0];
            unsigned int cnt1 = qs[act][iQ].cnt[1];

            if (1 == now_y)
            {
                st1 <<= ST_BITS;
            }

            int left = getVal4St(st1, now_y - 1);
            int up = getVal4St(st1, now_y);

            if (left && up)
            {
                unsigned int newSt1 = st1;
                if (h == now_x || 'x' == cells[now_x + 1][now_y])
                {
                    setVal4St(newSt1, now_y - 1, 0);
                }

                if (w == now_y || 'x' == cells[now_x][now_y + 1])
                {
                    setVal4St(newSt1, now_y, 0);
                }

                addSts(newSt1, st2, (2 * cnt0), (2 * cnt1), nAct);
            }
            else if (left)
            {
                unsigned int newSt2 = st2;
                setVal4St(newSt2, now_y, 1);

                // 没有 guard
                {
                    unsigned int newSt1 = st1;

                    setVal4St(newSt1, now_y - 1, 0);
                    if (w > now_y && '.' == cells[now_x][now_y + 1])
                    {
                        setVal4St(newSt1, now_y, 1);
                    }

                    addSts(newSt1, newSt2, cnt0, cnt1, nAct);
                }

                // 有 guard
                {
                    unsigned int newSt1 = st1;

                    if (h == now_x || 'x' == cells[now_x + 1][now_y])
                    {
                        setVal4St(newSt1, now_y - 1, 0);
                    }

                    if (w > now_y && '.' == cells[now_x][now_y + 1])
                    {
                        setVal4St(newSt1, now_y, 1);
                    }

                    addSts(newSt1, newSt2, cnt0, cnt1, nAct);
                }
            }
            else if (up)
            {
                // 没有 guard
                {
                    unsigned int newSt1 = st1;

                    if (h > now_x && '.' == cells[now_x + 1][now_y])
                    {
                        setVal4St(newSt1, now_y - 1, 1);
                    }
                    setVal4St(newSt1, now_y, 0);

                    addSts(newSt1, st2, cnt0, cnt1, nAct);
                }

                // 有 guard
                {
                    unsigned int newSt1 = st1;

                    if (h > now_x && '.' == cells[now_x + 1][now_y])
                    {
                        setVal4St(newSt1, now_y - 1, 1);
                    }

                    if (w == now_y || 'x' == cells[now_x][now_y + 1])
                    {
                        setVal4St(newSt1, now_y, 0);
                    }

                    addSts(newSt1, st2, cnt0, cnt1, nAct);
                }
            }
            else
            {
                // 0 == left && 0 == up
                // 没有 guard
                {
                    unsigned int newSt2 = st2;
                    setVal4St(newSt2, now_y, 0);

                    addSts(st1, newSt2, 0, cnt0, nAct);
                }

                // 有 guard
                {
                    unsigned int newSt1 = st1;

                    if (h > now_x && '.' == cells[now_x + 1][now_y])
                    {
                        setVal4St(newSt1, now_y - 1, 1);
                    }

                    if (w > now_y && '.' == cells[now_x][now_y + 1])
                    {
                        setVal4St(newSt1, now_y, 1);
                    }

                    unsigned int newSt2 = st2;
                    setVal4St(newSt2, now_y, 1);

                    addSts(newSt1, newSt2, cnt0, cnt1, nAct);
                }
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
