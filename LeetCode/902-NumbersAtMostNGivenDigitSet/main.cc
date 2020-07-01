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
    vector<int> a;
    int dp[32];

    int atMostNGivenDigitSet(vector<string> &D, int N)
    {
        memset(dp, -1, sizeof(dp));

        vector<int> d;
        for (size_t i = 0; i < D.size(); i++)
        {
            d.push_back(stoi(D[i]));
        }

        int x = N;

        while (x)
        {
            a.push_back(x % 10);
            x /= 10;
        }

        int ans = 0;
        for (int i = 0; i < a.size() - 1; i++)
        {
            ans += dfs(i, -1, 0, false, d);
        }

        bool limit = true;
        if (a[a.size() - 1] > d[d.size() - 1])
        {
            limit = false;
        }

        ans += dfs(a.size() - 1, -1, 0, limit, d);

        return ans;
    }

    int dfs(int pos, int pre, int sta, bool limit, vector<int> &d)
    {
        if (pos == -1)
        {
            return 1;
        }
        if (!limit && dp[pos] != -1)
            return dp[pos];
        int up = limit ? a[pos] : 9;
        int tmp = 0;
        for (vector<int>::iterator it = d.begin(); it != d.end() && (*it) <= up; it++)
        {
            tmp += dfs(pos - 1, -1, 0, limit && (*it) == a[pos], d);
        }
        if (!limit)
            dp[pos] = tmp;

        return tmp;
    }
};

int main()
{
    string s[] = {"1", "3", "5", "7"};
    vector<string> v(s, s + 4);

    Solution sol;
    cout << sol.atMostNGivenDigitSet(v, 100) << endl;

    return 0;
}
