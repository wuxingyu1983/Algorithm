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
char revcells[MAX_MN][MAX_MN];      // 反序的 cell
//long long outs[MAX_MN][MAX_MN];

unsigned int dp[MAX_MN][MAX_MN][262144];
unsigned int revdp[MAX_MN][MAX_MN][262144];

int revstate[262144];       // state 位反转

Record qs[2][QS_SIZE];
int qTail[2];
int cnts[2][QS_SIZE]; // state 在队列 qs 中的 位置
int act = 0;          // 当前生效的 map

#define insertFunc(IDX, X, Y, ST, SUM, DP) \
    {                                      \
        int index = cnts[IDX][ST];         \
        if (0 > index)                     \
        {                                  \
            index = qTail[IDX];            \
            qs[IDX][index].state = ST;     \
            qs[IDX][index].sum = SUM;      \
            cnts[IDX][ST] = index;         \
            qTail[IDX]++;                  \
        }                                  \
        else                               \
        {                                  \
            qs[IDX][index].sum += SUM;     \
            qs[IDX][index].sum %= MOD;     \
        }                                  \
        DP[X][Y][ST] += SUM;               \
        DP[X][Y][ST] %= MOD;               \
    }

inline unsigned int reverse(unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));

    return ((x >> 16) | (x << 16));
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
    for (unsigned int i = 1; i < 262144; i++)
    {
        if (0 == revstate[i])
        {
            unsigned int revi = reverse(i);
            revstate[i] = revi;
            revstate[revi] = i;
        }
    }

    memset(cnts[0], -1, QS_SIZE * sizeof(int));
    memset(cnts[1], -1, QS_SIZE * sizeof(int));

    int now_x = 0;
    int now_y = m;
    
    qs[act][qTail[act]++].sum = 1;

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

        if ('1' == cells[now_x][now_y])
        {
            // 障碍物
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned int state = qs[act][iQ].state;
                unsigned int sum = qs[act][iQ].sum;

                // do nothin
                insertFunc(nAct, now_x, now_y, state, sum, dp);
            }
        }
        else
        {
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {

            }
        }

        // 准备下一轮
        qTail[act] = 0;
        memset(cnts[act], -1, QS_SIZE * sizeof(int));
        act = nAct;
    }

    return 0;
}
