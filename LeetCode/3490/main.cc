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

    int func(int n)
    {
        int ret = 0;

        if (0 < n)
        {
            string strNum = to_string(n);
            vector<vector<unordered_map<int, int>>> dp(strNum.length(), vector<unordered_map<int, int>>(82));

            ret = dfs(dp, strNum, 0, 0, true);
        }

        return ret;
    }

    int dfs(vector<vector<unordered_map<int, int>>> &dp, const string& strNum, int top, int pos, bool limit)
    {
        int ret = 0;

        if (pos < strNum.length())
        {
            if (0 == pos)
            {
                int up = strNum.at(pos) - '0';

                // 0
                ret += dfs(dp, strNum, 0, pos + 1, false);
                // clear
                

                // 1 -> up - 1
                for (size_t n = 1; n < up; n++)
                {
//                    dp[pos][n][0] ++;
                }
                ret += dfs(dp, strNum, 1, pos + 1, false);
                // clear

                // up
//                dp[pos][up][0] ++;
                ret += dfs(dp, strNum, 1, pos + 1, true);
            }
            else
            {
                int up = 10;
                if (limit)
                {
                    up = strNum.at(pos) - '0';
                }

                // clear
                
                for (size_t n = 0; n < up; n++)
                {
                    
                }
                
            }
        }

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
