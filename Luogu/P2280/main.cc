// https://www.luogu.com.cn/problem/P2280

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define MAX_XY  5001

int dp[MAX_XY][MAX_XY];

int main()
{
    int n, m;
    cin >> n >> m;

    for (size_t i = 0; i < n; i++)
    {
        int x, y, v;
        cin >> x >> y >> v;
        dp[x][y] += v;
    }

    for (size_t row = 0; row < MAX_XY; row++)
    {
        for (size_t col = 1; col < MAX_XY; col++)
        {
            dp[row][col] += dp[row][col - 1];
        }
    }

    for (size_t col = 0; col < MAX_XY; col++)
    {
        for (size_t row = 1; row < MAX_XY; row++)
        {
            dp[row][col] += dp[row - 1][col];
        }
    }
    
    int ans = 0;

    for (size_t row = m; row < MAX_XY; row++)
    {
        for (size_t col = m; col < MAX_XY; col++)
        {
            int tmp = dp[row][col] - dp[row - m][col] - dp[row][col - m] + dp[row - m][col - m];
            if (tmp > ans)
            {
                ans = tmp;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
