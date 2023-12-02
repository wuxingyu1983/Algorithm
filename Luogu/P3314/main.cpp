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
bool bValid;

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
                if (qs[IDX][it->second].cnt > MOD)                                         \
                    qs[IDX][it->second].cnt -= MOD;                                        \
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

    bValid = true;
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
            unsigned int x1, y1, x2, y2;

            cin >> x1 >> y1 >> x2 >> y2;
            paths[x1 + 1][y1 + 1].push_back(i);
            flags[x1 + 1][y1 + 1][0]++;
            flags[x1 + 1][y1 + 1][i] = 1;

            paths[x2 + 1][y2 + 1].push_back(i);
            flags[x2 + 1][y2 + 1][0]++;
            flags[x2 + 1][y2 + 1][i] = 1;

            if (x1 == x2 && y1 == y2)
            {
                bValid = false;
            }
        }

        int len = -1, cnt = 0;

        if (bValid)
        {
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
                            if ((0 == left || 10 < left || 1 == flags[now_x][now_y][left]) && (0 == up || 10 < up || 1 == flags[now_x][now_y][up]))
                            {
                                if (11 == left && 12 == up)
                                {
                                    // 非法
                                }
                                else
                                {
                                    int abCnt = 0; // left 和 up 中大于 0 的个数

                                    vector<int> vecLeft;
                                    if (0 == left)
                                    {
                                        vecLeft.push_back(left);
                                    }
                                    else if (10 < left)
                                    {
                                        vecLeft.assign(paths[now_x][now_y].begin(), paths[now_x][now_y].end());
                                        abCnt++;
                                    }
                                    else
                                    {
                                        vecLeft.push_back(left);
                                        abCnt++;
                                    }

                                    vector<int> vecUp;
                                    if (0 == up)
                                    {
                                        vecUp.push_back(up);
                                    }
                                    else if (10 < up)
                                    {
                                        vecUp.assign(paths[now_x][now_y].begin(), paths[now_x][now_y].end());
                                        abCnt++;
                                    }
                                    else
                                    {
                                        vecUp.push_back(up);
                                        abCnt++;
                                    }

                                    for (vector<int>::iterator itLeft = vecLeft.begin(); itLeft != vecLeft.end(); itLeft++)
                                    {
                                        for (vector<int>::iterator itUp = vecUp.begin(); itUp != vecUp.end(); itUp++)
                                        {
                                            if (*itLeft != *itUp)
                                            {
                                                unsigned long long newSt = st;

                                                if (11 == left)
                                                {
                                                    forwardFunc(newSt, now_y - 1, 11, 12, *itLeft);
                                                    setOneVal4St(newSt, now_y - 1, *itLeft);
                                                }
                                                else if (12 == left)
                                                {
                                                    backwardFunc(newSt, now_y - 1, 12, 11, *itLeft);
                                                    setOneVal4St(newSt, now_y - 1, *itLeft);
                                                }

                                                if (11 == up)
                                                {
                                                    forwardFunc(newSt, now_y, 11, 12, *itUp);
                                                    setOneVal4St(newSt, now_y, *itUp);
                                                }
                                                else if (12 == up)
                                                {
                                                    backwardFunc(newSt, now_y, 12, 11, *itUp);
                                                    setOneVal4St(newSt, now_y, *itUp);
                                                }

                                                vector<int> vs;

                                                for (size_t ip = 0; ip < paths[now_x][now_y].size(); ip++)
                                                {
                                                    if (*itLeft != paths[now_x][now_y][ip] && *itUp != paths[now_x][now_y][ip])
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
                                    // 否则行程闭环
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
                                        addSts(newSt, len + 1, cnt, nAct);
                                    }

                                    if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
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
                                if (low > high)
                                {
                                    swap(low, high);
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
                                    addSts(newSt, len + 1, cnt, nAct);
                                }

                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
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
                                if (CHECK(flags[now_x + 1][now_y], val))
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, val);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }
                            }

                            if (w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                if (CHECK(flags[now_x][now_y + 1], val))
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
        }

        printf("%d %d\n", len, cnt);
    }

    return 0;
}
