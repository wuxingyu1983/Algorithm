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
#define QS_SIZE 70000
#define ST_BITS 1
#define ST_MASK 1
#define MOD 998244353

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, SUM, IDX)                       \
    {                                              \
        if (0 > cnts[IDX][ST])                     \
        {                                          \
            int pInQ = qTail[IDX];                 \
            qs[IDX][pInQ].state = ST;              \
            qs[IDX][pInQ].sum = SUM;               \
            cnts[IDX][ST] = pInQ;                  \
            qTail[IDX]++;                          \
        }                                          \
        else                                       \
        {                                          \
            qs[IDX][cnts[IDX][ST]].sum += SUM;     \
            if (MOD < qs[IDX][cnts[IDX][ST]].sum)  \
                qs[IDX][cnts[IDX][ST]].sum -= MOD; \
        }                                          \
    }

class Record
{
public:
    unsigned int state;
    unsigned int sum;

    Record() {}
};

int raw[MAX_HW][MAX_HW];
int cells[MAX_HW][MAX_HW];
int h, w;
Record qs[2][QS_SIZE];
int qTail[2];
int cnts[2][70000];
int act = 0; // 当前生效的 map
int now_x, now_y;

void init()
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    memset(cnts[0], -1, sizeof(cnts[0]));
    memset(cnts[1], -1, sizeof(cnts[1]));

    memcpy(cells, raw, sizeof(raw));

    now_x = 0;
    now_y = w;

    qs[act][0].sum = 1;

    qTail[act]++;
}

void func()
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
                unsigned int st = qs[act][iQ].state;
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
                        setVal4St(newSt, now_y, 0);

                        addSts(newSt, sum, nAct);
                    }

                    // 延续
                    if (w > now_y && 1 == cells[now_x][now_y + 1])
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 1);

                        addSts(newSt, sum, nAct);
                    }
                }
                else if (up)
                {
                    // 不再延伸
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 0);

                        addSts(newSt, sum, nAct);
                    }

                    // 延伸
                    if (h > now_x && 1 == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 1);
                        setVal4St(newSt, now_y, 0);

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
                        setVal4St(newSt, now_y, 0);

                        addSts(newSt, sum, nAct);
                    }

                    // 向右延续
                    if (w > now_y && 1 == cells[now_x][now_y + 1])
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, 1);

                        addSts(newSt, sum, nAct);
                    }

                    // 向下延伸
                    if (h > now_x && 1 == cells[now_x + 1][now_y])
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 1);
                        setVal4St(newSt, now_y, 0);

                        addSts(newSt, sum, nAct);
                    }
                }
            }

            qTail[act] = 0;
            memset(cnts[act], -1, sizeof(cnts[act]));
            act = nAct;
        }
    }

    cout << ans << endl;
}

int main()
{
    cin >> h >> w;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            cin >> raw[row][col];
        }
    }

    init();
    func();

    int t;
    cin >> t;

    for (size_t iT = 0; iT < t; iT++)
    {
        init();

        int op;
        cin >> op;

        switch (op)
        {
        case 1:
        {
            int x, y;
            cin >> x >> y;

            cells[x][y] = 0;
        }
        break;
        case 2:
        {
            int row;
            cin >> row;

            for (size_t col = 1; col <= w; col++)
            {
                cells[row][col] = 0;
            }
        }
        break;
        case 3:
        {
            int col;
            cin >> col;

            for (size_t row = 1; row <= h; row++)
            {
                cells[row][col] = 0;
            }
        }
        break;
        case 4:
        {
            int x, y, k;
            cin >> x >> y >> k;

            for (size_t i = 0; i <= k; i++)
            {
                cells[x][y + i] = 0;
            }
        }
        break;
        case 5:
        default:
        {
            int x, y, k;
            cin >> x >> y >> k;

            for (size_t i = 0; i <= k; i++)
            {
                cells[x + i][y] = 0;
            }
        }
        break;
        }

        func();
    }

    return 0;
}
