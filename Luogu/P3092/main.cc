// https://www.luogu.com.cn/problem/P3092

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
#include <cstring>

using namespace std;

#define MAX_K   16 
#define MAX_N   100000
#define MAX_2K  65536

unsigned int k, n;
int coins[MAX_K];
int costs[MAX_N];
long long sum[MAX_N];

class Item
{
public:
    unsigned short state;
    int idx; // item in the [idx]th queue
    Item *prev, *next;

    Item()
    {
        idx = -1;
    }
};

Item dp[MAX_2K];
Item head[MAX_N + 1][MAX_K + 1];

int main()
{
    cin >> k >> n;

    for (size_t i = 0; i < k; i++)
    {
        scanf("%d", &(coins[i]));
    }

    for (size_t i = 0; i < n; i++)
    {
        scanf("%d", &(costs[i]));
        sum[i] = costs[i];
        if (0 < i)
        {
            sum[i] += sum[i - 1];
        }
    }

    // init
    for (size_t i = 1; i < (1 << k); i++)
    {
        dp[i].state = i;
    }

    dp[0].idx = 0;
    head[0][0].next = &(dp[0]);
    dp[0].prev = &(head[0][0]);

    for (size_t iC = 0; iC < n; iC++)
    {
        for (int bits = 0; bits <= k; bits++)
        {
            if (head[iC][bits].next)
            {
                for (Item * it = head[iC][bits].next; it != NULL; it = it->next)
                {
                    // 需要使用新的 coin
                    {
                        unsigned short st = it->state;

                        for (size_t p = 0; p < k; p++)
                        {
                            if (0 == (st & (1 << p)) && coins[p] >= costs[iC])
                            {
                                unsigned short newSt = st;
                                newSt |= (1 << p);

                                int tmp = coins[p];
                                if (0 < iC)
                                {
                                    tmp += sum[iC - 1];
                                }

                                int idx = n;

                                if (tmp < sum[n - 1])
                                {
                                    idx = upper_bound(sum, sum + n, tmp) - sum;
                                }

                                if (0 > dp[newSt].idx)
                                {
                                    // 还从未入队列
                                    dp[newSt].next = head[idx][bits + 1].next;
                                    if (head[idx][bits + 1].next)
                                    {
                                        head[idx][bits + 1].next->prev = &(dp[newSt]);
                                    }
                                    head[idx][bits + 1].next = &(dp[newSt]);
                                    dp[newSt].prev = &(head[idx][bits + 1]);

                                    dp[newSt].idx = idx;
                                }
                                else if (dp[newSt].idx < idx)
                                {
                                    // remove from old queue
                                    dp[newSt].prev->next = dp[newSt].next;
                                    if (dp[newSt].next)
                                    {
                                        dp[newSt].next->prev = dp[newSt].prev;
                                    }

                                    // add to new queue
                                    dp[newSt].next = head[idx][bits + 1].next;
                                    if (head[idx][bits + 1].next)
                                    {
                                        head[idx][bits + 1].next->prev = &(dp[newSt]);
                                    }
                                    head[idx][bits + 1].next = &(dp[newSt]);
                                    dp[newSt].prev = &(head[idx][bits + 1]);

                                    dp[newSt].idx = idx;
                                }
                                else
                                {
                                    // dp[newSt].idx >= idx
                                    // do nothing
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // final 计算
    long long ans = -1;

    for (int bits = k; bits > 0; bits--)
    {
        if (head[n][bits].next)
        {
            for (Item *it = head[n][bits].next; it != NULL; it = it->next)
            {
                unsigned short st = it->state;
                int tmp = 0;

                for (size_t p = 0; p < k; p++)
                {
                    if (0 == (st & (1 << p)))
                    {
                        tmp += coins[p];
                    }
                }

                if (ans < tmp)
                {
                    ans = tmp;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
