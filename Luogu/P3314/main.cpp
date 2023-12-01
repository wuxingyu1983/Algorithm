// https://www.luogu.com.cn/problem/P3314

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
#define MAX_W 10
#define MAX_H 10
#define MAX_K 11
#define ST_BITS 4
#define ST_MASK 15
#define QS_SIZE 600000
#define MOD 25619849

class Record
{
public:
    unsigned long long state; // 轮廓线段状态
    unsigned int len;
    unsigned int cnt;

    Record() {}
};

unsigned int cells[MAX_H][MAX_W];
vector<unsigned int> paths[MAX_H][MAX_W];
unsigned char flags[MAX_H][MAX_W][MAX_K];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)                              \
    ST &= ~(((unsigned long long)255) << ((POS) * ST_BITS)); \
    if (VAL)                                                 \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

#define setOneVal4St(ST, POS, VAL)                               \
    ST &= ~(((unsigned long long)ST_MASK) << ((POS) * ST_BITS)); \
    if (VAL)                                                     \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

#define addSts(ST, LEN, CNT, IDX)                                                          \
    {                                                                                      \
        unordered_map<unsigned long long, unsigned int>::iterator it = cnts[IDX].find(ST); \
        if (it == cnts[IDX].end())                                                         \
        {                                                                                  \
            int pInQ = qTail[IDX];                                                         \
            qs[IDX][pInQ].state = ST;                                                      \
            qs[IDX][pInQ].len = LEN;                                                       \
            qs[IDX][pInQ].cnt = CNT;                                                       \
            cnts[IDX][ST] = pInQ;                                                          \
            qTail[IDX]++;                                                                  \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            if (LEN < qs[IDX][it->second].len)                                             \
            {                                                                              \
                qs[IDX][it->second].len = LEN;                                             \
                qs[IDX][it->second].cnt = CNT;                                             \
            }                                                                              \
            else if (LEN == qs[IDX][it->second].len)                                       \
            {                                                                              \
                qs[IDX][it->second].cnt += CNT;                                            \
                qs[IDX][it->second].cnt %= MOD;                                            \
            }                                                                              \
        }                                                                                  \
    }

#define forwardFunc(newSt, POS, plusVal, minusVal, newVal) \
    {                                                      \
        int pos = POS + 1;                                 \
        int s = 1;                                         \
        while (pos <= w)                                   \
        {                                                  \
            int v = getVal4St(newSt, pos);                 \
            if (plusVal == v)                              \
                s++;                                       \
            else if (minusVal == v)                        \
            {                                              \
                s--;                                       \
                if (0 == s)                                \
                {                                          \
                    setOneVal4St(newSt, pos, newVal);      \
                    break;                                 \
                }                                          \
            }                                              \
            pos++;                                         \
        }                                                  \
    }

#define backwardFunc(newSt, POS, plusVal, minusVal, newVal) \
    {                                                       \
        int pos = POS - 1;                                  \
        int s = 1;                                          \
        while (0 <= pos)                                    \
        {                                                   \
            int v = getVal4St(newSt, pos);                  \
            if (plusVal == v)                               \
                s++;                                        \
            else if (minusVal == v)                         \
            {                                               \
                s--;                                        \
                if (0 == s)                                 \
                {                                           \
                    setOneVal4St(newSt, pos, newVal);       \
                    break;                                  \
                }                                           \
            }                                               \
            pos--;                                          \
        }                                                   \
    }

#define CHECK(FLAG, VAL) \
    (10 < VAL || 0 == FLAG[0] || 0 < FLAG[VAL])

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    memset(flags, 0, sizeof(flags));

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].len = 0;
    qs[act][0].cnt = 1;

    qTail[act]++;
}

int main()
{
    int k;

    while (true)
    {
        cin >> w >> h >> k;

        if (0 == w && 0 == h && 0 == k)
        {
            break;
        }

        init();

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
                paths[row][col].clear();
            }
        }

        for (size_t i = 1; i <= k; i++)
        {
            unsigned int x, y;

            cin >> x >> y;
            paths[x + 1][y + 1].push_back(i);
            flags[x + 1][y + 1][0]++;
            flags[x + 1][y + 1][i] = 1;

            cin >> x >> y;
            paths[x + 1][y + 1].push_back(i);
            flags[x + 1][y + 1][0]++;
            flags[x + 1][y + 1][i] = 1;
        }

        int len = -1, cnt = 0;

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
                            if (0 > len || len > qs[act][iQ].len - k)
                            {
                                len = qs[act][iQ].len - k;
                                cnt = qs[act][iQ].cnt;
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

            if (1 == cells[now_x][now_y])
            {
                if (1 == now_y)
                {
                    for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        qs[act][iQ].state <<= ST_BITS;
                    }
                }

                continue;
            }

            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st = qs[act][iQ].state;
                unsigned int len = qs[act][iQ].len;
                unsigned int cnt = qs[act][iQ].cnt;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                if (0 < flags[now_x][now_y][0])
                {
                    // 电源
                    if (0 == left && 0 == up)
                    {
                        if (1 == paths[now_x][now_y].size())
                        {
                            if (h > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                if (CHECK(flags[now_x + 1][now_y], paths[now_x][now_y][0]))
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, paths[now_x][now_y][0]);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }
                            }

                            if (w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                if (CHECK(flags[now_x][now_y + 1], paths[now_x][now_y][0]))
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, paths[now_x][now_y][0] << ST_BITS);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }
                            }
                        }
                        else if (2 == paths[now_x][now_y].size())
                        {
                            if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                if (CHECK(flags[now_x + 1][now_y], paths[now_x][now_y][0]) && CHECK(flags[now_x][now_y + 1], paths[now_x][now_y][1]))
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, paths[now_x][now_y][0] + (paths[now_x][now_y][1] << ST_BITS));

                                    addSts(newSt, len + 2, cnt, nAct);
                                }

                                if (CHECK(flags[now_x + 1][now_y], paths[now_x][now_y][1]) && CHECK(flags[now_x][now_y + 1], paths[now_x][now_y][0]))
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, paths[now_x][now_y][1] + (paths[now_x][now_y][0] << ST_BITS));

                                    addSts(newSt, len + 2, cnt, nAct);
                                }
                            }
                        }
                    }
                    else
                    {
                        if (11 == left && 12 == up)
                        {
                            // 非法
                        }
                        else
                        {
                            unsigned long long newSt = st;
                            int leftEnd = 1, upEnd = 1;
                            int abCnt = 0;  // left 和 up 中大于 0 的个数
                            if (0 < left)
                            {
                                leftEnd = paths[now_x][now_y].size();
                                abCnt ++;
                            }

                            if (0 < up)
                            {
                                upEnd = paths[now_x][now_y].size();
                                abCnt ++;
                            }

                            for (size_t i = 0; i < leftEnd; i++)
                            {
                                if (0 == left || 10 < left || left == paths[now_x][now_y][i])
                                {
                                    int l = paths[now_x][now_y][i];
                                    if (0 == left)
                                    {
                                        l = 0;
                                    }
                                    else if (11 == left)
                                    {
                                        forwardFunc(newSt, now_y - 1, 11, 12, l);
                                        setOneVal4St(newSt, now_y - 1, l);
                                    }
                                    else if (12 == left)
                                    {
                                        backwardFunc(newSt, now_y - 1, 12, 11, l);
                                        setOneVal4St(newSt, now_y - 1, l);
                                    }

                                    for (size_t j = 0; j < upEnd; j++)
                                    {
                                        if (0 == up || 10 < up || up == paths[now_x][now_y][j])
                                        {
                                            int u = paths[now_x][now_y][j];
                                            if (0 == up)
                                            {
                                                u = 0;
                                            }

                                            if (l != u)
                                            {
                                                if (11 == up)
                                                {
                                                    forwardFunc(newSt, now_y, 11, 12, u);
                                                    setOneVal4St(newSt, now_y, u);
                                                }
                                                else if (12 == up)
                                                {
                                                    backwardFunc(newSt, now_y, 12, 11, u);
                                                    setOneVal4St(newSt, now_y, u);
                                                }

                                                vector<int> vs;

                                                for (size_t ip = 0; ip < paths[now_x][now_y].size(); ip++)
                                                {
                                                    if (l != paths[now_x][now_y][ip] && u != paths[now_x][now_y][ip])
                                                    {
                                                        vs.push_back(paths[now_x][now_y][ip]);
                                                    }
                                                }

                                                if (0 == vs.size())
                                                {
                                                    setVal4St(newSt, now_y - 1, 0);

                                                    addSts(newSt, len + abCnt, cnt, nAct);
                                                }
                                                else if (1 == vs.size())
                                                {
                                                    if (h > now_x && 0 == cells[now_x + 1][now_y])
                                                    {
                                                        if (CHECK(flags[now_x + 1][now_y], vs[0]))
                                                        {
                                                            setVal4St(newSt, now_y - 1, vs[0]);

                                                            addSts(newSt, len + abCnt + 1, cnt, nAct);
                                                        }
                                                    }

                                                    if (w > now_y && 0 == cells[now_x][now_y + 1])
                                                    {
                                                        if (CHECK(flags[now_x][now_y + 1], vs[0]))
                                                        {
                                                            setVal4St(newSt, now_y - 1, vs[0] << ST_BITS);

                                                            addSts(newSt, len + abCnt + 1, cnt, nAct);
                                                        }
                                                    }
                                                }
                                                else if (2 == vs.size())
                                                {
                                                    if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                                    {
                                                        if (CHECK(flags[now_x + 1][now_y], vs[0]) && CHECK(flags[now_x][now_y + 1], vs[1]))
                                                        {
                                                            setVal4St(newSt, now_y - 1, vs[0] + (vs[1] << ST_BITS));

                                                            addSts(newSt, len + abCnt + 2, cnt, nAct);
                                                        }

                                                        if (CHECK(flags[now_x + 1][now_y], vs[1]) && CHECK(flags[now_x][now_y + 1], vs[0]))
                                                        {
                                                            setVal4St(newSt, now_y - 1, vs[1] + (vs[0] << ST_BITS));

                                                            addSts(newSt, len + abCnt + 2, cnt, nAct);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    // 普通格子
                    if (left && up)
                    {
                        if (11 > left && 11 > up)
                        {
                            // 都是已经确定 path
                            if (left == up)
                            {
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, 0);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }

                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, 203);

                                    addSts(newSt, len + 2, cnt, nAct);
                                }
                            }
                            else
                            {
                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    // left ==> down, up ==> right
                                    if (CHECK(flags[now_x + 1][now_y], left) && CHECK(flags[now_x][now_y + 1], up))
                                    {
                                        addSts(st, len + 2, cnt, nAct);
                                    }
                                }
                            }
                        }
                        else if (10 < left && 10 < up)
                        {
                            // 都是未确定的 path
                            if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                // left ==> down, up ==> right
                                addSts(st, len + 2, cnt, nAct);
                            }

                            if (11 == left && 12 == up)
                            {
                                // 只能 left ==> down, up ==> right
                            }
                            else
                            {
                                unsigned long long newSt = st;

                                if (12 == left && 11 == up)
                                {
                                    // do nothing
                                }
                                else if (11 == left && 11 == up)
                                {
                                    forwardFunc(newSt, now_y, 11, 12, 11);
                                }
                                else
                                {
                                    // 12 == left && 12 == up
                                    backwardFunc(newSt, now_y - 1, 12, 11, 12);
                                }

                                {
                                    setVal4St(newSt, now_y - 1, 0);
                                    addSts(st, len + 1, cnt, nAct);
                                }

                                {
                                    setVal4St(newSt, now_y - 1, 203);
                                    addSts(newSt, len + 2, cnt, nAct);
                                }
                            }
                        }
                        else
                        {
                            // 一个已确定 path、一个未确定 path
                            if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                if (CHECK(flags[now_x + 1][now_y], left) && CHECK(flags[now_x][now_y + 1], up))
                                {
                                    // left ==> down, up ==> right
                                    addSts(st, len + 2, cnt, nAct);
                                }
                            }

                            unsigned long long newSt = st;
                            int low = left, high = up;
                            if (10 < left)
                            {
                                high = left;
                                low = up;
                            }

                            if (11 == high)
                            {
                                forwardFunc(newSt, now_y, 11, 12, low);
                            }
                            else
                            {
                                // 12 == high
                                backwardFunc(newSt, now_y - 1, 12, 11, low);
                            }

                            {
                                setVal4St(newSt, now_y - 1, 0);
                                addSts(st, len + 1, cnt, nAct);
                            }

                            {
                                setVal4St(newSt, now_y - 1, 203);
                                addSts(newSt, len + 2, cnt, nAct);
                            }
                        }
                    }
                    else if (left || up)
                    {
                        int val = left + up;
                        if (h > now_x && 0 == cells[now_x + 1][now_y])
                        {
                            if (10 < val || CHECK(flags[now_x + 1][now_y], val))
                            {
                                unsigned long long newSt = st;
                                setVal4St(newSt, now_y - 1, val);

                                addSts(newSt, len + 1, cnt, nAct);
                            }
                        }

                        if (w > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            if (10 < val || CHECK(flags[now_x][now_y + 1], val))
                            {
                                unsigned long long newSt = st;
                                setVal4St(newSt, now_y - 1, val << ST_BITS);

                                addSts(newSt, len + 1, cnt, nAct);
                            }
                        }
                    }
                    else
                    {
                        // 0 == left && 0 == up
                        {
                            // do nothing
                            addSts(st, len, cnt, nAct);
                        }

                        if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            // down - 11, up - 12
                            unsigned long long newSt = st;
                            setVal4St(newSt, now_y - 1, 203);

                            addSts(newSt, len + 1, cnt, nAct);
                        }
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        printf("%d %d\n", len, cnt);
    }

    return 0;
}
