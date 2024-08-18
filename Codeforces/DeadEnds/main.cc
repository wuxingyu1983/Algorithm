// https://codeforces.com/problemset/problem/53/E#

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

#define DEBUG   0
#define MAX_N   10
#define MAX_2N  1024

int dp[MAX_2N][MAX_2N];     // [st1][st2], st1 : 1 - 已经包含了；st2 : 1 - dead ends

int n, m, k;

int main()
{
    cin >> n >> m >> k;

    int finalSt = (1 << n) - 1;

    // init
    dp[0][0] = 1;

    for (size_t iM = 0; iM < m; iM++)
    {
        int v1, v2;
        cin >> v1 >> v2;

        v1 --;
        v2 --;

        for (size_t st1 = 0; st1 <= finalSt; st1++)
        {
            for (size_t st2 = 0; st2 <= finalSt; st2++)
            {
                if (dp[st1][st2])
                {

                }
            }
        }
    }

    int ans = 0;

    cout << ans << endl;

    return 0;
}
