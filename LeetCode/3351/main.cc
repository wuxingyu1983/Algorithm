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
    int sumOfGoodSubsequences(vector<int> &nums)
    {
        int ret = 0;

        const int maxN = 100005;
        const int mod = 1000000007;

        long long cnt[maxN];
        long long sum[maxN];
        memset(cnt, 0, sizeof(cnt));
        memset(sum, 0, sizeof(sum));

        long long total = 0;

        for (size_t i = 0; i < nums.size(); i++)
        {
            long long num = nums[i];
            long long tmpCnt = 1;
            long long tmpSum = 0;

            if (0 < num)
            {
                tmpCnt += cnt[num - 1];
                tmpSum += sum[num - 1];
            }
            
            tmpCnt += cnt[num + 1];
            tmpSum += sum[num + 1];

            cnt[num] += tmpCnt;
            cnt[num] %= mod;

            sum[num] += tmpSum + num * tmpCnt;
            sum[num] %= mod;

            total += tmpSum + num * tmpCnt;
            total %= mod;
        }

        ret = total;

        return ret;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> nums;
    for (size_t i = 0; i < n; i++)
    {
        int num;
        cin >> num;

        nums.push_back(num);
    }

    Solution s;

    cout << s.sumOfGoodSubsequences(nums) << endl;

    return 0;
}
