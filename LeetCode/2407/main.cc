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
    int lengthOfLIS(vector<int> &nums, int k)
    {
        int ret = 0;

        const int maxN = 100001;

        vector<int> d(maxN * 4 + 2);

        for (size_t i = 0; i < nums.size(); i++)
        {
            int num = nums[i];

            int max = 0;

            if (1 < num)
            {
                int left = num - k;
                if (1 > left)
                {
                    left = 1;
                }

                max = getMax(d, left, num - 1, 1, maxN, 1);
            }

            update(d, num, (max + 1), 1, maxN, 1);

            if (ret < max + 1)
            {
                ret = max + 1;
            }
        }

        return ret;
    }

private:
    // segment tree func
    int update(vector<int> &d, int idx, int c, int s, int t, int p)
    {
        if (idx == s && idx == t)
        {
            d[p] = c;
            return c;
        }
        int m = s + ((t - s) >> 1);
        if (idx <= m)
        {
            unsigned long long tmp = update(d, idx, c, s, m, p * 2);
            if (tmp > d[p])
            {
                d[p] = tmp;
            }
        }
        if (idx > m)
        {
            unsigned long long tmp = update(d, idx, c, m + 1, t, p * 2 + 1);
            if (tmp > d[p])
            {
                d[p] = tmp;
            }
        }

        return d[p];
    }

    int getMax(vector<int> &d, int l, int r, int s, int t, int p)
    {
        if (l > r)
        {
            return 0;
        }
        if (l <= s && t <= r)
            return d[p];
        int m = s + ((t - s) >> 1);
        int max = 0;
        if (l <= m)
        {
            max = getMax(d, l, r, s, m, p * 2);
        }
        if (r > m)
        {
            int tmp = getMax(d, l, r, m + 1, t, p * 2 + 1);
            if (tmp > max)
            {
                max = tmp;
            }
        }
        return max;
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

    int k;
    cin >> k;

    Solution s;
    cout << s.lengthOfLIS(nums, k) << endl;
    
    return 0;
}
