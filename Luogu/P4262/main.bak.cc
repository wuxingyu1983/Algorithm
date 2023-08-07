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

Record *cnts[2][QS_SIZE];
int act = 0; // 当前生效的 map

inline void insertFunc(int idx, int x, int y, int state, Record *old)
{
    Record * rec = cnts[idx][state];
    if (NULL == rec)
    {
        rec = old;
        qs[idx][qTail[idx]++] = rec;
        cnts[idx][state] = rec;
    }
    else
    {
        rec->total += old->total;
        rec->total %= MOD;
        for (size_t i = 1; i <= x; i++)
        {
            int end = m;
            if (i == x)
            {
                end = y;
            }
            for (size_t j = 1; j <= end; j++)
            {
                rec->sums[i][j] += old->sums[i][j];
                rec->sums[i][j] %= MOD;
            }
        }
        // free record
        old->next = freeRecs;
        freeRecs = old;
    }
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

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            rec = qs[act][iQ];
            int state = rec->state;
            long long total = rec->total;

            if ('1' == cells[now_x][now_y])
            {
                // 障碍物
                int st = state;
                setState(st, now_y - 1, 1);
                rec->state = st;

                insertFunc(nAct, now_x, now_y, st, rec);
            }
            else
            {
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
        memset(cnts[act], 0, QS_SIZE * 4);
        act = nAct;
    }

    return 0;
}
