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
#include <unordered_map>
#include <bitset>

using namespace std;

class Solution
{
public:
    int superEggDrop(int k, int n)
    {
        int ret = 0;

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        vector<vector<int>> lastOcc(k + 1, vector<int>(n + 1, 0));

        // init
        {
            for (size_t floor = 1; floor <= n; floor++)
            {
                dp[floor][1] = floor;
                lastOcc[1][floor] = floor;
            }

            for (size_t iK = 2; iK <= k; iK++)
            {
                dp[1][iK] = 1;
                lastOcc[iK][1] = 1;
            }
        }

        for (int floor = 2; floor <= n; floor++)
        {
            for (size_t iK = 2; iK <= k; iK++)
            {
                dp[floor][iK] = -1;
               
                for (int val = 1; val < floor; val++)
                {
                    int stp = lastOcc[iK][val];
                    if (0 >= stp || stp >= floor)
                    {
                        break;
                    }

                    int tmp = max(dp[floor - stp - 1][iK - 1], dp[stp][iK]);
                    tmp += 1;

                    if (0 > dp[floor][iK] || dp[floor][iK] > tmp)
                        dp[floor][iK] = tmp;
                }

                lastOcc[iK][dp[floor][iK]] = floor;
            }
        }

        ret = dp[n][k];

        return ret;
    }
};

int main()
{
    int n, k;
    cin >> k >> n;

    Solution s;
    cout << s.superEggDrop(k, n) << endl;

    return 0;
}
