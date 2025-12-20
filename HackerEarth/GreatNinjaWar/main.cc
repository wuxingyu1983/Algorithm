// https://www.hackerearth.com/zh/problem/algorithm/sallu-bhai-and-ias-8838ac8d/?purpose=login&source=problem-page&update=google

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

int lcm[48] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};
multimap<int, int> mltmap;
long long dp[13][1024][2520];

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

void init()
{
    for (int n = 1023; n > 0; n--)
    {
        int l = 1;
        for (int idx = 1; idx < 10; idx++)
        {
            if (n & (1 << idx))
            {
                l = l * idx / gcd(l, idx);
            }
        }

        mltmap.insert(make_pair<int, int>((int)l, (int)n));
    }
}


int main()
{
    int q;
    cin >> q;

    vector<long long> ls, rs;

    for (size_t i = 0; i < q; i++)
    {
        long long l, r;
        cin >> l >> r;

        ls.push_back(l);
        rs.push_back(r);
    }

    init();

    vector<long long> ans(q, 0);



    return 0;
}
