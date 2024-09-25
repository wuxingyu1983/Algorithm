// https://acm.hdu.edu.cn/showproblem.php?pid=6514

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

#define MAX_MN  10000001

char land[MAX_MN];
int dp[MAX_MN];

int main()
{
    int n, m;   // n = rows, m = cols
    cin >> n >> m;

    int p;
    cin >> p;
    
    for (size_t i = 0; i < p; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        x1 --;
        y1 --;
        x2 --;
        y2 --;

        for (size_t row = x1; row <= x2; row++)
        {
            memset(&(land[row * m + y1]), 1, (y2 - y1 + 1));
        }
    }
    
    for (size_t row = 0; row < n; row++)
    {
        for (size_t col = 1; col < m; col++)
        {
            dp[row * m + col] += dp[row * m + col - 1] + land[row * m + col];
        }
    }

    for (size_t col = 0; col < m; col++)
    {
        for (size_t row = 1; row < n; row++)
        {
            dp[row * m + col] += dp[(row - 1) * m + col];
        }
    }

    int q;
    cin >> q;

    for (size_t i = 0; i < q; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        x1 --;
        y1 --;
        x2 --;
        y2 --;

        int total = (y2 - y1 + 1) * (x2 - x1 + 1);
        int cnt = dp[x2 * m + y2];
        if (0 < x1)
            cnt -= dp[(x1 - 1) * m + y2];
        if (0 < y1)
            cnt -= dp[x2 * m + (y1 - 1)];
        if (0 < x1 && 0 < y1)
            cnt += dp[(x1 - 1) * m + (y1 - 1)];
        if (total == cnt)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    

    return 0;
}
