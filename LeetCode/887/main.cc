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

        // init
        {
            for (size_t floor = 1; floor <= n; floor++)
            {
                dp[floor][1] = floor;
            }

            for (size_t iK = 2; iK <= k; iK++)
            {
                dp[1][iK] = 1;
            }
        }

        for (int floor = 2; floor <= n; floor++)
        {
            for (size_t iK = 2; iK <= k; iK++)
            {
                dp[floor][iK] = -1;
                
                for (size_t i = 1; i <= floor; i++)
                {
                    int tmp = max(dp[i - 1][iK - 1], dp[floor - i][iK]);
                    tmp += 1;

                    if (0 > dp[floor][iK] || dp[floor][iK] > tmp)
                        dp[floor][iK] = tmp;
                }
                
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
