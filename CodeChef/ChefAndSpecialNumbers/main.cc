// https://www.codechef.com/problems/WORKCHEF?tab=statement

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

long long powers[19];
unordered_multimap<int, int> mltmap;

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

void init(int k, int mod)
{
    
}

long long getCnt(long long num, int k, int mod)
{
    long long ret = 0;

    return ret;
}

int main()
{
    int q;
    cin >> q;

    // init
    {
        for (int n = 1; n < 1024; n++)
        {
            int l = 1;
            for (int idx = 0; idx < 10; idx++)
            {
                if (n & (1 << idx))
                {
                    l = l * idx / gcd(l, idx);
                }
            }

            mltmap.insert(make_pair<int, int>(__builtin_popcount(n), (int)l));
        }
    }

    for (int i = 0; i < q; i++)
    {
        long long l, r;
        int k;

        cin >> l >> r >> k;

        long long cntL = 0, cntR = 0;
        auto range = mltmap.equal_range(k);
        for (auto it = range.first; it != range.second; ++it)
        {
            init(k, it->second);

            cntL += getCnt(l - 1, k, it->second);
            cntR += getCnt(r, k, it->second);
        }

        if ((k & 1) && (k != 9))
        {
            range = mltmap.equal_range(9);
            for (auto it = range.first; it != range.second; ++it)
            {
                init(9, it->second);

                cntL += getCnt(l - 1, 9, it->second);
                cntR += getCnt(r, 9, it->second);
            }
        }

        cout << cntR - cntL << endl;
    }

    return 0;
}
