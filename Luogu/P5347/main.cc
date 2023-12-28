// https://www.luogu.com.cn/problem/P5347

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
#define MAX_HW 10
#define ST_BITS 4
#define ST_MASK 15
#define QS_SIZE 600000
#define MOD 998244353

#define getVal4St(ST, POS) (((ST) >> ((POS) * ST_BITS)) & ST_MASK)

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

class Record
{
public:
    unsigned long long state; // 轮廓线cell状态
    unsigned long long sum;

    unsigned char minUnused;

    Record() {}
};

char cells[MAX_HW][MAX_HW];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w, c, op;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

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

int main()
{
    cin >> h >> w >> c >> op;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            cin >> cells[row][col];
        }
    }

    // init
    {
        act = 0;

        now_x = 0;
        now_y = w;

        qs[act][0].minUnused = 1;

        qTail[act]++;
    }

    if (op)
    {

    }
    else
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

            if ('#' == cells[now_x][now_y])
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
                    unsigned long long st = qs[act][iQ].state;
                    unsigned long long sum = qs[act][iQ].sum;
                    unsigned char minUnused = qs[act][iQ].minUnused;

                    if (1 == now_y)
                    {
                        st <<= ST_BITS;
                    }


                }

                qTail[act] = 0;
                cnts[act].clear();
                act = nAct;
            }
        }
    }

    return 0;
}
