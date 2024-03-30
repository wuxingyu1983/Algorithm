// https://www.luogu.com.cn/problem/CF762D
// https://codeforces.com/problemset/problem/762/D

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
#define MAX_N 100001
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 6000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    long long sum;

    Record() {}
};

long long cells[MAX_N][4];
Record qs[2][QS_SIZE];
int qTail[2];
int n;      // row
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;
long long ans;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

#define addSts(ST, SUM, IDX)                                                     \
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
        if (qs[IDX][it->second].sum < SUM)                                       \
            qs[IDX][it->second].sum = SUM;                                       \
    }

int main()
{
    cin >> n;

    for (size_t col = 1; col <= 3; col++)
    {
        for (size_t row = 1; row <= n; row++)
        {
            cin >> cells[row][col];
        }
    }

    // init
    ans = 0;

    act = 0;

    now_x = 0;
    now_y = 3;

    qs[act][0].state = 0;
    qs[act][0].sum = 0;

    qTail[act]++;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;

        if (3 == now_y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
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
            long long sum = qs[act][iQ].sum;

            if (1 == now_y)
            {
                st <<= ST_BITS;
            }

            unsigned int left = getVal4St(st, now_y - 1);
            unsigned int up = getVal4St(st, now_y);

            if (1 == now_x && 1 == now_y)
            {
                // 起点
                if (n > now_x)
                {
                    unsigned int newSt = st;

                    setVal4St(newSt, 0, 3);

                    addSts(newSt, cells[now_x][now_y], nAct);
                }

                {
                    unsigned int newSt = st;

                    setVal4St(newSt, 1, 3);

                    addSts(newSt, cells[now_x][now_y], nAct);
                }
            }
            else if (n == now_x && 3 == now_y)
            {
                // 终点
                if (left && up)
                {
                    // invalid
                }
                else if (left || up)
                {
                    unsigned int newSt = st;
                    setVal4St(newSt, now_y - 1, 0);
                    setVal4St(newSt, now_y, 0);

                    if (0 == newSt)
                    {
                        addSts(newSt, (sum + cells[now_x][now_y]), nAct);
                    }
                }
                else
                {
                    // 0 == left && 0 == up
                    // invalid
                }
            }
            else
            {
                if (left && up)
                {

                }
                else if (left || up)
                {
                    unsigned int val = left + up;

                    if (n > now_x)
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, val);
                        setVal4St(newSt, now_y, 0);

                        addSts(newSt, (sum + cells[now_x][now_y]), nAct);
                    }

                    if (3 > now_y)
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, now_y - 1, 0);
                        setVal4St(newSt, now_y, val);

                        addSts(newSt, (sum + cells[now_x][now_y]), nAct);
                    }
                }
                else
                {
                    // 0 == left && 0 == up
                    // do nothing
                    addSts(st, sum, nAct);

                    if (n > now_x && 3 > now_y)
                    {
                        unsigned int newSt = st;
                        setVal4St(newSt, now_y - 1, 1);
                        setVal4St(newSt, now_y, 2);

                        addSts(newSt, (sum + cells[now_x][now_y]), nAct);
                    }
                }
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
