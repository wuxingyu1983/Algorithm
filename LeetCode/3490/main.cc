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
    int maxSum;

    int func(int n)
    {
        int ret = 0;

        if (0 < n)
        {
            string strNum = to_string(n);
            if (10 == strNum.length())
            {
                maxSum = 82;
            }
            else
            {
                maxSum = 9 * strNum.length() + 1;
            }
            vector<vector<unordered_map<int, int>>> dp(strNum.length(), vector<unordered_map<int, int>>(maxSum));

            ret = dfs(dp, strNum, 0, 0, true);

            // 处理含有0的数字个数
            {
                // 不含有0的数字个数
                int cnt = 0;
                for (size_t i = 1; i < strNum.length(); i++)
                {
                    cnt += (int)pow(9, i);
                }

                bool have0 = false;
                for (size_t i = 0; i < strNum.length(); i++)
                {
                    int up = strNum.at(i) - '0';
                    if (up)
                    {
                        cnt += (up - 1) * (int)pow(9, strNum.length() - 1 - i);
                    }
                    else
                    {
                        have0 = true;
                        break;
                    }
                }

                if (false == have0)
                {
                    cnt ++;
                }

                ret += n - cnt;
            }
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
                for (size_t sum = 1; sum < maxSum; sum++)
                {
                    dp[pos][sum].clear();
                }

                // 1 -> up - 1
                for (size_t n = 1; n < up; n++)
                {
                    for (size_t mod = n; mod < maxSum; mod++)
                    {
                        int key = (mod << 7) | (n % mod);
                        dp[pos][n][key] ++;
                    }
                }
                ret += dfs(dp, strNum, 1, pos + 1, false);
                // clear
                for (size_t sum = 1; sum < maxSum; sum++)
                {
                    dp[pos][sum].clear();
                }

                // up
                for (size_t mod = up; mod < maxSum; mod++)
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
                for (size_t sum = 1; sum < maxSum; sum++)
                {
                    dp[pos][sum].clear();
                }
               
                for (size_t sum = 1; sum < maxSum; sum++)
                {
                    if (0 < dp[pos - 1][sum].size())
                    {
                        for (unordered_map<int, int>::iterator it = dp[pos - 1][sum].begin(); it != dp[pos - 1][sum].end(); it++)
                        {
                            int oldMod = it->first & 127;
                            int oldS = it->first >> 7;
                            
                            for (size_t n = 1; n < up; n++)
                            {
                                int newSum = sum + n;

                                if (newSum > oldS)
                                {
                                    break;
                                }

                                int newMod = (oldMod * n) % oldS;

                                int newKey = (oldS << 7) + newMod;
                                dp[pos][newSum][newKey] += it->second;
                            }
                        }
                    }
                }

                if (0 == top)
                {
                    for (size_t n = 1; n < up; n++)
                    {
                        for (size_t s = n; s < maxSum; s++)
                        {
                            int key = (s << 7) | (n % s);
                            dp[pos][n][key]++;
                        }
                    }
                }

                ret += dfs(dp, strNum, top, pos + 1, false);

                if (up < 10 && 0 < up)
                {
                    // limit
                    // clear
                    for (size_t sum = 1; sum < maxSum; sum++)
                    {
                        dp[pos][sum].clear();
                    }

                    for (size_t sum = 1; sum < maxSum; sum++)
                    {
                        if (0 < dp[pos - 1][sum].size())
                        {
                            for (unordered_map<int, int>::iterator it = dp[pos - 1][sum].begin(); it != dp[pos - 1][sum].end(); it++)
                            {
                                int oldMod = it->first & 127;
                                int oldS = it->first >> 7;

                                int newSum = sum + up;

                                if (newSum > oldS)
                                {
                                    continue;
                                }

                                int newMod = (oldMod * up) % oldS;

                                int newKey = (oldS << 7) + newMod;
                                dp[pos][newSum][newKey] += it->second;
                            }
                        }
                    }

                    ret += dfs(dp, strNum, top, pos + 1, true);
                }
            }
        }
        else
        {
            // pos == strNum.length()
            for (size_t sum = 1; sum < maxSum; sum++)
            {
                if (0 < dp[pos - 1][sum].size())
                {
                    int key = sum << 7;
                    unordered_map<int, int>::const_iterator it = dp[pos - 1][sum].find(key);
                    if (it != dp[pos - 1][sum].end())
                    {
                        ret += it->second;
                    }
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
