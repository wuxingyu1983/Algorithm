// https://codeforces.com/problemset/problem/919/B

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

int dp[11][10][11];

int func(int pos, int& k, int remain)
{
    int ret = 0;

    int sum = 0;
    for (size_t n = 0; n < 10; n++)
    {
        sum += dp[pos][n][remain];
        if (k <= sum)
        {
            ret = n;
            k -= sum - dp[pos][n][remain];
            break;
        }
    }

    return ret;
}

int main()
{
    int k;
    cin >> k;

    // init
    {
        int pos = 0;
        for (size_t n = 0; n < 10; n++)
        {
            dp[pos][n][n] = 1;
        }
       
        for (; pos < 10; pos++)
        {
            for (size_t n = 0; n < 10; n++)
            {
                for (size_t sum = 0; sum <= 10; sum++)
                {
                    if (dp[pos][n][sum])
                    {
                        for (size_t i = 0; i < 10; i++)
                        {
                            if (10 >= i + sum)
                            {
                                dp[pos + 1][i][i + sum] += dp[pos][n][sum];
                            }
                        }
                    }
                }
            }
        }
    }

    vector<int> ans;

    int remain = 10;
    for (int pos = 10; pos >= 0; pos--)
    {
        int n = func(pos, k, remain);
        if (0 < n || 0 < ans.size())
        {
            ans.push_back(n);
        }

        remain -= n;
    }

    for (size_t i = 0; i < ans.size(); i++)
    {
        cout << ans[i];
    }
    cout << endl;

    return 0;
}
