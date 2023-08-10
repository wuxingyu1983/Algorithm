// https://www.luogu.com.cn/problem/P4262

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
#define MAX_MN 18
#define BITS 1
#define MASK 1
#define QS_SIZE 263000
#define MOD 1000000007

class Record
{
public:
    unsigned int state; // 轮廓线状态
    unsigned int sum;

    Record() {}
};

#define getState(ST, POS) ((ST) >> ((POS)*BITS)) & MASK

#define setState(ST, POS, VAL)       \
    ST &= ~((MASK) << ((POS)*BITS)); \
    ST |= (VAL) << ((POS)*BITS);

int n, m;
char cells[MAX_MN][MAX_MN];
char revcells[MAX_MN][MAX_MN]; // 反序的 cell
// long long outs[MAX_MN][MAX_MN];

unsigned int dp[MAX_MN][MAX_MN][262144];
unsigned int revdp[MAX_MN][MAX_MN][262144];

int revstate[262144]; // state 位反转

Record qs[2][QS_SIZE];
int qTail[2];
int cnts[2][QS_SIZE]; // state 在队列 qs 中的 位置
int act = 0;          // 当前生效的 map

#define insertFunc(IDX, X, Y, ST, SUM, FLAG, DP) \
    {                                            \
        int index = cnts[IDX][ST];               \
        if (0 > index)                           \
        {                                        \
            index = qTail[IDX];                  \
            qs[IDX][index].state = ST;           \
            qs[IDX][index].sum = SUM;            \
            cnts[IDX][ST] = index;               \
            qTail[IDX]++;                        \
        }                                        \
        else                                     \
        {                                        \
            qs[IDX][index].sum += SUM;           \
            qs[IDX][index].sum %= MOD;           \
        }                                        \
        if (FLAG)                                \
        {                                        \
            DP[X][Y][ST] += SUM;                 \
            DP[X][Y][ST] %= MOD;                 \
        }                                        \
    }

inline unsigned int reverse(unsigned int x, int m)
{
    unsigned int ret = 0;
    unsigned int flag = 1;
    unsigned int revflag = 1 << m;

    for (int i = 0; i <= m; i++, flag <<= 1, revflag >>= 1)
    {
        if (x & flag)
        {
            ret |= revflag;
        }
    }

    return ret;
}

void func(char carr[][MAX_MN], unsigned int dparr[][MAX_MN][262144])
{
    memset(cnts[0], -1, QS_SIZE * sizeof(int));
    memset(cnts[1], -1, QS_SIZE * sizeof(int));

    int now_x = 0;
    int now_y = m;

    act = 0;
    qs[act][0].state = 0;
    qs[act][0].sum = 1;
    qTail[act] = 1;
    qTail[1] = 0;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;
        if (m == now_y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                break;
            }
        }
        else
        {
            now_y++;
        }

        if ('1' == carr[now_x][now_y])
        {
            // 障碍物
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned int state = qs[act][iQ].state;
                unsigned int sum = qs[act][iQ].sum;

                if (1 == now_y)
                {
                    state <<= BITS;
                }

                // do nothing
                insertFunc(nAct, now_x, now_y, state, sum, false, dparr);
            }
        }
        else
        {
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned int state = qs[act][iQ].state;
                unsigned int sum = qs[act][iQ].sum;

                if (1 == now_y)
                {
                    state <<= BITS;
                }

                int left = getState(state, (now_y - 1));
                int up = getState(state, now_y);

                if (0 == left && 0 == up)
                {
                    // 跳过该cell
                    insertFunc(nAct, now_x, now_y, state, sum, true, dparr);

                    if (n > now_x && '1' != carr[now_x + 1][now_y])
                    {
                        // 下插头
                        unsigned int st = state;
                        setState(st, (now_y - 1), 1);

                        insertFunc(nAct, now_x, now_y, st, sum, false, dparr);
                    }

                    if (m > now_y && '1' != carr[now_x][now_y + 1])
                    {
                        int rightUp = getState(state, now_y + 1);
                        if (0 == rightUp)
                        {
                            // 右插头
                            unsigned int st = state;
                            setState(st, now_y, 1);

                            insertFunc(nAct, now_x, now_y, st, sum, false, dparr);
                        }
                    }
                }
                else if (0 < left && 0 < up)
                {
                    // 非法
                    continue;
                }
                else
                {
                    // 封住该插头
                    unsigned int st = state;
                    setState(st, (now_y - 1), 0);
                    setState(st, now_y, 0);

                    insertFunc(nAct, now_x, now_y, st, sum, false, dparr);
                }
            }
        }

        // 准备下一轮
        qTail[act] = 0;
        memset(cnts[act], -1, QS_SIZE * sizeof(int));
        act = nAct;
    }
}

int main()
{
    cin >> n >> m;

    char ch;
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            cin >> ch;
            cells[i][j] = ch;
            revcells[n + 1 - i][m + 1 - j] = ch;
        }
    }

    // init
    // 初始化 revstate
    for (unsigned int i = 1; i < (1 << (m + 1)); i++)
    {
        if (0 == revstate[i])
        {
            unsigned int revi = reverse(i, m);
            revstate[i] = revi;
            revstate[revi] = i;
        }
    }

    func(cells, dp);
    func(revcells, revdp);

    unsigned int maxst = (1 << (m + 1)) - 1;
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            unsigned long long total = 0;

            if ('1' != cells[i][j])
            {
                for (unsigned int st = 0; st <= maxst; st++)
                {
                    long long s = 0;
                    if (s = dp[i][j][st])
                    {
                        unsigned int revst = revstate[st];
                        long long revs = 0;
                        if (revs = revdp[n + 1 - i][m + 1 - j][revst])
                        {
                            total += s * revs;
                            total %= MOD;
                        }
                    }
                }
            }

            if (1 == j)
            {
                printf("%llu", total);
            }
            else
            {
                printf(" %llu", total);
            }
        }
        printf("\n");
    }

    return 0;
}
