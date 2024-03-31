// https://www.luogu.com.cn/problem/UVA11270
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2245

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
#define MAX_MN 101
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 2100

class Record
{
public:
    unsigned short state; // 轮廓线段状态
    unsigned long long count;

    Record() {}
};

long long cells[MAX_MN][MAX_MN];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
int cnts[2][2050];
int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long ans;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, CNT, IDX)                 \
    if (0 > cnts[IDX][ST])                   \
    {                                        \
        int pInQ = qTail[IDX];               \
        qs[IDX][pInQ].state = ST;            \
        qs[IDX][pInQ].count = CNT;           \
        cnts[IDX][ST] = pInQ;                \
        qTail[IDX]++;                        \
    }                                        \
    else                                     \
    {                                        \
        qs[IDX][cnts[IDX][ST]].count += CNT; \
    }

int main()
{
    while (cin >> h >> w)
    {
        if (h < w)
        {
            swap(h, w);
        }

        if ((h & 1) && (w & 1))
        {
            cout << 0 << endl;
            continue;
        }

        // init
        act = 0;

        now_x = 0;
        now_y = w;

        qs[act][0].state = 0;
        qs[act][0].count = 1;

        qTail[0] = 1;
        qTail[1] = 0;

        memset(cnts[0], -1, sizeof(int) * 2050);
        memset(cnts[1], -1, sizeof(int) * 2050);

        while (0 < qTail[act])
        {
            int nAct = 1 - act;

            if (w == now_y)
            {
                now_x++;
                now_y = 1;

                if (h < now_x)
                {
                    if (1 == qTail[act])
                    {
                        if (0 == qs[act][0].state)
                        {
                            ans = qs[act][0].count;
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
                unsigned short st = qs[act][iQ].state;
                unsigned long long cnt = qs[act][iQ].count;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                unsigned short left = getVal4St(st, now_y - 1);
                unsigned short up = getVal4St(st, now_y);

                if (left && up)
                {
                    // invalid
                }
                else if (left || up)
                {
                    unsigned short newSt = st;
                    
                    setVal4St(newSt, now_y - 1, 0);
                    setVal4St(newSt, now_y, 0);

                    addSts(newSt, cnt, nAct);
                }
                else
                {
                    // 0 == left && 0 == up
                    if (h > now_x)
                    {
                        unsigned short newSt = st;

                        setVal4St(newSt, now_y - 1, 1);

                        addSts(newSt, cnt, nAct);
                    }

                    if (w > now_y)
                    {
                        unsigned short newSt = st;

                        setVal4St(newSt, now_y, 1);

                        addSts(newSt, cnt, nAct);
                    }
                }
            }

            qTail[act] = 0;
            memset(cnts[act], -1, sizeof(int) * 2050);
            act = nAct;
        }

        cout << ans << endl;
    }

    return 0;
}
