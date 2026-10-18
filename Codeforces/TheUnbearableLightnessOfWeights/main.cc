// https://codeforces.com/contest/1078/problem/B

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

using namespace std;

int dp[101][10005];
char flag[101][10005];
int cnt[101];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int sum = 0;
    int diff = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];

        cnt[a[i]]++;
        if (1 == cnt[a[i]])
        {
            diff++;
        }
    }

    sort(a.begin(), a.end());

    int ans = 1;

    if (diff < n)
    {
        
    }

    cout << ans << "\n";

    return 0;
}
