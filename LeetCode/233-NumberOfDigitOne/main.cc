#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <stack>

using namespace std;

class Solution
{
public:
    int n;
    vector<int> a;
    int dp[64];

    int countDigitOne(int _n)
    {
        memset(dp, -1, sizeof(dp));

        n = _n;
        int x = n;

        while (x)
        {
            a.push_back(x % 10);
            x /= 10;
        }

        int len = a.size();

        int ans = dfs(len - 1, -1, 0, true);
        return ans;
    }

    int dfs(int pos, int pre, int sta, bool limit)
    {
        if (pos == -1)
            return 0;
        if (!limit && dp[pos] != -1)
            return dp[pos];
        int up = limit ? a[pos] : 9;
        int tmp = 0;
        for (int i = 0; i <= up; i++)
        {
            if (1 == i)
            {
                if (i == up)
                {
                    tmp += 1;
                    tmp += n % (int)(pow(10, pos));
                }
                else
                {
                    tmp += pow(10, pos);
                }
            }
            tmp += dfs(pos - 1, 0, 0, limit && i == a[pos]);
        }
        if (!limit)
            dp[pos] = tmp;

        return tmp;
    }
};

int main()
{
    int n;
    cin >> n;

    Solution s;
    cout << s.countDigitOne(n) << endl;

    return 0;
}
