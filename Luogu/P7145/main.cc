// https://www.luogu.com.cn/problem/P7145

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
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
#define MAX_K 4
#define MAX_N 500
#define MOD 998244353

unsigned int dp[65536][MAX_N][16];
unsigned char nums[65536][16]; // 每个 num 每个 s[i]
unsigned char flags[65536];    // 0 - 无效，1 - 有效
unsigned char newNum0[16];     // 添加 0 得出的新的 num
unsigned char newNum1[16];     // 添加 1 得出的新的 num

int n, k;

int main()
{
    cin >> n >> k;

    unsigned int ans = 0;
    unsigned int end = 1 << (1 << k);

    // init
    {
        for (size_t i = 0; i < end; i++)
        {
            unsigned int num = i;

            for (int j = (1 << k) - 1; j >= 0; j--)
            {
                if (num & 1)
                {
                    nums[i][j] = 1;
                }

                num >>= 1;
            }
        }

        memset(flags, 1, sizeof(flags));
        unsigned int mask = (1 << k) - 1;

        for (size_t i = 0; i < end; i++)
        {
            unsigned int num = i;

            for (int j = (1 << k) - k; j >= 0; j--)
            {
                if (0 == nums[i][num & mask])
                {
                    // 非法
                    flags[i] = 0;
                    break;
                }

                num >>= 1;
            }

            if (1 == flags[i])
            {
                dp[i][1 << k][i & mask] = 1;
                if (n == (1 << k))
                {
                    ans++;
                }
            }
        }

        for (size_t i = 0; i < (1 << k); i++)
        {
            newNum0[i] = (i << 1) & mask;
            newNum1[i] = ((i << 1) & mask) + 1;
        }
    }

    for (size_t i = 0; i < end; i++)
    {
        if (1 == flags[i])
        {
            for (size_t iN = 1 << k; iN < n; iN++)
            {
                for (size_t j = 0; j < (1 << k); j++)
                {
                    if (dp[i][iN][j])
                    {
                        // 新增 0
                        if (1 == nums[i][newNum0[j]])
                        {
                            dp[i][iN + 1][newNum0[j]] += dp[i][iN][j];
                            dp[i][iN + 1][newNum0[j]] %= MOD;

                            if (n == iN + 1)
                            {
                                ans += dp[i][iN][j];
                                ans %= MOD;
                            }
                        }

                        // 新增 1
                        if (1 == nums[i][newNum1[j]])
                        {
                            dp[i][iN + 1][newNum1[j]] += dp[i][iN][j];
                            dp[i][iN + 1][newNum1[j]] %= MOD;

                            if (n == iN + 1)
                            {
                                ans += dp[i][iN][j];
                                ans %= MOD;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
