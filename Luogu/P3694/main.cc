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
int length[1048577];

int main()
{
    cin >> n >> m;

    for (size_t i = 0; i < n; i++)
    {
        cin >> idols[i];
        total[idols[i]] ++;

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

    }

    return 0;
}
