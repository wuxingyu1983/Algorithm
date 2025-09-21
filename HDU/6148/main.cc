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
                    dp[idx][2][n] += dp[idx - 1][1][m];
                }
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

        int type = 0; 
        int pre = -1;
        int len = strNum.length();

        if (1 == len)
        {
            cnt = strNum.at(0) - '0';
        }
        else
        {
            for (int idx = 0; idx < len; idx++)
            {
                int up = strNum.at(idx) - '0';

                if (0 == idx)
                {
                    // 0
                    cnt += sum[len - 2];

                    for (int n = 1; n < up; n++)
                    {
                        cnt += dp[len - 1 - idx][0][n];
                        cnt += dp[len - 1 - idx][1][n];
                        cnt += dp[len - 1 - idx][2][n];
                        cnt %= mod;
                    }
                }
                else
                {
                    if (1 == type && pre > up)
                    {
                        // invalid
                        break;
                    }

                    if (idx == len - 1)
                    {
                        up += 1;
                    }

                    if (0 == type)
                    {
                        for (int n = 0; n < up; n++)
                        {
                            if (pre < n)
                            {
                                cnt += dp[len - 1 - idx][0][n];
                                cnt += dp[len - 1 - idx][1][n];
                                cnt %= mod;
                            }
                            else
                            {
                                cnt += dp[len - 1 - idx][0][n];
                                cnt += dp[len - 1 - idx][1][n];
                                cnt += dp[len - 1 - idx][2][n];
                                cnt %= mod;
                            }
                        }

                        if (pre < up)
                        {
                            type = 1;
                        }
                        else if (pre > up)
                        {
                            type = 2;
                        }
                    }
                    else if (1 == type)
                    {
                        for (int n = pre; n < up; n++)
                        {
                            cnt += dp[len - 1 - idx][0][n];
                            cnt += dp[len - 1 - idx][1][n];
                            cnt %= mod;
                        }
                    }
                    else
                    {
                        // 2 == type
                        for (int n = 0; n < up; n++)
                        {
                            if (pre < n)
                            {
                                cnt += dp[len - 1 - idx][0][n];
                                cnt += dp[len - 1 - idx][1][n];
                                cnt %= mod;
                            }
                            else
                            {
                                cnt += dp[len - 1 - idx][0][n];
                                cnt += dp[len - 1 - idx][1][n];
                                cnt += dp[len - 1 - idx][2][n];
                                cnt %= mod;
                            }
                        }

                        if (pre < up)
                        {
                            type = 1;
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
