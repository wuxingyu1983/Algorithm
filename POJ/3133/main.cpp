// http://poj.org/problem;jsessionid=49743215C3FBD3C529FBB64C68579633?id=3133

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
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
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int len;

    Record() {}
};

int cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
// unordered_map<unsigned int, unsigned int> cnts[2];
int cnts[2][1048576];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)     \
    ST &= ~(15 << ((POS)*ST_BITS)); \
    if (VAL)                        \
        ST |= (VAL) << ((POS)*ST_BITS);

/*
#define setVal4St(NEW, OLD, POS, VAL)     \
    NEW = OLD;                            \
    NEW &= ~(ST_MASK << ((POS)*ST_BITS)); \
    NEW |= (VAL) << ((POS)*ST_BITS);
*/

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    memset(cnts[0], -1, sizeof(cnts[0]));
    memset(cnts[1], -1, sizeof(cnts[1]));

    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].len = 0;

    qTail[act]++;
}

#define addSts(ST, LEN, IDX)           \
    {                                  \
        int it = cnts[IDX][ST];        \
        if (0 > it)                    \
        {                              \
            int pInQ = qTail[IDX];     \
            qs[IDX][pInQ].state = ST;  \
            qs[IDX][pInQ].len = LEN;   \
            cnts[IDX][ST] = pInQ;      \
            qTail[IDX]++;              \
        }                              \
        else                           \
        {                              \
            if (LEN < qs[IDX][it].len) \
                qs[IDX][it].len = LEN; \
        }                              \
    }

int main()
{
    while (true)
    {
        scanf("%d %d", &h, &w);

        if (0 == h && 0 == w)
        {
            break;
        }

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                scanf("%d", &cells[row][col]);
            }
        }

        init();

        int ans = 0;

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
                            if (0 == ans || ans > (qs[act][iQ].len - 2))
                            {
                                ans = qs[act][iQ].len - 2;
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
                unsigned int st = qs[act][iQ].state;
                unsigned int len = qs[act][iQ].len;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                if (1 == cells[now_x][now_y])
                {
                    // 障碍物
                    addSts(st, len, nAct);
                }
                else if (0 == cells[now_x][now_y])
                {
                    if (0 == left && 0 == up)
                    {
                        // do nothing
                        addSts(st, len, nAct);

                        if (h > now_x && w > now_y && 1 != cells[now_x + 1][now_y] && 1 != cells[now_x][now_y + 1])
                        {
                            if (3 != cells[now_x + 1][now_y] && 3 != cells[now_x][now_y + 1])
                            {
                                unsigned int newSt = st;
                                // 2, 2
                                setVal4St(newSt, now_y - 1, 10);

                                addSts(newSt, len + 1, nAct);
                            }

                            if (2 != cells[now_x + 1][now_y] && 2 != cells[now_x][now_y + 1])
                            {
                                unsigned int newSt = st;
                                // 3, 3
                                setVal4St(newSt, now_y - 1, 15);

                                addSts(newSt, len + 1, nAct);
                            }
                        }
                    }
                    else if (0 == left || 0 == up)
                    {
                        // 有1个 plug
                        int val = left + up;
                        unsigned int newSt;

                        if (h > now_x && 1 != cells[now_x + 1][now_y])
                        {
                            if (0 == cells[now_x + 1][now_y] || val == cells[now_x + 1][now_y])
                            {
                                newSt = st;
                                setVal4St(newSt, now_y - 1, val);

                                addSts(newSt, len + 1, nAct);
                            }
                        }

                        if (w > now_y && 1 != cells[now_x][now_y + 1])
                        {
                            if (0 == cells[now_x][now_y + 1] || val == cells[now_x][now_y + 1])
                            {
                                newSt = st;
                                setVal4St(newSt, now_y - 1, val << 2);

                                addSts(newSt, len + 1, nAct);
                            }
                        }
                    }
                    else
                    {
                        // 有2个 plug
                        if (left == up)
                        {
                            unsigned int newSt = st;

                            setVal4St(newSt, now_y - 1, 0);

                            addSts(newSt, len + 1, nAct);
                        }
                    }
                }
                else if (2 == cells[now_x][now_y])
                {
                    unsigned int newSt = st;
                    if (0 == left && 0 == up)
                    {
                        if (h > now_x && 1 != cells[now_x + 1][now_y])
                        {
                            if (3 != cells[now_x + 1][now_y])
                            {
                                newSt = st;
                                setVal4St(newSt, now_y - 1, 2);

                                addSts(newSt, len + 1, nAct);
                            }
                        }

                        if (w > now_y && 1 != cells[now_x][now_y + 1])
                        {
                            if (3 != cells[now_x][now_y + 1])
                            {
                                newSt = st;
                                setVal4St(newSt, now_y - 1, 8);

                                addSts(newSt, len + 1, nAct);
                            }
                        }
                    }
                    else if (0 == left || 0 == up)
                    {
                        int val = left + up;
                        if (2 == val)
                        {
                            setVal4St(newSt, now_y - 1, 0);

                            addSts(newSt, len + 1, nAct);
                        }
                    }
                }
                else
                {
                    // 3 == cells[now_x][now_y]
                    unsigned int newSt = st;
                    if (0 == left && 0 == up)
                    {
                        if (h > now_x && 1 != cells[now_x + 1][now_y])
                        {
                            if (2 != cells[now_x + 1][now_y])
                            {
                                newSt = st;
                                setVal4St(newSt, now_y - 1, 3);

                                addSts(newSt, len + 1, nAct);
                            }
                        }

                        if (w > now_y && 1 != cells[now_x][now_y + 1])
                        {
                            if (2 != cells[now_x][now_y + 1])
                            {
                                newSt = st;
                                setVal4St(newSt, now_y - 1, 12);

                                addSts(newSt, len + 1, nAct);
                            }
                        }
                    }
                    else if (0 == left || 0 == up)
                    {
                        int val = left + up;
                        if (3 == val)
                        {
                            setVal4St(newSt, now_y - 1, 0);

                            addSts(newSt, len + 1, nAct);
                        }
                    }
                }
            }

            qTail[act] = 0;
            memset(cnts[act], -1, sizeof(cnts[act]));
            act = nAct;
        }

        printf("%d\n", ans);
    }

    return 0;
}
