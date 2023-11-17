// https://www.luogu.com.cn/problem/P1713

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
#define MAX_HW 11
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int max, min;

    Record() {}
};

char cells[MAX_HW][MAX_HW];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)     \
    ST &= ~(15 << ((POS)*ST_BITS)); \
    if (VAL)                        \
        ST |= (VAL) << ((POS)*ST_BITS);

#define addSts(ST, MAX, MIN, IDX)                                                    \
    {                                                                                \
        unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX].find(ST); \
        if (it == cnts[IDX].end())                                                   \
        {                                                                            \
            int pInQ = qTail[IDX];                                                   \
            qs[IDX][pInQ].state = ST;                                                \
            qs[IDX][pInQ].max = MAX;                                                 \
            qs[IDX][pInQ].min = MIN;                                                 \
            cnts[IDX][ST] = pInQ;                                                    \
            qTail[IDX]++;                                                            \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            if (MIN < qs[IDX][it->second].min)                                       \
                qs[IDX][it->second].min = MIN;                                       \
            if (MAX > qs[IDX][it->second].max)                                       \
                qs[IDX][it->second].max = MAX;                                       \
        }                                                                            \
    }

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state = 3 << ((w - 1) * ST_BITS);
    qs[act][0].max = 0;
    qs[act][0].min = 0;

    qTail[act]++;
}

int main()
{
    int m;
    cin >> h >> m;

    w = h;

    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        cells[x][y] = 1;
    }
    
    init();

    int max = 0, min = 0;

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
            unsigned int max = qs[act][iQ].max;
            unsigned int min = qs[act][iQ].min;

            if (1 == now_y)
            {
                st <<= ST_BITS;
            }

            int left = getVal4St(st, now_y - 1);
            int up = getVal4St(st, now_y);

            if (h == now_x && 1 == now_y)
            {

            }
            else
            {

            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
