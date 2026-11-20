// https://codeforces.com/problemset/problem/1839/E

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
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

const int MAXN = 303;

vector<bitset<MAXN>> dp(MAXN, bitset<MAXN>());

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    multiset<int> sAll;
    int sum = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];

        sAll.insert(a[i]);
    }

    int winner = 1;
    if (0 == (sum & 1))
    {
        int half = sum >> 1;

        dp[0][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            dp[i] = dp[i - 1] | (dp[i - 1] << a[i]);
        }

        if (dp[n][half])
        {
            winner = 2;
        }
    }

    multiset<int> s1, s2;
    if (2 == winner)
    {
        int half = sum >> 1;
        int curSum = half;

        for (int i = n; i >= 1; i--)
        {
            if (curSum >= a[i] && dp[i - 1][curSum - a[i]])
            {
                s1.insert(a[i]);
                curSum -= a[i];
            }
            else
            {
                s2.insert(a[i]);
            }
        }
    }
    


    return 0;
}
