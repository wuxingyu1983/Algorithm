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
                for (size_t sum = 1; sum < 82; sum++)
                {
                    dp[pos][sum].clear();
                }

                // 1 -> up - 1
                for (size_t n = 1; n < up; n++)
                {
                    for (size_t mod = 1; mod < 82; mod++)
                    {
                        int key = (mod << 7) | (n % mod);
                        dp[pos][n][key] ++;
                    }
                }
                ret += dfs(dp, strNum, 1, pos + 1, false);
                // clear
                for (size_t sum = 1; sum < 82; sum++)
                {
                    dp[pos][sum].clear();
                }

                // up
                for (size_t mod = 1; mod < 82; mod++)
                {
                    int key = (mod << 7) | (up % mod);
                    dp[pos][up][key] ++;
                }
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
                for (size_t sum = 1; sum < 82; sum++)
                {
                    dp[pos][sum].clear();
                }
                
                for (size_t n = 0; n < up; n++)
                {
                    for (size_t sum = 1; sum < 82; sum++)
                    {
                        if (0 < dp[pos - 1][sum].size())
                        {
                            for (unordered_map<int, int>::iterator it = dp[pos - 1][sum].begin(); it != dp[pos - 1][sum].end(); it++)
                            {
                                int oldMod = it->first & 127;
                                int oldS = it->first >> 7;

                                int newSum = sum + n;
                                int newMod = (oldMod * n) % oldS;

                                int newKey = (oldS << 7) + newMod;
                                dp[pos][newSum][newKey] += it->second;
                            }
                        }
                    }
                }
                
            }
        }
        else
        {
            // pos == strNum.length()

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
