// https://codeforces.com/contest/688/problem/E

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

const int MAXN = 505;
bool dp[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    dp[0][0] = true;

    for (int i = 1; i <= n; i++)
    {
        int c;
        cin >> c;
        
        for (int j = k; j >= c; j--)
        {
            for (int x = j; x >= 0; x--)
            {
                // dp[j][x]

                if (dp[j - c][x])
                {
                    dp[j][x] = true;
                }

                if (x >= c && dp[j - c][x - c])
                {
                    dp[j][x] = true;
                }
            }
        }
    }
    
    vector<int> ans;
    for (int x = 0; x <= k; x++)
    {
        if (dp[k][x])
        {
            ans.push_back(x);
        }
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}
