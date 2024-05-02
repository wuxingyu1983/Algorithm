// https://www.luogu.com.cn/problem/P3052
// 状压DP

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

#define MAX_N 18

int n, w;
int c[MAX_N];

class Item
{
public:
    int elevator;
    int remain;

    Item() {}
};

Item dp[262144];

int main()
{
    cin >> n >> w;

    for (size_t i = 0; i < n; i++)
    {
        cin >> c[i];
    }

    for (size_t st = 1; st < (1 << n); st++)
    {
        for (size_t pos = 0, j = 1; j <= st; pos++, j <<= 1)
        {
            if (st & j)
            {
                int subSt = st & (~j);
                int tmpEle = dp[subSt].elevator;
                int tmpRem = dp[subSt].remain;

                if (c[pos] > tmpRem)
                {
                    tmpEle++;
                    tmpRem = w - c[pos];
                }
                else
                {
                    tmpRem -= c[pos];
                }

                if (0 == dp[st].elevator || dp[st].elevator > tmpEle)
                {
                    dp[st].elevator = tmpEle;
                    dp[st].remain = tmpRem;
                }
                else if (dp[st].elevator == tmpEle && dp[st].remain < tmpRem)
                {
                    dp[st].remain = tmpRem;
                }
            }
        }
    }

    cout << dp[(1 << n) - 1].elevator << endl;

    return 0;
}
