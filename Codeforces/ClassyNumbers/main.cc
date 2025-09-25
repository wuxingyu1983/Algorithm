// https://codeforces.com/problemset/problem/1036/C

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

long long func(long long n)
{
    long long ret = 0;

    return ret;
}

int main()
{
    int t;
    cin >> t;

    for (size_t iT = 0; iT < t; iT++)
    {
        long long l, r;
        cin >> l >> r;

        cout << func(r) - func(l - 1) << endl;
    }

    return 0;
}
