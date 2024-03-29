// https://www.luogu.com.cn/problem/P6557

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
#define MAX_HW 16
#define QS_SIZE 65536
#define ST_BITS 1
#define ST_MASK 1
#define MOD 998244353

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

// 2 bits 合一 set
#define setVal4St(ST, POS, VAL)      \
    ST &= ~(3 << ((POS) * ST_BITS)); \
    if (VAL)                         \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, SUM, IDX)                                                         \
    {                                                                                \
        if (0 > cnts[ST] || cnts[ST] >= qTail[IDX] || qs[IDX][cnts[ST]].state != ST) \
        {                                                                            \
            int pInQ = qTail[IDX];                                                   \
            qs[IDX][pInQ].state = ST;                                                \
            qs[IDX][pInQ].sum = SUM;                                                 \
            cnts[ST] = pInQ;                                                         \
            qTail[IDX]++;                                                            \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            qs[IDX][cnts[ST]].sum += SUM;                                            \
            if (MOD < qs[IDX][cnts[ST]].sum)                                         \
                qs[IDX][cnts[ST]].sum -= MOD;                                        \
        }                                                                            \
    }

class Record
{
public:
    unsigned short state;
    unsigned int sum;

    Record() {}
};

int cells[MAX_HW][MAX_HW];
int h, w;
Record qs[2][QS_SIZE];
int qTail[2];
short cnts[65536];
int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned int maxSt = 0;
int backup[MAX_HW];
unsigned int ver[MAX_HW], hor[MAX_HW];

inline void init()
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].sum = 1;

    qTail[act]++;
}

inline unsigned int func()
{
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
                if (1 == qTail[act] && 0 == qs[act][0].state)
                {
                    ans = qs[act][0].sum;
                }

                break;
            }
        }
        else
        {
            now_y++;
        }

        if (0 == cells[now_x][now_y])
        {
            if (1 == now_y)
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    qs[act][iQ].state <<= ST_BITS;
                }
            }
        }
        else
        {
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned short st = qs[act][iQ].state;
                unsigned int sum = qs[act][iQ].sum;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                unsigned int left = getVal4St(st, now_y - 1);
                unsigned int up = getVal4St(st, now_y);

                if (left && up)
                {
                    // 非法
                }
                else if (left)
                {
                    // 不再延伸
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 0);

                        addSts(newSt, sum, nAct);
                    }

                    // 延续
                    if (w > now_y && 1 == cells[now_x][now_y + 1])
                    {
                        unsigned int rightUp = getVal4St(st, now_y + 1);
                        if (0 == rightUp)
                        {
                            unsigned int newSt = st;

                            setVal4St(newSt, now_y - 1, 2);

                            addSts(newSt, sum, nAct);
                        }
                    }
                }
                else if (up)
                {
                    // 不再延伸
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 0);

                        addSts(newSt, sum, nAct);
                    }

                    // 延伸
                    if (h > now_x && 1 == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 1);

                        addSts(newSt, sum, nAct);
                    }
                }
                else
                {
                    // 0 == left && 0 == up
                    // 不放置
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 0);

                        addSts(newSt, sum, nAct);
                    }

                    // 向右延续
                    if (w > now_y && 1 == cells[now_x][now_y + 1])
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 2);

                        addSts(newSt, sum, nAct);
                    }

                    // 向下延伸
                    if (h > now_x && 1 == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 1);

                        addSts(newSt, sum, nAct);
                    }
                }
            }

            qTail[act] = 0;
            act = nAct;
        }
    }

    printf("%u\n", ans);

    return ans;
}

int main()
{
    scanf("%d %d", &h, &w);

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            scanf("%d", &(cells[row][col]));
        }
    }

    maxSt = 1 << (w + 1);

    init();
    func();

    int t;
    scanf("%d", &t);

    for (size_t iT = 0; iT < t; iT++)
    {
        init();

        int op;
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        {
            int x, y;
            scanf("%d %d", &x, &y);

            backup[0] = cells[x][y];
            cells[x][y] = 0;

            func();

            cells[x][y] = backup[0];
        }
        break;
        case 2:
        {
            int row;
            scanf("%d", &row);

            if (hor[row])
            {
                printf("%d\n", hor[row]);
            }
            else
            {
                for (size_t col = 1; col <= w; col++)
                {
                    backup[col] = cells[row][col];
                    cells[row][col] = 0;
                }

                hor[row] = func();

                for (size_t col = 1; col <= w; col++)
                {
                    cells[row][col] = backup[col];
                }
            }
        }
        break;
        case 3:
        {
            int col;
            scanf("%d", &col);

            if (ver[col])
            {
                printf("%d\n", ver[col]);
            }
            else
            {
                for (size_t row = 1; row <= h; row++)
                {
                    backup[row] = cells[row][col];
                    cells[row][col] = 0;
                }

                ver[col] = func();

                for (size_t row = 1; row <= h; row++)
                {
                    cells[row][col] = backup[row];
                }
            }
        }
        break;
        case 4:
        {
            int x, y, k;
            scanf("%d %d %d", &x, &y, &k);

            for (size_t i = 0; i <= k; i++)
            {
                backup[i] = cells[x][y + i];
                cells[x][y + i] = 0;
            }

            func();

            for (size_t i = 0; i <= k; i++)
            {
                cells[x][y + i] = backup[i];
            }
        }
        break;
        case 5:
        default:
        {
            int x, y, k;
            scanf("%d %d %d", &x, &y, &k);

            for (size_t i = 0; i <= k; i++)
            {
                backup[i] = cells[x + i][y];
                cells[x + i][y] = 0;
            }

            func();

            for (size_t i = 0; i <= k; i++)
            {
                cells[x + i][y] = backup[i];
            }
        }
        break;
        }
    }

    return 0;
}
