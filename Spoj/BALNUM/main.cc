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
int valid[1024];

long long func(long long num)
{
    long long ret = 0;

    return ret;
}

int main()
{
    // init
    {
        for (size_t mask = 1; mask < 1024; mask++)
        {
            for (size_t n = 0; n < 10; n++)
            {
                if (0 == (n & 1) && (mask & (1 << n)))
                {
                    valid[mask] |= 1 << n;
                }
            }
        }

        int pos = 0;
        for (size_t n = 0; n < 10; n++)
        {
            dp[pos][1 << n][1 << n] = 1;

            if (valid[1 << n] == (1 << n))
            {
                sum[pos] ++;
            }
        }
        
        for (; pos < 19; pos++)
        {
            for (size_t mask = 0; mask < 1024; mask++)
            {
                for (size_t cnt = 0; cnt < 1024; cnt++)
                {
                    if (dp[pos][mask][cnt])
                    {
                        for (size_t n = 0; n < 10; n++)
                        {
                            int newMask = mask | (1 << n);
                            int newCnt = cnt;

                            if (cnt & (1 << n))
                            {
                                // odd => even
                                newCnt &= ~(1 << n);
                            }
                            else
                            {
                                // even => odd
                                newCnt |= 1 << n;
                            }

                            dp[pos + 1][newMask][newCnt] += dp[pos][mask][cnt];

                            if (0 < n && valid[newMask] == newCnt)
                            {
                                sum[pos + 1] += dp[pos][mask][cnt];
                            }
                        }
                    }
                }
            }

            sum[pos + 1] += sum[pos];
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
