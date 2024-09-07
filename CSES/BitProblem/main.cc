// https://cses.fi/problemset/task/1654/

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

#define MAX_M   20
#define MAX_2M  1048575

int n;
vector<int> xs;

int dp0[MAX_2M + 1];
int dp1[MAX_2M + 1];

int main()
{
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;

        xs.push_back(tmp);

        dp0[tmp] ++;
        dp1[MAX_2M - tmp] ++;
    }

    for (int i = 0; i < MAX_M; i ++)
    {
        for (int mask = MAX_2M; mask >= 0; mask --)
        {
            if (mask & (1 << i))
            {
                dp0[mask] += dp0[mask ^ (1 << i)];
                dp1[mask] += dp1[mask ^ (1 << i)];
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        int tmp = xs[i];

        cout << dp0[tmp] << " " << dp1[MAX_2M - tmp] << " " << n - dp0[MAX_2M - tmp] << endl;
    }
    

    return 0;
}
