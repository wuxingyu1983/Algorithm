// https://cses.fi/problemset/task/2137

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
#include <bitset>

using namespace std;

const int maxN = 3001;

#pragma GCC optimize ("O2")
#pragma GCC target("popcnt")

bitset<maxN> lines[maxN];

int main()
{
    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        cin >> lines[i];
    }
    
    long long ans = 0;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            bitset<maxN> tmp = lines[i] & lines[j];
            long long cnt = tmp.count();
            ans += cnt * (cnt - 1) / 2;
        }
    }

    cout << ans << endl;

    return 0;
}
