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

void init()
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

int main()
{
    int q;
    cin >> q;

    init();

    

    return 0;
}
