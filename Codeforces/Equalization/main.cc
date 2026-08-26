// https://codeforces.com/problemset/problem/2075/D

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

using namespace std;

class Item
{
public:
    long long xSt, ySt;

    Item() {}
};

Item dp[65][65];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        long long x, y;
        cin >> x >> y;

        memset(dp, 0, sizeof(dp));

        if (x == y)
        {
            cout << 0 << "\n";
        }
        else
        {
            
        }
    }

    return 0;
}
