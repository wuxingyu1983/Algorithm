// https://www.spoj.com/problems/BALNUM/

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

long long dp[20][1024][1024];   // dp[pos][mask][cnt]
long long sum[20];

long long func(long long num)
{
    long long ret = 0;

    return ret;
}

int main()
{
    // init
    {
        int pos = 0;
        for (size_t n = 0; n < 10; n++)
        {
            dp[pos][1 << n][1 << n] = 1;
        }
        
        for (; pos < 19; pos++)
        {
            for (size_t mask = 0; mask < 1024; mask++)
            {
                for (size_t cnt = 0; cnt < 1024; cnt++)
                {
                    if (dp[pos][mask][cnt])
                    {
                        
                    }
                }
            }
        }
    }

    int t;
    cin >> t;

    for (size_t i = 0; i < t; i++)
    {
        long long l, r;
        cin >> l >> r;

        cout << func(r) - func(l - 1) << endl;
    }

    return 0;
}
