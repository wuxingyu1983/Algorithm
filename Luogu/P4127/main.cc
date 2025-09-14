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

int maxSum, maxLen;

int main()
{
    long long l, r;
    cin >> l >> r;

    l -= 1;
    
    string strL = to_string(l);
    string strR = to_string(r);

    if (19 == strR.length())
    {
        maxSum = 9 * 18 + 1;
    }
    else
    {
        maxSum = 9 * strR.length() + 1;
    }
    maxLen = strR.length();

    // dp[pos][0 - pos 位的数字和, 范围 0 - maxSum][val mod sum]
    long long ***dp;
    // init
    dp = new long long**[maxLen];
    for (size_t i = 0; i < maxLen; i++)
    {
        dp[i] = new long long * [maxSum];
        for (size_t j = 0; j < maxLen; j++)
        {
            dp[i][j] = new long long [maxSum];
            memset(dp[i][j], 0, sizeof(long long) * maxSum);
        }
    }
   
    long long cnt = 0;

    for (size_t sum = 1; sum < maxSum; sum++)
    {
        // pos = 0, init
        for (size_t n = 0; n <= 9 && n <= sum; n++)
        {
            dp[0][n][n % sum] ++;
        }
       
        long long tens = 10;
        for (size_t pos = 1; pos < maxLen; pos++)
        {
            // copy
            for (size_t s = 0; s <= sum; s++)
            {
                memcpy(dp[pos][s], dp[pos - 1][s], sizeof(long long) * maxSum);
            }
            
            for (size_t s = 0; s <= sum; s++)
            {
                for (size_t mod = 0; mod < sum; mod++)
                {
                    if (dp[pos - 1][s][mod])
                    {
                        for (size_t n = 1; n <= 9; n++)
                        {
                            int newS = s + n;
                            if (sum < newS)
                            {
                                break;
                            }
                            else
                            {
                                int newMod = (mod + tens * n) % sum;
                                dp[pos][newS][newMod] += dp[pos - 1][s][mod];
                            }
                        }
                    }
                }
            }
            
            tens *= 10;
        }


        
        
    }

    cout << cnt << endl;

    return 0;
}
