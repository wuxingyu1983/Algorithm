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
#include <bitset>

using namespace std;

const int mod = 1000000007;
long long dp[100][3][10];
long long sum[100];

int main()
{
    int t;
    cin >> t;

    // init
    int idx = 0;
    for (int n = 0; n < 10; n++)
    {
        dp[idx][0][n] = 1;
    }
    sum[idx] = 9;

    for (idx = 1; idx < 100; idx++)
    {
        // type = 0
        for (int n = 0; n < 10; n++)
        {
            dp[idx][0][n] += dp[idx - 1][0][n];
            if (0 < n)
            {
                sum[idx] += dp[idx][0][n];
            }
        }

        // type = 1
        for (int n = 0; n < 10; n++)
        {
            for (int m = n; m < 10; m++)
            {
                if (m != n)
                {
                    dp[idx][1][n] += dp[idx - 1][0][m];
                }
                dp[idx][1][n] += dp[idx - 1][1][m];
            }

            dp[idx][1][n] %= mod;
            if (0 < n)
            {
                sum[idx] += dp[idx][1][n];
                sum[idx] %= mod;
            }
        }

        // type = 2
        for (int n = 1; n < 10; n++)
        {
            for (int m = 0; m <= n; m++)
            {
                if (n != m)
                {
                    dp[idx][2][n] += dp[idx - 1][0][m];
                }
                dp[idx][2][n] += dp[idx - 1][1][m];
                dp[idx][2][n] += dp[idx - 1][2][m];
            }

            dp[idx][2][n] %= mod;
            if (0 < n)
            {
                sum[idx] += dp[idx][2][n];
                sum[idx] %= mod;
            }
        }

        sum[idx] += sum[idx - 1];
        sum[idx] %= mod;
    }

    for (size_t i = 0; i < t; i++)
    {
        string strNum;
        cin >> strNum;

        long long cnt = 0;

        int type = -1;
        int pre = -1;
        int len = strNum.length();

        if (1 == len)
        {
            cnt = strNum.at(0) - '0';
        }
        else
        {
            for (int idx = 0; idx < len - 1; idx++)
            {
                int up = strNum.at(idx) - '0';

                if (0 == idx)
                {
                    // 0
                    cnt += sum[len - 2];

                    for (int n = 1; n < up; n++)
                    {
                        // type = 0
                        cnt += dp[len - 2][0][n];
                        cnt %= mod;

                        // type = 1
                        for (int m = n; m < 10; m++)
                        {
                            if (m != n)
                            {
                                cnt += dp[len - 2][0][m];
                            }
                            cnt += dp[len - 2][1][m];
                            cnt %= mod;
                        }

                        // type = 2
                        for (int m = 0; m <= n; m++)
                        {
                            if (m != n)
                            {
                                cnt += dp[len - 2][0][m];
                            }
                            cnt += dp[len - 2][1][m];
                            cnt += dp[len - 2][2][m];
                            cnt %= mod;
                        }
                    }
                }
                else if (1 == idx)
                {
                    for (int n = 0; n < up; n++)
                    {
                        if (n == pre)
                        {
                            // 3 种 type 都可以
                        }
                        else if (pre < n)
                        {
                            // type 0 和 1
                        }
                        else
                        {
                            // pre > n
                            // 3 种 type 都可以
                        }
                    }
                    
                }
                
                pre = up;
            }
        }

        cout << cnt << endl;
    }

    return 0;
}
