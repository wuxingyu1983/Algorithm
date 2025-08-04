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

        vector<int> d(2 * maxN * 4);
        vector<int> b(2 * maxN * 4);

        

        return ret;
    }

private:
    // segment tree func
    void update(vector<int> &d, vector<int> &b, int l, int r, int c, int s, int t, int p)
    {
        if (l <= s && t <= r)
        {
            d[p] += (t - s + 1) * c, b[p] += c;
            return;
        }
        int m = s + ((t - s) >> 1);
        if (b[p] && s != t)
        {
            d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
            b[p * 2] += b[p], b[p * 2 + 1] += b[p];
            b[p] = 0;
        }
        if (l <= m)
            update(d, b, l, r, c, s, m, p * 2);
        if (r > m)
            update(d, b, l, r, c, m + 1, t, p * 2 + 1);
        if (d[p * 2] < d[p * 2 + 1])
            d[p] = d[p * 2];
        else
            d[p] = d[p * 2 + 1];
    }

    int getMax(vector<int> &d, vector<int> &b, int l, int r, int s, int t, int p)
    {
        if (l <= s && t <= r)
        {
            return d[p];
        }
        int m = s + ((t - s) >> 1);
        if (b[p])
        {
            d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
            b[p * 2] += b[p], b[p * 2 + 1] += b[p];
            b[p] = 0;
        }
        int max = 0;
        if (l <= m)
        {
            max = getMax(d, b, l, r, s, m, p * 2);
        }
        if (r > m)
        {
            int tmp = getMax(d, b, l, r, m + 1, t, p * 2 + 1);
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
