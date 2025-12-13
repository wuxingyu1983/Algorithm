// https://toph.co/p/noora-number

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

#pragma GCC target("popcnt")

int flag[1024];
long long dp[20][1024];

int main()
{
    int t;
    cin >> t;

    vector<string> vec;
    for (size_t i = 0; i < t; i++)
    {
        string str;
        cin >> str;

        vec.push_back(str);
    }
    
    // init
    {
        for (size_t n = 1; n < 1024; n++)
        {
            int max = 0;
            for (int i = 9; i >= 0; i--)
            {
                if (n & (1 << i))
                {
                    max = i;
                    break;
                }
            }

            if (__builtin_popcount(n) == max)
            {
                flag[n] = 1;
            }
        }

        int pos = 0;
        for (size_t i = 0; i < 10; i++)
        {
            dp[pos][1 << i] = 1;
        }
       
        for (; pos < 19; pos++)
        {
            for (size_t n = 1; n < 1024; n++)
            {
                if (dp[pos][n])
                {
                    for (size_t i = 0; i < 10; i++)
                    {
                        dp[pos + 1][n | (1 << i)] += dp[pos][n];
                    }
                }
            }
        }
    }

    return 0;
}
