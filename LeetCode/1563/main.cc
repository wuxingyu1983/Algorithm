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
    int stoneGameV(vector<int> &stoneValue)
    {
        int ret = 0;

        vector<int> sum(stoneValue.size());
        sum[0] = stoneValue[0];
        for (size_t i = 1; i < stoneValue.size(); i++)
        {
            sum[i] = sum[i - 1] + stoneValue[i];
        }
        
        vector<vector<int>> dp(stoneValue.size(), vector<int>(stoneValue.size(), 0));

        for (size_t stp = 1; stp < stoneValue.size(); stp++)
        {
            for (size_t x = 0; x < stoneValue.size() && x + stp < stoneValue.size(); x++)
            {
                for (size_t i = 0; i < stp; i++)
                {
                    // left : x -> x + i
                    int leftSum = sum[x + i];
                    if (0 < x)
                    {
                        leftSum -= sum[x - 1];
                    }

                    // right : x + i + 1 -> x + stp
                    int rightSum = sum[x + stp] - sum[x + i];

                    int tmp = 0;
                    if (leftSum > rightSum)
                    {
                        tmp = rightSum + dp[x + i + 1][x + stp];
                    }
                    else if (leftSum < rightSum)
                    {
                        tmp = leftSum + dp[x][x + i];
                    }
                    else
                    {
                        // ==
                        tmp = leftSum + max(dp[x][x + i], dp[x + i + 1][x + stp]);
                    }

                    if (tmp > dp[x][x + stp])
                    {
                        dp[x][x + stp] = tmp;
                    }
                }
            }
        }

        ret = dp[0][stoneValue.size() - 1];

        return ret;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> vals;
    for (size_t i = 0; i < n; i++)
    {
        int v;
        cin >> v;

        vals.push_back(v);
    }
    
    Solution s;
    cout << s.stoneGameV(vals) << endl;

    return 0;
}
