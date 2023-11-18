// https://www.luogu.com.cn/problem/P3170

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
#define MAX_HW 31
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int ls;    // 已经有的 L 的个数
    unsigned long long cnt;

    Record() {}
};

char cells[MAX_HW][MAX_HW];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2][4];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, LS, CNT, IDX)                                                         \
    {                                                                                    \
        unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX][LS].find(ST); \
        if (it == cnts[IDX][LS].end())                                                   \
        {                                                                                \
            int pInQ = qTail[IDX];                                                       \
            qs[IDX][pInQ].state = ST;                                                    \
            qs[IDX][pInQ].ls = LS;                                                       \
            qs[IDX][pInQ].cnt = CNT;                                                     \
            cnts[IDX][LS][ST] = pInQ;                                                    \
            qTail[IDX]++;                                                                \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            qs[IDX][it->second].cnt += CNT;                                              \
        }                                                                                \
    }

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].ls = 0;
    qs[act][0].cnt = 1;

    qTail[act]++;
}

int main()
{
    cin >> h >> w;

    for (size_t i = 1; i <= h; i++)
    {
        for (size_t j = 1; j <= w; j++)
        {
            cin >> cells[i][j];
        }
    }

    init();
    unsigned long long ans = 0;

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
            unsigned int ls = qs[act][iQ].ls;
            unsigned long long cnt = qs[act][iQ].cnt;

            if (1 == now_y)
            {
                st <<= ST_BITS;
            }

            if ('#' == cells[now_x][now_y])
            {
                // 障碍物
                addSts(st, ls, cnt, nAct);
            }
            else
            {
                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                if (left && up)
                {
                    // 非法
                }
                else if (left)
                {
                    {
                        // 截断
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 0);

                        if (3 == ls && 0 == newSt)
                        {
                            ans += cnt;
                        }
                        else
                        {
                            addSts(newSt, ls, cnt, nAct);
                        }
                    }

                    if (w > now_y && '.' == cells[now_x][now_y + 1])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 1);

                        addSts(newSt, ls, cnt, nAct);
                    }
                }
                else if (up)
                {
                    if (h > now_x && '.' == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 1);
                        setVal4St(newSt, now_y, 0);

                        addSts(newSt, ls, cnt, nAct);
                    }

                    if (w > now_y && '.' == cells[now_x][now_y + 1])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 1);

                        addSts(newSt, ls, cnt, nAct);
                    }
                }
                else
                {
                    // 0 == left && 0 == up
                    // do nothing
                    addSts(st, ls, cnt, nAct);

                    // new L
                    if (3 > ls && h > now_x && '.' == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 1);
                        setVal4St(newSt, now_y, 0);

                        addSts(newSt, ls + 1, cnt, nAct);
                    }
                }
            }
        }

        qTail[act] = 0;
        cnts[act][0].clear();
        cnts[act][1].clear();
        cnts[act][2].clear();
        cnts[act][3].clear();
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
