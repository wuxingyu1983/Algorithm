// https://codeforces.com/contest/148/problem/E

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

const int MAXN = 101;
const int MAXM = 10001;

vector<int> shelves[MAXN];
vector<int> sums[MAXN];
int sdp[MAXN][MAXM];
int dp[MAXM];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;

        for (int j = 0; j < num; j++)
        {
            int val;
            cin >> val;

            shelves[i].push_back(val);

            if (0 == j)
                sums[i].push_back(val);
            else
                sums[i].push_back(val + sums[i][j - 1]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        int size = shelves[i].size();
        for (int j = 1; j <= min(size, m); j++)
        {
            for (int start = 0; start + size - j - 1 <= size - 1; start++)
            {
                int end = start + size - j - 1;

                int tmp = sums[i][end];
                if (0 < start)
                    tmp -= sums[i][start - 1];

                sdp[i][j] = max(sdp[i][j], sums[i][size - 1] - tmp);
            }
        }
    }

    // i = 0
    for (int j = m; j >= 1; j--)
    {
        dp[j] = sdp[0][j];
    }
    

    for (int i = 1; i < n; i++)
    {
        for (int j = m; j > 0; j--)
        {
            for (int l = 1; l < j; l ++)
            {
                dp[j] = max(dp[j], dp[l] + sdp[i][j - l]);
            }
        }
    }
    
    cout << dp[m] << "\n";

    return 0;
}
