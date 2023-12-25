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
#define QS_SIZE 100000
#define ST_BITS 2
#define ST_MASK 3
#define MOD 998244353

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, SUM, IDX)                                                         \
    {                                                                                \
        unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX].find(ST); \
        if (it == cnts[IDX].end())                                                   \
        {                                                                            \
            int pInQ = qTail[IDX];                                                   \
            qs[IDX][pInQ].state = ST;                                                \
            qs[IDX][pInQ].sum = SUM;                                                 \
            cnts[IDX][ST] = pInQ;                                                    \
            qTail[IDX]++;                                                            \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            qs[IDX][it->second].sum += SUM;                                          \
            if (MOD < qs[IDX][it->second].sum)                                       \
                qs[IDX][it->second].sum -= MOD;                                      \
        }                                                                            \
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
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

void init()
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;
    cnts[0].clear();
    cnts[1].clear();

    memcpy(cells, raw, sizeof(raw));

    now_x = 0;
    now_y = w;

    qs[act][0].sum = 1;

    qTail[act]++;
}

void func()
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
                // TBD

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
            unsigned int sum = qs[act][iQ].sum;

                if (0 == cells[now_x][now_y])
            {
                // 障碍物
                setVal4St(st, now_y, 0);

                addSts(st, sum, nAct);
            }
            else
            {
                unsigned int left = getVal4St(st, now_y - 1);
                unsigned int up = getVal4St(st, now_y);
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }
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
