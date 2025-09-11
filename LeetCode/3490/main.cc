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

            // 预处理
            dfs(dp, strNum, 0);

            if (2 <= strNum.length())
            {
                for (size_t sum = 1; sum < maxSum; sum++)
                {
                    if (0 < dp[strNum.length() - 2][sum].size())
                    {
                        int key = sum << 7;
                        unordered_map<int, int>::const_iterator it = dp[strNum.length() - 2][sum].find(key);
                        if (it != dp[strNum.length() - 2][sum].end())
                        {
                            ret += it->second;
                        }
                    }
                }
            }

            int preSum = 0;
            int prePrdt = 1;
            for (int pos = 0; pos < strNum.length(); pos++)
            {
                int up = strNum.at(pos) - '0';
                if (0 == up)
                {
                    break;
                }

                int i = strNum.length() - 1 - pos - 1;
                if (0 <= i)
                {
                    for (size_t sum = 1; sum < maxSum; sum++)
                    {
                        if (0 < dp[i][sum].size())
                        {
                            for (unordered_map<int, int>::iterator it = dp[i][sum].begin(); it != dp[i][sum].end(); it++)
                            {
                                int oldMod = it->first & 127;
                                int oldS = it->first >> 7;

                                for (size_t n = 1; n < up; n++)
                                {
                                    int newSum = sum + n + preSum;
                                    if (oldS == newSum)
                                    {
                                        int newMod = (oldMod * prePrdt * n) % oldS;
                                        if (0 == newMod)
                                        {
                                            ret += it->second;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    for (size_t n = 1; n <= up; n++)
                    {
                        if (0 == ((prePrdt * n) % (preSum + n)))
                        {
                            ret++;
                        }
                    }
                }

                preSum += up;
                prePrdt *= up;
            }

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

    void dfs(vector<vector<unordered_map<int, int>>> &dp, const string& strNum, int pos)
    {
        if (pos < strNum.length() - 1)
        {
            if (0 == pos)
            {
                for (size_t n = 1; n <= 9; n++)
                {
                    for (size_t s = n; s < maxSum; s++)
                    {
                        int key = (s << 7) | (n % s);
                        dp[pos][n][key]++;
                    }
                }
            }
            else
            {
                for (size_t sum = 1; sum < maxSum; sum++)
                {
                    if (0 < dp[pos - 1][sum].size())
                    {
                        for (unordered_map<int, int>::iterator it = dp[pos - 1][sum].begin(); it != dp[pos - 1][sum].end(); it++)
                        {
                            int oldMod = it->first & 127;
                            int oldS = it->first >> 7;

                            for (size_t n = 1; n <= 9; n++)
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

                for (size_t n = 1; n <= 9; n++)
                {
                    for (size_t s = n; s < maxSum; s++)
                    {
                        int key = (s << 7) | (n % s);
                        dp[pos][n][key]++;
                    }
                }
            }
            
            dfs(dp, strNum, pos + 1);
        }
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
