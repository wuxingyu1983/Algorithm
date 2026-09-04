// https://codeforces.com/contest/2144/problem/E2
// https://codeforces.com/contest/2144/problem/E1

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

const long long MOD = 998244353;
const int MAXN = 300000;

long long pw2[MAXN + 1];

int func(vector<int> &a, vector<long long> &out)
{
    int highest = 0;

    vector<int> lis;
    lis.push_back(a[0]);
    highest = a[0];
    for (int i = 1; i < a.size(); i++)
    {
        if (highest < a[i])
        {
            lis.push_back(a[i]);
            highest = a[i];
        }
    }

    vector<int> pos(lis.size(), -1);
    vector<int> cnt(lis.size(), 0);
    vector<long long> dp(lis.size(), 0);

    for (int i = 0; i < a.size(); i++)
    {
        int idx = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
        if (a[i] == lis[idx])
        {



            pos[idx] = i;
            cnt[idx]++;
        }
    }

    return highest;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    {
        pw2[0] = 1;
        for (int i = 1; i <= MAXN; i++)
        {
            pw2[i] = (pw2[i - 1] * 2) % MOD;
        }
    }

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<int> a, tmp;

        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            a.push_back(x);
            tmp.push_back(x);
        }

        // 去重
        sort(tmp.begin(), tmp.end());
        auto it = unique(tmp.begin(), tmp.end());
        tmp.erase(it, tmp.end());

        // vector a 序列化
        for (int i = 0; i < n; i++)
        {
            a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
        }

        vector<long long> out(n, 0);
        int highest = func(a, out);

        reverse(a.begin(), a.end());
        vector<long long> rout(n, 0);
        func(a, rout);


    }

    return 0;
}
