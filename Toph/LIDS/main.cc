// https://toph.co/p/lids

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

long long dp[11][11][10];           // dp[pos][num][len]
long long surfix[11][11][10];       // surfix[pos][num][len]
long long sum[11][10];              // sum[pos][len]

void func(long long n, vector<long long> &vec)
{
    string strN = to_string(n);
    int len = strN.length();

    long long pre[10][10]; // pre[num][len]
    memset(pre, 0, sizeof(pre));

    for (int pos = 0; pos < len; pos++)
    {
        int d = strN.at(pos) - '0';
        int down = 0, up = d - 1;
        
        if (0 == pos)
        {
            down = 1;

            if (1 < len)
            {
                for (int n = 0; n < 10; n++)
                {
                    for (int l = 0; l < 10; l++)
                    {
                        if (dp[len - 2][n][l])
                        {
                            vec[l] += dp[len - 2][n][l];
                        }
                    }
                }
            }
        }

        if (len - 1 == pos)
        {
            up = d;
        }

        if (0 == pos && len - 1 == pos)
        {
            for (int n = down; n <= up; n++)
            {
                vec[1] ++;
            }
        }
        else if (0 == pos)
        {
            for (int n = down; n <= up; n++)
            {
                for (int aftN = n + 1; aftN < 10; aftN++)
                {
                    for (int aftL = 1; aftL < 10; aftL++)
                    {
                        if (dp[len - 2 - pos][aftN][aftL])
                        {
                            vec[1 + aftL] += dp[len - 2 - pos][aftN][aftL];
                        }
                    }
                }
            }
        }
        else if (len - 1 == pos)
        {
            for (int n = down; n <= up; n++)
            {
                for (int preN = 1; preN < n; preN++)
                {
                    for (int preL = 1; preL < pos; preL++)
                    {
                        if (pre[preN][preL])
                        {
                            vec[preL + 1] += pre[preN][preL];
                        }
                    }
                }
            }
        }
        else
        {
            for (int n = down; n <= up; n++)
            {
                for (int preN = 1; preN < n; preN++)
                {
                    for (int preL = 1; preL < pos; preL++)
                    {
                        if (pre[preN][preL])
                        {
                            for (int aftN = n + 1; aftN < 10; aftN++)
                            {
                                for (int aftL = 1; aftL < 10; aftL++)
                                {
                                    if (dp[len - 2 - pos][aftN][aftL])
                                    {
                                        vec[preL + 1 + aftL] += pre[preN][preL] * dp[len - 2 - pos][aftN][aftL];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // update pre
        {
            pre[d][1] += 1;
            for (int n = 1; n < d; n++)
            {
                for (int l = 10; l >= 0; l--)
                {
                    if (pre[n][l])
                    {
                        pre[d][l + 1] += pre[n][l];
                    }
                }
            }
            
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    {
        int pos = 0;
        for (int n = 0; n < 10; n++)
        {
            dp[pos][n][1] = 1;
        }
        surfix[pos][9][1] = 1;
        for (int n = 8; n >= 0; n--)
        {
            surfix[pos][n][1] += surfix[pos][n + 1][1];
        }
        
       
        for (pos = 1; pos < 11; pos++)
        {
            for (int n = 0; n < 10; n++)
            {
                int len = 1;
                dp[pos][n][len] = (long long)pow(n + 1, pos);

                for (len = 2; len < 10; len++)
                {
                    for (int i = pos - 1; i >= 0; i--)
                    {
                        dp[pos][n][len] += surfix[i][n + 1][len - 1] * (long long)pow(n + 1, pos - i - 1);
                    }
                }
            }

            for (int len = 1; len < 10; len++)
            {
                surfix[pos][9][len] = dp[pos][9][len];
            }
            for (int n = 8; n >= 0; n--)
            {
                for (int len = 1; len < 10; len++)
                {
                    surfix[pos][n][len] = surfix[pos][n + 1][len] + dp[pos][n][len];
                }
            }
        }

        sum[0][1] = 10;
        for (int pos = 1; pos < 11; pos++)
        {
            for (int len = 1; len < 10; len++)
            {
                sum[pos][len] = sum[pos - 1][len] + surfix[pos][1][len];
            }
        }
    }

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++)
    {
        long long x, y;
        cin >> x >> y;

        vector<long long> vecX(10, 0);
        vector<long long> vecY(10, 0);
        func(x - 1, vecX);
        func(y, vecY);

        for (int l = 9; l > 0; l--)
        {
            long long cnt = vecY[l] - vecX[l];
            if (0 < cnt)
            {
                printf("Case %d: %d %lld\n", i, l, cnt);
                break;
            }
        }
    }

    return 0;
}
