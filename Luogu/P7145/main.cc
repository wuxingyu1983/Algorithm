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

unsigned int dp[65536][16][MAX_N];
unsigned char nums[65536][16];      // 每个 num 每个 s[i]
unsigned char flags[65536];         // 0 - 无效，1 - 有效

int n, k;

int main()
{
    cin >> n >> k;

    // init
    {
        unsigned int end = 1 << (1 << k);
        
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
        }
    }

    return 0;
}
