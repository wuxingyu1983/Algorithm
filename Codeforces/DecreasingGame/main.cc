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

vector<bitset<MAXN * MAXN>> dp(MAXN, bitset<MAXN * MAXN>());
vector<int> groups(MAXN, 1);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int sum = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
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

    if (2 == winner)
    {
        int half = sum >> 1;
        int curSum = half;

        for (int i = n; i >= 1; i--)
        {
            if (curSum >= a[i] && dp[i - 1][curSum - a[i]])
            {
                curSum -= a[i];
            }
            else
            {
                groups[i] = 2;
            }
        }
    }
    
    if (1 == winner)
    {
        cout << "First" << "\n";
        cout << 1 << "\n";
        cout.flush();

        int preFirst = 1;
        int x;
        while (cin >> x && 0 < x)
        {
            int tmp = min(a[preFirst], a[x]);
            a[preFirst] -= tmp;
            a[x] -= tmp;

            for (int i = 1; i <= n; i++)
            {
                if (a[i] > 0)
                {
                    preFirst = i;
                    cout << i << "\n";
                    cout.flush();
                    break;
                }
            }
        }
    }
    else
    {
        cout << "Second" << "\n";
        cout.flush();

        int x;
        while (cin >> x && 0 < x)
        {
            for (int i = 1; i <= n; i++)
            {
                if (groups[i] != groups[x] && a[i] > 0)
                {
                    cout << i << "\n";
                    cout.flush();

                    int tmp = min(a[i], a[x]);
                    a[i] -= tmp;
                    a[x] -= tmp;

                    break;
                }
            }
        }
    }

    return 0;
}
