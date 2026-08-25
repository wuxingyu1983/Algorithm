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
vector<int> sums[MAXN], rsums[MAXN];
int total[MAXN][101];
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

        sums[i].push_back(0);

        for (int j = 1; j <= num; j++)
        {
            int val;
            cin >> val;

            shelves[i].push_back(val);

            sums[i].push_back(val + sums[i][j - 1]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        reverse(shelves[i].begin(), shelves[i].end());

        rsums[i].push_back(0);

        if (1 == shelves[i].size())
        {
            rsums[i].push_back(0);
        }
        else
        {
            for (int j = 1; j <= shelves[i].size(); j++)
            {
                rsums[i].push_back(shelves[i][j - 1] + rsums[i][j - 1]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= shelves[i].size(); j++)
        {
            for (int l = 0; l <= j; l++)
            {
                total[i][j] = max(total[i][j], sums[i][l] + rsums[i][j - l]);
            }
        }
    }

    {
        // i = 0
        for (int j = min(m, (int)shelves[0].size()); j >= 1; j--)
        {
            dp[j] = total[0][j];
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (0 < dp[j] || 0 == j)
                {
                    for (int l = 1; l <= min(m, (int)shelves[i].size()) && j + l <= m; l++)
                    {
                        dp[j + l] = max(dp[j + l], dp[j] + total[i][l]);
                    }
                }
            }
        }
    }

    cout << dp[m] << "\n";

    return 0;
}
