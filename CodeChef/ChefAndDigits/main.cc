// https://www.codechef.com/problems/DGTCNT

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

long long dp[18][262144];
long long sum[18];

void initDP(int st, vector<int> &vec)
{

}

long long func(string strN, int st, vector<int> &vec)
{
    long long ret = 0;

    return ret;
}

int main()
{
    int t;
    cin >> t;

    for (size_t i = 0; i < t; i++)
    {
        long long l, r;
        cin >> l >> r;
        l --;

        vector<int> vecA;
        for (size_t n = 0; n < 10; n++)
        {
            int a;
            cin >> a;
            vecA.push_back(a);
        }

        string strL = to_string(l);
        string strR = to_string(r);
        long long cntL = 0, cntR = 0;
        for (int st = 1; st < 1024; st++)
        {
            initDP(st, vecA);

            if (1 & __builtin_popcount(st))
            {
                cntL += func(strL, st, vecA);
                cntR += func(strR, st, vecA);
            }
            else
            {
                cntL -= func(strL, st, vecA);
                cntR -= func(strR, st, vecA);
            }
        }

        cout << (r - cntL) - (l - cntL) << endl;
    }


    return 0;
}
