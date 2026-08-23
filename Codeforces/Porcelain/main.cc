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
    
    return 0;
}
