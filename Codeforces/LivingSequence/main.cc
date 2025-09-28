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

long long dp[18][10];

int main()
{
    int t;
    cin >> t;

    // init
    {
        int idx = 0;
        for (int n = 0; n < 10; n++)
        {
            if (4 != n)
                dp[idx][n] = 1;
        }
        
        for (idx = 1; idx < 18; idx++)
        {
            for (int n = 0; n < 10; n++)
            {
                if (4 != n)
                {
                    for (int m = 0; m < 10; m++)
                    {
                        dp[idx][n] += dp[idx -1][m];
                    }
                }
            }
        }
    }

    for (size_t iT = 0; iT < t; iT++)
    {
        long long k;
        cin >> k;

        k ++;

        string res;

        for (int idx = 17; idx >= 0; idx--)
        {
            long long sum = 0;
            
            for (int m = 0; m < 10; m++)
            {
                if (sum + dp[idx][m] >= k)
                {
                    if (0 != m || 0 < res.length())
                    {
                        res += '0' + m;
                    }

                    k -= sum;

                    break;
                }

                sum += dp[idx][m];
            }
        }

        cout << res << endl;
    }

    return 0;
}
