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
#define QS_SIZE 1000000
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
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)                                  \
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

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

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

        for (size_t row = 1; row <= h; row ++)
        {
            for (size_t col = 1; col <= w; col ++)
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

            cin >> x >> y;
            paths[x + 1][y + 1].push_back(i);
        }

        init();

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

            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st = qs[act][iQ].state;
                unsigned int len = qs[act][iQ].len;
                unsigned int cnt = qs[act][iQ].cnt;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                if (1 == cells[now_x][now_y])
                {
                    // 障碍物
                    addSts(st, len, cnt, nAct);
                }
                else
                {
                    int left = getVal4St(st, now_y - 1);
                    int up = getVal4St(st, now_y);

                    if (0 < paths[now_x][now_y].size())
                    {
                        // 电源
                        if (left && up)
                        {
                            if (left != up)
                            {
                                vector<int> vs;

                                for (size_t i = 0; i < paths[now_x][now_y].size(); i++)
                                {
                                    if (left != paths[now_x][now_y][i] && up != paths[now_x][now_y][i])
                                    {
                                        vs.push_back(paths[now_x][now_y][i]);
                                    }
                                }

                                if (vs.size() + 2 == paths[now_x][now_y].size())
                                {
                                    if (0 == vs.size())
                                    {
                                        unsigned long long newSt = st;
                                        setVal4St(newSt, now_y - 1, 0);
                                        setVal4St(newSt, now_y, 0);

                                        addSts(newSt, len + 2, cnt, nAct);
                                    }
                                    else if (1 == vs.size())
                                    {
                                        if (h > now_x && 0 == cells[now_x + 1][now_y])
                                        {
                                            unsigned long long newSt = st;
                                            setVal4St(newSt, now_y - 1, vs[0]);
                                            setVal4St(newSt, now_y, 0);

                                            addSts(newSt, len + 3, cnt, nAct);
                                        }

                                        if (w > now_y && 0 == cells[now_x][now_y + 1])
                                        {
                                            unsigned long long newSt = st;
                                            setVal4St(newSt, now_y - 1, 0);
                                            setVal4St(newSt, now_y, vs[0]);

                                            addSts(newSt, len + 3, cnt, nAct);
                                        }
                                    }
                                    else if (2 == vs.size())
                                    {
                                        if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                        {
                                            unsigned long long newSt = st;
                                            setVal4St(newSt, now_y - 1, vs[0]);
                                            setVal4St(newSt, now_y, vs[1]);

                                            addSts(newSt, len + 4, cnt, nAct);

                                            newSt = st;
                                            setVal4St(newSt, now_y - 1, vs[1]);
                                            setVal4St(newSt, now_y, vs[0]);

                                            addSts(newSt, len + 4, cnt, nAct);
                                        }
                                    }
                                }
                            }
                        }
                        else if (left || up)
                        {
                            int val = left + up;
                            vector<int> vs;

                            for (size_t i = 0; i < paths[now_x][now_y].size(); i++)
                            {
                                if (val != paths[now_x][now_y][i])
                                {
                                    vs.push_back(paths[now_x][now_y][i]);
                                }
                            }

                            if (vs.size() + 1 == paths[now_x][now_y].size())
                            {
                                if (0 == vs.size())
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, 0);
                                    setVal4St(newSt, now_y, 0);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }
                                else if (1 == vs.size())
                                {
                                    if (h > now_x && 0 == cells[now_x + 1][now_y])
                                    {
                                        unsigned long long newSt = st;
                                        setVal4St(newSt, now_y - 1, vs[0]);
                                        setVal4St(newSt, now_y, 0);

                                        addSts(newSt, len + 2, cnt, nAct);
                                    }

                                    if (w > now_y && 0 == cells[now_x][now_y + 1])
                                    {
                                        unsigned long long newSt = st;
                                        setVal4St(newSt, now_y - 1, 0);
                                        setVal4St(newSt, now_y, vs[0]);

                                        addSts(newSt, len + 2, cnt, nAct);
                                    }
                                }
                                else if (2 == vs.size())
                                {
                                    if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                    {
                                        unsigned long long newSt = st;
                                        setVal4St(newSt, now_y - 1, vs[0]);
                                        setVal4St(newSt, now_y, vs[1]);

                                        addSts(newSt, len + 3, cnt, nAct);

                                        newSt = st;
                                        setVal4St(newSt, now_y - 1, vs[1]);
                                        setVal4St(newSt, now_y, vs[0]);

                                        addSts(newSt, len + 3, cnt, nAct);
                                    }
                                }
                            }
                        }
                        else
                        {
                            // 0 == left && 0 == up
                            if (1 == paths[now_x][now_y].size())
                            {
                                if (h > now_x && 0 == cells[now_x + 1][now_y])
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, paths[now_x][now_y][0]);
                                    setVal4St(newSt, now_y, 0);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }

                                if (w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, 0);
                                    setVal4St(newSt, now_y, paths[now_x][now_y][0]);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }
                            }
                            else if (2 == paths[now_x][now_y].size())
                            {
                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, paths[now_x][now_y][0]);
                                    setVal4St(newSt, now_y, paths[now_x][now_y][1]);

                                    addSts(newSt, len + 2, cnt, nAct);

                                    newSt = st;
                                    setVal4St(newSt, now_y - 1, paths[now_x][now_y][1]);
                                    setVal4St(newSt, now_y, paths[now_x][now_y][0]);

                                    addSts(newSt, len + 2, cnt, nAct);
                                }
                            }
                        }
                    }
                    else
                    {
                        // 普通格子
                        if (left && up)
                        {
                            if (left == up)
                            {
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, 0);
                                    setVal4St(newSt, now_y, 0);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }

                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    for (size_t color = 1; color <= k; color++)
                                    {
                                        if (color != left)
                                        {
                                            unsigned long long newSt = st;
                                            setVal4St(newSt, now_y - 1, color);
                                            setVal4St(newSt, now_y, color);

                                            addSts(newSt, len + 2, cnt, nAct);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    // left ==> down, up ==> right
                                    addSts(st, len + 2, cnt, nAct);
                                }
                            }
                        }
                        else if (left || up)
                        {
                            int val = left + up;
                            if (h > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                unsigned long long newSt = st;
                                setVal4St(newSt, now_y - 1, val);
                                setVal4St(newSt, now_y, 0);

                                addSts(newSt, len + 1, cnt, nAct);
                            }

                            if (w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                unsigned long long newSt = st;
                                setVal4St(newSt, now_y - 1, 0);
                                setVal4St(newSt, now_y, val);

                                addSts(newSt, len + 1, cnt, nAct);
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
                                for (size_t color = 1; color <= k; color++)
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, color);
                                    setVal4St(newSt, now_y, color);

                                    addSts(newSt, len + 1, cnt, nAct);
                                }
                            }
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
