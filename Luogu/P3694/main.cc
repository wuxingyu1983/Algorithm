// https://www.luogu.com.cn/problem/P3694
// https://www.luogu.com.cn/article/8dbgzfzf

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

#define MAX_N 100001
#define MAX_M 21
#define MAX_2M 1048577

unsigned int n, m;
unsigned char idols[MAX_N];
int dp[MAX_2M];
int total[MAX_M];
int prefixSum[MAX_M][MAX_N];
int length[MAX_2M];

int main()
{
    cin >> n >> m;

    for (size_t i = 0; i < n; i++)
    {
        cin >> idols[i];
        idols[i] -= '0';
        total[idols[i]]++;

        if (0 < i)
        {
            for (size_t j = 1; j <= m; j++)
            {
                prefixSum[j][i] = prefixSum[j][i - 1];
            }
        }

        prefixSum[idols[i]][i] ++;
    }

    // init
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (size_t st = 1; st < (1 << m); st++)
    {
        for (size_t pos = 1, j = 1; j <= st; pos++, j <<= 1)
        {
            if (j & st)
            {
                length[st] += total[pos];
            }
        }
    }

    for (size_t st = 1; st < (1 << m); st++)
    {
        for (size_t pos = 1, j = 1; j <= st; pos++, j <<= 1)
        {
            if (st & j)
            {
                int subSt = st & (~j);
                int tmp = dp[subSt] + total[pos];
                if (0 < length[st])
                {
                    tmp -= prefixSum[pos][length[st] - 1];
                }
                if (0 < length[subSt])
                {
                    tmp += prefixSum[pos][length[subSt] - 1];
                }
                if (0 > dp[st] || dp[st] > tmp)
                {
                    dp[st] = tmp;
                }
            }
        }
    }

    cout << dp[(1 << m) - 1] << endl;

    return 0;
}
