// https://codeforces.com/problemset/problem/383/E

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

#define MAX_M   24
#define MAX_2M  16777216

int dp1[16777216];
int dp2[16777216];
int dp3[16777216];

int main()
{
    int n;

    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;

        int a = str[0] - 'a';
        int b = str[1] - 'a';
        int c = str[2] - 'a';

        dp1[1 << a] ++;
        dp1[1 << b] ++;
        dp1[1 << c] ++;

        dp2[(1 << a) | (1 << b)] ++;
        dp2[(1 << a) | (1 << c)] ++;
        dp2[(1 << b) | (1 << c)] ++;

        dp3[(1 << a) | (1 << b) | (1 << c)] ++;
    }
    
    for (int rd = 0; rd < MAX_M; rd ++)
    {
        for (int mask = MAX_2M - 1; mask >= 0; mask--)
        {
            if (mask & (1 << rd))
            {
                dp1[mask] += dp1[mask ^ (1 << rd)];
                dp2[mask] += dp2[mask ^ (1 << rd)];
                dp3[mask] += dp3[mask ^ (1 << rd)];
            }
        }
    }

    int ans = 0;

    for (size_t i = 0; i < MAX_2M; i++)
    {
        int num = dp1[i] - dp2[i] + dp3[i];
        ans ^= (num * num);
    }

    cout << ans << endl;

    return 0;
}
