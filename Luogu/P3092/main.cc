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

class Item
{
public:
    unsigned short state;
    int remain;
    Item * prev, * next;

    Item() {}
};

Item dp[MAX_2K];
Item * head[MAX_K + 1];

int main()
{
    cin >> k >> n;

    for (size_t i = 0; i < k; i++)
    {
        cin >> coins[i];
    }

    for (size_t i = 0; i < n; i++)
    {
        cin >> costs[i];
    }

    // init
    for (size_t i = 1; i < (1 << k); i++)
    {
        dp[i].state = i;
    }

    head[0] = &(dp[0]);

    for (size_t iC = 0; iC < n; iC++)
    {
        for (int bits = k; bits >= 0; bits--)
        {
            if (head[bits])
            {
                for (Item * it = head[bits]; it != NULL; it = it->next)
                {
                    if (it->remain >= costs[iC])
                    {
                        // 还够用
                        it->remain -= costs[iC];
                    }
                    else
                    {
                        // 需要使用新的 coin


                        // 删除该 item
                        if (NULL == it->prev)
                        {
                            // first
                            head[bits] = it->next;
                            if (head[bits])
                            {
                                head[bits]->prev = NULL;
                            }
                        }
                        else
                        {
                            it->prev->next = it->next;
                            if (it->next)
                            {
                                it->next->prev = it->prev;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
