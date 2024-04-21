// https://www.luogu.com.cn/problem/P6883

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

#define MAX_N 20
#define MAX_K 20
#define MAX_NK 1048576

int n, k;
int cost[MAX_N][MAX_N];
int dp[MAX_NK];
vector<int> vec[MAX_N + 1];
char bits[MAX_NK];
int act;

int main()
{
    cin >> n >> k;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    // init
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 1; j <= i; j <<= 1)
        {
            if (j & i)
            {
                bits[i]++;
            }
        }

        vec[bits[i]].push_back(i);
    }

    memset(dp, -1, sizeof(dp));
    act = 0;
    dp[(1 << n) - 1] = 0;

    int ans = -1;

    if (k == n)
    {
        ans = 0;
    }
    else
    {
        for (size_t digit = n; digit > k; digit--)
        {
            for (vector<int>::iterator it = vec[digit].begin(); it != vec[digit].end(); it++)
            {
                int num = *it;

                for (size_t i = 0, fi = 1; fi <= num; i++, fi <<= 1)
                {
                    if (fi & num)
                    {
                        int mask = ~(1 << i);
                        int tmp = -1;
                        
                        for (size_t j = 0, fj = 1; fj <= num; j++, fj <<= 1)
                        {
                            if ((i != j) && (fj & num))
                            {
                                if (0 > tmp || tmp > cost[i][j])
                                {
                                    tmp = cost[i][j];
                                }
                            }
                        }

                        if (0 > dp[num & mask] || dp[num & mask] > (dp[num] + tmp))
                        {
                            dp[num & mask] = dp[num] + tmp;
                        }
                    }
                }
            }
        }

        for (vector<int>::iterator it = vec[k].begin(); it != vec[k].end(); it++)
        {
            if (0 <= dp[*it])
            {
                if (0 > ans || ans > dp[*it])
                {
                    ans = dp[*it];
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
