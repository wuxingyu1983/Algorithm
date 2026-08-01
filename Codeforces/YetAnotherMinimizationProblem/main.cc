// https://codeforces.com/contest/1637/problem/D

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

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int iT = 0; iT < t; iT++)
    {
        int n;
        cin >> n;

        vector<int> a, b;

        for (int iN = 0; iN < n; iN++)
        {
            int x;
            cin >> x;
            a.push_back(x);
        }
        
        for (int iN = 0; iN < n; iN++)
        {
            int x;
            cin >> x;
            b.push_back(x);
        }

        long long ans = 0;

        if (1 == n)
        {
        }
        else if (2 == n)
        {
            ans = max((a[0] + a[1]) * (a[0] + a[1]) + (b[0] + b[1]) * (b[0] + b[1]), (a[0] + b[1]) * (a[0] + b[1]) + (b[0] + a[1]) * (b[0] + a[1]));
        }
        else
        {

        }

        cout << ans << "\n";
    }

    return 0;
}
