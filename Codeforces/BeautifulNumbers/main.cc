// https://codeforces.com/problemset/problem/55/D

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

vector<int> subsets[512];
int lcm[512];
int num[48] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};

long long dp[19][512][2520];

int gcd(int a, int b)
{
	if (a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}

void init()
{
    for (int n = 1; n < 512; n++)
    {
        int l = 1;
        for (int idx = 0; idx < 10; idx++)
        {
            if (n & (1 << idx))
            {
                l = l * (idx + 1) / gcd(l, idx + 1);
            }
        }

        lcm[n] = l;

        for (int m = 1; m <= n; m++)
        {
            if (m == (m & n))
            {
                subsets[n].push_back(m);
            }
        }
    }
}

void initDP(int st)
{

}

long long func(long long num, int st)
{
    long long ret = 0;

    return ret;
}

int main()
{
    init();

    int t;
    cin >> t;

    vector<long long> ls, rs;

    for (size_t i = 0; i < t; i++)
    {
        long long l, r;
        cin >> l >> r;

        ls.push_back(l);
        rs.push_back(r);
    }

    vector<long long> cnts(t, 0);
    for (int st = 1; st < 512; st++)
    {
        initDP(st);

        for (size_t i = 0; i < t; i++)
        {
            cnts[i] += func(rs[i], st) - func(ls[i] - 1, st);
        }
    }

    for (size_t i = 0; i < t; i++)
    {
        cout << cnts[i] << endl;
    }

    return 0;
}
