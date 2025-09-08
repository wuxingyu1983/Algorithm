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
#include <unordered_map>
#include <bitset>

using namespace std;

class Solution
{
public:
    int beautifulNumbers(int l, int r)
    {
        int ret = 0;

        ret = func(r) - func(l - 1);

        return ret;
    }

private:
    int ***dp;

    int func(int n)
    {
        int ret = 0;

        if (0 < n)
        {
            string strNum = to_string(n);

            dp = new int**[strNum.length()];
            for (size_t i = 0; i < strNum.length(); i++)
            {
                dp[i] = new int *[82];
                for (size_t j = 0; j < 82; j++)
                {
                    dp[i][j] = new int[82];
                    memset(dp[i][j], 0, sizeof(int) * 82);
                }
            }

            ret = dfs(strNum, 0, true);
        }

        return ret;
    }

    int dfs(const string& strNum, int pos, bool limit)
    {
        int ret = 0;

        return ret;
    }
};

int main()
{
    int l, r;
    cin >> l >> r;

    Solution s;
    cout << s.beautifulNumbers(l, r) << endl;

    return 0;
}
