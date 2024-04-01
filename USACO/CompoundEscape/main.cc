// https://usaco.org/index.php?page=viewproblem2&cpid=949&lang=zh
// https://hydro.ac/d/loj/p/P3769

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
#define MAX_H   30001
#define MAX_W   7
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 6000000
#define MOD 1000000007

class Record
{
public:
    unsigned int state; // 轮廓线段状态

    unsigned long long sum;
    unsigned long long count;
    unsigned char minUnused;

    Record() {}
};

unsigned long long rowGate[MAX_H][MAX_W];
unsigned long long colGate[MAX_W][MAX_H];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

// 最小表示法重编码
#define recode(ST, UNUSED)             \
    int bb[10];                        \
    memset(bb, -1, sizeof(bb));        \
    int bn = 1;                        \
    bb[0] = 0;                         \
    for (int i = 0; i <= w; i++)       \
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

#define addSts(ST, SUM, CNT, IDX)                                                       \
    unsigned char unused;                                                               \
    unsigned int recodedSt = ST;                                                        \
    recode(recodedSt, unused);                                                          \
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX].find(recodedSt); \
    if (it == cnts[IDX].end())                                                          \
    {                                                                                   \
        int pInQ = qTail[IDX];                                                          \
        qs[IDX][pInQ].state = recodedSt;                                                \
        qs[IDX][pInQ].sum = SUM;                                                        \
        qs[IDX][pInQ].count = CNT;                                                      \
        qs[IDX][pInQ].minUnused = unused;                                               \
        cnts[IDX][recodedSt] = pInQ;                                                    \
        qTail[IDX]++;                                                                   \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        if (qs[IDX][it->second].sum > SUM)                                              \
        {                                                                               \
            qs[IDX][it->second].sum = SUM;                                              \
            qs[IDX][it->second].count = CNT;                                            \
        }                                                                               \
        else if (qs[IDX][it->second].sum == SUM)                                        \
        {                                                                               \
            qs[IDX][it->second].count += CNT;                                           \
            qs[IDX][it->second].count %= MOD;                                           \
        }                                                                               \
    }

int main()
{
    cin >> h >> w;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col < w; col++)
        {
            cin >> rowGate[row][col];
        }
    }

    for (size_t col = 1; col <= w; col++)
    {
        for (size_t row = 1; row < h; row++)
        {
            cin >> colGate[col][row];
        }
    }

    // init
    act = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].sum = 0;
    qs[act][0].count = 1;
    qs[act][0].minUnused = 1;

    qTail[act]++;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;

        if (w == now_y)
        {
            now_x++;
            now_y = 1;

            if (h < now_x)
            {
                // TBD
                if (1 == qTail[act] && 0 == qs[act][0].state)
                {
                    cout << qs[act][0].count << endl;
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
            unsigned long long sum = qs[act][iQ].sum;
            unsigned long long cnt = qs[act][iQ].count;
            unsigned char newVal = qs[act][iQ].minUnused;

            if (1 == now_y)
            {
                st <<= ST_BITS;
            }

            unsigned int left = getVal4St(st, now_y - 1);
            unsigned int up = getVal4St(st, now_y);

            if (left && up)
            {
                // 就此打住
                // up ==> left
                for (int i = 0; i <= w; i++)
                {
                    int tmp = getVal4St(st, i);
                    if (tmp == up)
                    {
                        setVal4St(st, i, left);
                    }
                }

                setVal4St(st, now_y - 1, 0);
                setVal4St(st, now_y, 0);

                bool flag = false;
                if (h == now_x && w == now_y)
                {
                    // last cell
                    flag = true;
                }
                else
                {
                    for (int i = 0; i <= w; i++)
                    {
                        int tmp = getVal4St(st, i);
                        if (tmp == left)
                        {
                            flag = true;
                            break;
                        }
                    }
                }

                if (flag)
                {
                    addSts(st, sum, cnt, nAct);
                }

                newVal = left;
            }
            else if (left || up)
            {
                // 就此打住
                unsigned int val = left + up;

                setVal4St(st, now_y - 1, 0);
                setVal4St(st, now_y, 0);

                bool flag = false;
                if (h == now_x && w == now_y)
                {
                    // last cell
                    flag = true;
                }
                else
                {
                    for (int i = 0; i <= w; i++)
                    {
                        int tmp = getVal4St(st, i);
                        if (tmp == val)
                        {
                            flag = true;
                            break;
                        }
                    }
                }

                if (flag)
                {
                    addSts(st, sum, cnt, nAct);
                }

                newVal = val;
            }
            else
            {
                // 0 == left && 0 == up
                // 不能就此打住
            }

            // 扩展到其他 cell
            if (h > now_x)
            {
                unsigned int newSt = st;

                setVal4St(newSt, now_y - 1, newVal);

                addSts(newSt, (sum + colGate[now_y][now_x]), cnt, nAct);
            }

            if (w > now_y)
            {
                unsigned int newSt = st;

                setVal4St(newSt, now_y, newVal);

                addSts(newSt, (sum + rowGate[now_x][now_y]), cnt, nAct);
            }

            if (h > now_x && w > now_y)
            {
                unsigned int newSt = st;

                setVal4St(newSt, now_y - 1, newVal);
                setVal4St(newSt, now_y, newVal);

                addSts(newSt, (sum + colGate[now_y][now_x] + rowGate[now_x][now_y]), cnt, nAct);
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
