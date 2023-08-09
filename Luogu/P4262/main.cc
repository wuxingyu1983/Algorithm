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
#define QS_SIZE 135000
#define MOD 1000000007

class Record
{
public:
    int state; // 轮廓线状态
    long long total;
    long long sums[MAX_MN][MAX_MN];
    Record *next;

    Record() {}
};

#define getState(ST, POS) ((ST) >> ((POS)*BITS)) & MASK

#define setState(ST, POS, VAL)       \
    ST &= ~((MASK) << ((POS)*BITS)); \
    ST |= (VAL) << ((POS)*BITS);

int n, m;
unsigned char cells[MAX_MN][MAX_MN];
long long outs[MAX_MN][MAX_MN];

Record records[2 * QS_SIZE];
Record *qs[2][QS_SIZE];
int qTail[2];

Record *freeRecs = NULL;

int cnts[2][QS_SIZE]; // state 在队列 qs 中的 位置
int act = 0;          // 当前生效的 map

#define insertFunc(IDX, X, Y, ST, OLD)                 \
    {                                                  \
        int index = cnts[IDX][ST];                     \
        if (0 > index)                                 \
        {                                              \
            Record *rd = OLD;                          \
            cnts[IDX][ST] = qTail[IDX];                \
            qs[IDX][qTail[IDX]++] = rd;                \
        }                                              \
        else                                           \
        {                                              \
            Record *rd = qs[IDX][index];               \
            rd->total += OLD->total;                   \
            rd->total %= MOD;                          \
            for (size_t i = 1; i <= X; i++)            \
            {                                          \
                int end = m;                           \
                if (i == X)                            \
                {                                      \
                    end = Y;                           \
                }                                      \
                for (size_t j = 1; j <= end; j++)      \
                {                                      \
                    rd->sums[i][j] += OLD->sums[i][j]; \
                    rd->sums[i][j] %= MOD;             \
                }                                      \
            }                                          \
            OLD->next = freeRecs;                      \
            freeRecs = OLD;                            \
        }                                              \
    }

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
    memset(cnts[0], -1, QS_SIZE * sizeof(int));
    memset(cnts[1], -1, QS_SIZE * sizeof(int));

    int now_x = 0;
    int now_y = m;

    for (size_t i = 0; i < 2 * QS_SIZE; i++)
    {
        records[i].next = freeRecs;
        freeRecs = &(records[i]);
    }

    // get free record
    Record *rec = freeRecs;
    freeRecs = rec->next;

    rec->total = 1;
    qs[act][qTail[act]++] = rec;

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
                    rec = qs[act][iQ];
                    total += rec->total;

                    for (size_t i = 1; i <= n; i++)
                    {
                        for (size_t j = 1; j <= m; j++)
                        {
                            outs[i][j] += rec->sums[i][j];
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

        if ('1' == cells[now_x][now_y])
        {
            // 障碍物
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                rec = qs[act][iQ];
                if (NULL == rec)
                {
                    continue;
                }

                int state = rec->state;
                int up = 1;
                if (1 < now_x)
                {
                    up = getState(state, now_y - 1);
                }

                int st = state;
                int twinSt = state;

                setState(twinSt, now_y - 1, (1 - up));

                if (st != twinSt)
                {
                    int twinIdx = cnts[act][twinSt];
                    if (0 <= twinIdx)
                    {
                        Record *twinRec = qs[act][twinIdx];
                        if (twinRec)
                        {
                            rec->total += twinRec->total;
                            rec->total %= MOD;
                            for (size_t i = 1; i <= now_x; i++)
                            {
                                int end = m;
                                if (i == now_x)
                                {
                                    end = now_y;
                                }
                                for (size_t j = 1; j <= end; j++)
                                {
                                    rec->sums[i][j] += twinRec->sums[i][j];
                                    rec->sums[i][j] %= MOD;
                                }
                            }

                            // free twinRec
                            qs[act][twinIdx] = NULL;
                            twinRec->next = freeRecs;
                            freeRecs = twinRec;
                        }
                    }
                }

                setState(st, now_y - 1, 1);
                rec->state = st;

                insertFunc(nAct, now_x, now_y, st, rec);
            }
        }
        else
        {
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                rec = qs[act][iQ];
                if (NULL == rec)
                {
                    continue;
                }

                int state = rec->state;
                long long total = rec->total;

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

                    // get free record
                    Record *tmp = NULL;
                    tmp = freeRecs;
                    freeRecs = tmp->next;

                    memcpy(tmp, rec, sizeof(Record));
                    tmp->state = st;
                    tmp->sums[now_x][now_y - 1] += total;
                    tmp->sums[now_x][now_y] += total;

                    insertFunc(nAct, now_x, now_y, st, tmp);
                }

                if (0 == up)
                {
                    int st = state;
                    setState(st, now_y - 1, 1);

                    // get free record
                    Record *tmp = NULL;
                    tmp = freeRecs;
                    freeRecs = tmp->next;

                    memcpy(tmp, rec, sizeof(Record));
                    tmp->state = st;
                    tmp->sums[now_x - 1][now_y] += total;
                    tmp->sums[now_x][now_y] += total;

                    insertFunc(nAct, now_x, now_y, st, tmp);
                }

                {
                    // do nothing , 跳过
                    int st = state;

                    setState(st, now_y - 1, 0);
                    rec->state = st;

                    insertFunc(nAct, now_x, now_y, st, rec);
                }
            }
        }

        // 准备下一轮
        qTail[act] = 0;
        memset(cnts[act], -1, QS_SIZE * sizeof(int));
        act = nAct;
    }

    return 0;
}
