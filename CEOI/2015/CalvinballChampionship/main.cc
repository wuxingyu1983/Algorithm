// https://www.luogu.com.cn/problem/P4798

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

const int maxN = 10002;
const int mod = 1000007;

int maxT[maxN];
long long dp[maxN];

int main()
{
    int n;
    cin >> n;

    vector<int> tms;
    for (size_t i = 0; i < n; i++)
    {
        int t;
        cin >> t;

        tms.push_back(t);

        if (0 == i)
        {
            maxT[i] = t;
        }
        else
        {
            if (maxT[i - 1] < t)
            {
                maxT[i] = t;
            }
            else
            {
                maxT[i] = maxT[i - 1];
            }
        }
    }
   
    long long ans = 0;

    {
        int i = n - 1;

        for (size_t j = 1; j <= n; j++)
        {
            dp[j] = 1;
        }

        int num = tms[i];
        ans += num;
    }

    for (int i = n - 2; i >= 0; i--)
    {
        int num = tms[i];

        for (size_t j = 1; j <= n; j++)
        {
            dp[j] = j * dp[j] + dp[j + 1];
            dp[j] %= mod;
        }

        if (num > 1)
        {
            ans += (num - 1) * dp[maxT[i - 1]];
            ans %= mod;
        }
    }

    cout << ans << endl;

    return 0;
}
