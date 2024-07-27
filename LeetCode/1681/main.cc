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

class Solution
{
public:
    int minimumIncompatibility(vector<int> &nums, int k)
    {
        if (k == nums.size())
        {
            return 0;
        }

        // init
        memset(dp, -1, sizeof(dp));
        cntInSet = nums.size() / k;
        finalSt = (1 << nums.size()) - 1;
        sort(nums.begin(), nums.end());
        dp[0][0] = 0;

        for (size_t i = 1; i <= k; i++)
        {
            for (size_t st = 0; st <= finalSt; st++)
            {
                if (0 <= dp[i - 1][st])
                {
                    func(nums, i, st, st, -1, 0, cntInSet, dp[i - 1][st]);
                }
            }
        }
        
        return dp[k][finalSt];
    }

private:
    int dp[17][65536];
    int cntInSet;
    int finalSt;

    void func(vector<int> &nums, int rd, int st, int newSt, int last, int curr, int cnt, int sum)
    {
        if (curr < nums.size())
        {
            // 忽略当前 curr
            func(nums, rd, st, newSt, last, curr + 1, cnt, sum);

            if (0 == (st & (1 << curr)))
            {
                if (0 > last || nums[last] != nums[curr])
                {
                    newSt |= 1 << curr;
                    sum += nums[curr] - nums[last];

                    if (1 == cnt)
                    {
                        if (0 > dp[rd][newSt] || sum < dp[rd][newSt])
                        {
                            dp[rd][newSt] = sum;
                        }
                    }
                    else
                    {
                        func(nums, rd, st, newSt, curr, curr + 1, cnt - 1, sum);
                    }
                }
            }
        }
    }
};

int main()
{
    int k;
    cin >> k;

    vector<int> nums;
    int num;
    while (cin >> num)
    {
        nums.push_back(num);
        if (cin.get() == '\n')
            break;
    }

    Solution s;
    cout << s.minimumIncompatibility(nums, k) << endl;

    return 0;
}
