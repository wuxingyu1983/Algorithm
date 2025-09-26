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
#include <unordered_map>

using namespace std;

const int mod = 1000000007;
int dp[10][200001];

int main()
{
    int t;
    cin >> t;

    // init
    {
        for (int n = 0; n < 10; n++)
        {
            dp[n][0] = 1;
        }
        
        for (int i = 1; i <= 200000; i++)
        {
            for (int n = 0; n < 10; n++)
            {
                if (i < (10 - n))
                {
                    dp[n][i] = 1;
                }
                else
                {
                    dp[n][i] = dp[1][i - (10 - n)] + dp[0][i - (10 - n)];
                    dp[n][i] %= mod;
                }
            }
        }
    }

    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n >> m;

        int cnt = 0;
        string strNum = to_string(n);
        for (size_t idx = 0; idx < strNum.length(); idx++)
        {
            int digit = strNum.at(idx) - '0';
            cnt += dp[digit][m];
            cnt %= mod;
        }

        cout << cnt << endl;
    }
    
    return 0;
}
