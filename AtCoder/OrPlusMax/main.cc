// https://atcoder.jp/contests/arc100/tasks/arc100_c

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

#define MAX_N   18
#define MAX_2N  262144

int dp0[MAX_2N];    // 1st max 的 index
int dp1[MAX_2N];    // 2nd max 的 index

int main()
{
    int n;
    cin >> n;
 
    memset(dp0, -1, sizeof(dp0));
    memset(dp1, -1, sizeof(dp1));

    vector<int> as;
    for (size_t i = 0; i < (1 << n); i++)
    {
        int tmp;
        cin >> tmp;

        as.push_back(tmp);

        dp0[i] = i;
    }
       
    for (int rd = 0; rd < n; rd ++)
    {
        for (int mask = (1 << n) - 1; mask >= 0; mask --)
        {
            if (mask & (1 << rd))
            {
                if (dp0[mask] == dp0[mask ^ (1 << rd)])
                {
                    // 最大的 index 相同
                    if (0 > dp1[mask])
                    {
                        dp1[mask] = dp1[mask ^ (1 << rd)];
                    }
                    else
                    {
                        // 0 <= dp1[mask]
                        if (0 <= dp1[mask ^ (1 << rd)] && as[dp1[mask]] < as[dp1[mask ^ (1 << rd)]])
                        {
                            dp1[mask] = dp1[mask ^ (1 << rd)];
                        }
                    }
                }
                else
                {
                    if (as[dp0[mask]] < as[dp0[mask ^ (1 << rd)]])
                    {
                        if (0 <= dp1[mask ^ (1 << rd)] && as[dp0[mask]] < as[dp1[mask ^ (1 << rd)]])
                        {
                            dp1[mask] = dp1[mask ^ (1 << rd)];
                        }
                        else
                        {
                            dp1[mask] = dp0[mask];
                        }

                        dp0[mask] = dp0[mask ^ (1 << rd)];
                    }
                    else
                    {
                        if (0 > dp1[mask] || as[dp1[mask]] < as[dp0[mask ^ (1 << rd)]])
                        {
                            dp1[mask] = dp0[mask ^ (1 << rd)];
                        }
                    }
                }
            }
        }
    }

    vector<int> ans;
    ans.push_back(0);

    for (size_t i = 1; i < (1 << n); i++)
    {
        int tmp = as[dp0[i]] + as[dp1[i]];
        if (tmp < ans[i - 1])
        {
            tmp = ans[i - 1];
        }
        ans.push_back(tmp);

        cout << tmp << endl;
    }

    return 0;
}
