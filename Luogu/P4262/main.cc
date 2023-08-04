// https://www.luogu.com.cn/problem/P4262

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
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
#define QS_SIZE 132000
#define MOD 1000000007

class Record
{
public:
    int state; // 轮廓线状态
    long long total;
    long long sums[MAX_MN][MAX_MN];

    Record() {}
};

#define getState(ST, POS) ((ST) >> ((POS)*BITS)) & MASK

#define setState(ST, POS, VAL)       \
    ST &= ~((MASK) << ((POS)*BITS)); \
    ST |= (VAL) << ((POS)*BITS);

#define insertState(IDX, X, Y, ST, OLD, NOWID)                     \
    {                                                              \
        unordered_map<int, int>::iterator it = cnts[IDX].find(ST); \
        if (it == cnts[IDX].end())                                 \
        {                                                          \
            NOWID = qTail[IDX];                                    \
            qs[IDX][NOWID].state = ST;                             \
            qs[IDX][NOWID].total = OLD.total;                      \
            for (size_t i = 1; i <= X; i++)                        \
            {                                                      \
                int end = m;                                       \
                if (i == X)                                        \
                {                                                  \
                    end = Y;                                       \
                }                                                  \
                for (size_t j = 1; j <= end; j++)                  \
                {                                                  \
                    qs[IDX][NOWID].sums[i][j] = OLD.sums[i][j];    \
                }                                                  \
            }                                                      \
            qTail[IDX]++;                                          \
            cnts[IDX][ST] = NOWID;                                 \
        }                                                          \
        else                                                       \
        {                                                          \
            NOWID = it->second;                                    \
            qs[IDX][NOWID].total += OLD.total;                     \
            qs[IDX][NOWID].total %= MOD;                           \
            for (size_t i = 1; i <= X; i++)                        \
            {                                                      \
                int end = m;                                       \
                if (i == X)                                        \
                {                                                  \
                    end = Y;                                       \
                }                                                  \
                for (size_t j = 1; j <= end; j++)                  \
                {                                                  \
                    qs[IDX][NOWID].sums[i][j] += OLD.sums[i][j];   \
                    qs[IDX][NOWID].sums[i][j] %= MOD;              \
                }                                                  \
            }                                                      \
        }                                                          \
    }

int n, m;
unsigned char cells[MAX_MN][MAX_MN];
long long outs[MAX_MN][MAX_MN];

Record qs[2][QS_SIZE];
int qTail[2];

unordered_map<int, int> cnts[2];
int act = 0; // 当前生效的 map

int main()
{
    cin >> n >> m;

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            cin >> cells[i][j];
        }
    }

    // init
    int now_x = 0;
    int now_y = m;

    qs[act][0].total = 1;
    qTail[act]++;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;
        if (m == now_y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                long long total = 0;

                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    total += qs[act][iQ].total;

                    for (size_t i = 1; i <= n; i++)
                    {
                        for (size_t j = 1; j <= m; j++)
                        {
                            outs[i][j] += qs[act][iQ].sums[i][j];
                        }
                    }
                }

                total %= MOD;

                for (size_t i = 1; i <= n; i++)
                {
                    if ('1' == cells[i][1])
                    {
                        printf("0");
                    }
                    else
                    {
                        printf("%lld", (MOD + total - (outs[i][1] % MOD)) % MOD);
                    }
                    for (size_t j = 2; j <= m; j++)
                    {
                        if ('1' == cells[i][j])
                        {
                            printf(" 0");
                        }
                        else
                        {
                            printf(" %lld", (MOD + total - (outs[i][j] % MOD)) % MOD);
                        }
                    }
                    printf("\n");
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
            int state = qs[act][iQ].state;
            long long total = qs[act][iQ].total;

            if ('1' == cells[now_x][now_y])
            {
                // 障碍物
                int st = state;
                setState(st, now_y - 1, 1);

                int id = 0;
                insertState(nAct, now_x, now_y, st, qs[act][iQ], id);
            }
            else
            {
                {
                    // do nothing , 跳过
                    int st = state;
                    setState(st, now_y - 1, 0);

                    int id = 0;
                    insertState(nAct, now_x, now_y, st, qs[act][iQ], id);
                }

                int left = 1, up = 1;
                if (1 < now_y)
                {
                    left = getState(state, now_y - 2);
                }
                if (1 < now_x)
                {
                    up = getState(state, now_y - 1);
                }

                if (0 == left)
                {
                    int st = state;
                    setState(st, now_y - 2, 1);
                    setState(st, now_y - 1, 1);

                    int id = 0;
                    insertState(nAct, now_x, now_y, st, qs[act][iQ], id);

                    qs[nAct][id].sums[now_x][now_y - 1] += total;
                    qs[nAct][id].sums[now_x][now_y - 1] %= MOD;
                    qs[nAct][id].sums[now_x][now_y] += total;
                    qs[nAct][id].sums[now_x][now_y] %= MOD;
                }

                if (0 == up)
                {
                    int st = state;
                    setState(st, now_y - 1, 1);

                    int id = 0;
                    insertState(nAct, now_x, now_y, st, qs[act][iQ], id);

                    qs[nAct][id].sums[now_x - 1][now_y] += total;
                    qs[nAct][id].sums[now_x - 1][now_y] %= MOD;
                    qs[nAct][id].sums[now_x][now_y] += total;
                    qs[nAct][id].sums[now_x][now_y] %= MOD;
                }
            }
        }

        // 准备下一轮
        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
