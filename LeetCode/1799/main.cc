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
    int maxScore(vector<int> &nums)
    {
        init(nums);

        int finalSt = (1 << nums.size()) - 1;

        for (size_t op = 1; op <= nums.size() / 2; op++)
        {
            for (size_t st = 0; st <= finalSt; st++)
            {
                if (0 < dp[op - 1][st])
                {
                    func(st, op, 0, nums.size(), dp[op - 1][st]);
                }
            }
        }

        return dp[nums.size() / 2][finalSt] - 1;
    }

private:
    int gcd[14][14];
    int dp[8][16384];

    void init(vector<int> &nums)
    {
        memset(gcd, 0, sizeof(gcd));
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;

        for (size_t i = 0; i < nums.size(); i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                gcd[i][j] = gcd[j][i] = gcdFunc(nums[i], nums[j]);
            }
        }
        
    }

    int gcdFunc(int a, int b)
    {
        for (;;)
        {
            if (b == 0)
                return a;
            int temp = a % b;
            a = b;
            b = temp;
        }
    }

    void func(int st, int rd, int idx, int last, int sum)
    {
        if (idx < last - 1)
        {
            if (0 == (st & (1 << idx)))
            {
                for (size_t i = idx + 1; i < last; i++)
                {
                    if (0 == (st & (1 << i)))
                    {
                        int newSt = st | (1 << idx) | (1 << i);
                        int newSum = sum + rd * gcd[idx][i];

                        if (newSum > dp[rd][newSt])
                        {
                            dp[rd][newSt] = newSum;
                        }
                    }
                }
            }

            func(st, rd, idx + 1, last, sum);
        }
    }
};

int main()
{
    vector<int> nums;

    int num;
    while (cin >> num)
    {
        nums.push_back(num);
        if (cin.get() == '\n')
            break;
    }

    Solution s;
    cout << s.maxScore(nums) << endl;

    return 0;
}