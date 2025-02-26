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

#define MAX_N 16
#define MAX_2N 65536

class Solution {
public:
    int countTriplets(vector<int> &nums)
    {
        int ret = 0;

        // init
        memset(dp, 0, sizeof(dp));

        for (size_t i = 0; i < nums.size(); i++)
        {
            dp[nums[i]]++;
        }

        // dp[mask], mask 子集的个数
        for (int i = 0; i < MAX_N; ++i)
        {
            for (int mask = 0; mask < (MAX_2N); ++mask)
            {
                if (mask & (1 << i))
                    dp[mask] += dp[mask ^ (1 << i)];
            }
        }

        int sum1 = 0, sum2 = 0, sum3 = 0;

        // 3 个都相同
        sum3 = dp[0];

        // 2 个想同的
        for (size_t i = 0; i < nums.size(); i++)
        {
            if (nums[i] == (nums[i] & (MAX_2N - 1 - nums[i])))
            {
                sum2 += 3 * (dp[MAX_2N - 1 - nums[i]] - 1);
            }
            else
            {
                sum2 += 3 * dp[MAX_2N - 1 - nums[i]];
            }
        }

        for (size_t i = 0; i < nums.size(); i++)
        {
            for (size_t j = 0; j < nums.size(); j++)
            {
                if (i != j)
                {
                    int iAndj = nums[i] & nums[j];
                    int tmp = 0;

                    if (nums[i] == (nums[i] & (MAX_2N - 1 - iAndj)))
                    {
                        tmp ++;
                    }
                    
                    if (nums[j] == (nums[j] & (MAX_2N - 1 - iAndj)))
                    {
                        tmp ++;
                    }

                    sum1 += dp[MAX_2N - 1 - iAndj] - tmp;
                }
            }
        }

        ret = sum1 + sum2 + sum3;

        return ret;
    }

private:
    int dp[MAX_2N];
};

int main()
{
    int n;
    cin >> n;

    vector<int> nums;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        nums.push_back(tmp);
    }

    Solution s;
    cout << s.countTriplets(nums) << endl;

    return 0;
}
