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
        cntInSet = nums.size() / k;
        finalSt = (1 << nums.size()) - 1;

        dp = new int *[k + 1];
        for (size_t i = 0; i <= k; i++)
        {
            dp[i] = new int[finalSt + 1];
            memset(dp[i], -1, sizeof(int) * (finalSt + 1));
        }

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
    int **dp;
    int cntInSet;
    int finalSt;

    void func(vector<int> &nums, int rd, int st, int newSt, int last, int curr, int cnt, int sum)
    {
        if (curr < nums.size())
        {
            if (0 == (st & (1 << curr)))
            {
                if (0 > last || nums[last] != nums[curr])
                {
                    int tmpSt = newSt | (1 << curr);
                    int tmpSum = sum;

                    if (0 <= last)
                    {
                        tmpSum += nums[curr] - nums[last];
                    }

                    if (1 == cnt)
                    {
                        if (0 > dp[rd][tmpSt] || tmpSum < dp[rd][tmpSt])
                        {
                            dp[rd][tmpSt] = tmpSum;
                        }
                    }
                    else
                    {
                        func(nums, rd, st, tmpSt, curr, curr + 1, cnt - 1, tmpSum);
                    }
                }
            }

            // 忽略当前 curr
            func(nums, rd, st, newSt, last, curr + 1, cnt, sum);
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
