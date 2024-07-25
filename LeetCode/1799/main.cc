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
    }

private:
    int gcd[14][14];
    int dp[8][16384];

    void init(vector<int> &nums)
    {
        memset(gcd, 0, sizeof(gcd));
        memset(dp, 0, sizeof(dp));

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