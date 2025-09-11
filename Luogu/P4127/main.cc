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

const int OFFSET = 8;
const int MASK = 255;

class Solution
{
public:
    int beautifulNumbers(long long l, long long r)
    {
        long long ret = 0;

        string strNum = to_string(r);
        if (19 == strNum.length())
        {
            maxSum = 163;
        }
        else
        {
            maxSum = 9 * strNum.length() + 1;
        }
        vector<vector<unordered_map<int, long long>>> dp(strNum.length(), vector<unordered_map<int, long long>>(maxSum));

        // 预处理
        dfs(dp, strNum, 0);

        ret = func(r, dp) - func(l - 1, dp);

        return ret;
    }

private:
    int maxSum;

    long long func(long long n, vector<vector<unordered_map<int, long long>>> &dp)
    {
        long long ret = 0;

        if (0 < n)
        {
            string strNum = to_string(n);
            if (19 == strNum.length())
            {
                maxSum = 163;
            }
            else
            {
                maxSum = 9 * strNum.length() + 1;
            }
/*
            int pos = strNum.length() - 2;
            if (0 <= pos)
            {
                for (size_t sum = 1; sum < maxSum; sum++)
                {
                    if (0 < dp[pos][sum].size())
                    {
                        int key = sum << OFFSET;
                        unordered_map<int, long long>::const_iterator it = dp[pos][sum].find(key);
                        if (it != dp[pos][sum].end())
                        {
                            ret += it->second;
                        }
                    }
                }
            }
*/
            int preSum = 0;
            long long preVal = 0;
            for (int pos = 0; pos < strNum.length(); pos++)
            {
                int up = strNum.at(pos) - '0';
                int i = strNum.length() - 1 - pos - 1;
                if (0 <= i)
                {
                    for (size_t sum = 1; sum < maxSum; sum++)
                    {
                        if (0 < dp[i][sum].size())
                        {
                            for (unordered_map<int, long long>::iterator it = dp[i][sum].begin(); it != dp[i][sum].end(); it++)
                            {
                                int oldMod = it->first & MASK;
                                int oldS = it->first >> OFFSET;

                                for (size_t n = 0; n < up; n++)
                                {
                                    int newSum = sum + n + preSum;
                                    if (oldS == newSum)
                                    {
                                        int newMod = (oldMod + (preVal + n) * (long long)pow(10, i)) % oldS;
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
                    for (size_t n = 0; n <= up; n++)
                    {
                        if (0 < (preSum + n) && 0 == ((preVal + n) % (preSum + n)))
                        {
                            ret++;
                        }
                    }
                }

                preSum += up;
                preVal = (preVal + up) * 10;
            }
        }

        return ret;
    }

    void dfs(vector<vector<unordered_map<int, long long>>> &dp, const string& strNum, int pos)
    {
        if (pos < strNum.length() - 1)
        {
            if (0 == pos)
            {
                for (size_t n = 0; n <= 9; n++)
                {
                    for (size_t s = 1; s < maxSum; s++)
                    {
                        int key = (s << OFFSET) | (n % s);
                        dp[pos][n][key]++;
                    }
                }
            }
            else
            {
                for (size_t sum = 0; sum < maxSum; sum++)
                {
                    dp[pos][sum] = dp[pos - 1][sum];
                }

                for (size_t sum = 0; sum < maxSum; sum++)
                {
                    if (0 < dp[pos - 1][sum].size())
                    {
                        for (unordered_map<int, long long>::iterator it = dp[pos - 1][sum].begin(); it != dp[pos - 1][sum].end(); it++)
                        {
                            int oldMod = it->first & MASK;
                            int oldS = it->first >> OFFSET;

                            for (size_t n = 1; n <= 9; n++)
                            {
                                int newSum = sum + n;
                                int newMod = (oldMod + (n * (long long)pow(10, pos))) % oldS;

                                int newKey = (oldS << OFFSET) + newMod;
                                dp[pos][newSum][newKey] += it->second;
                            }
                        }
                    }
                }
            }

            dfs(dp, strNum, pos + 1);
        }
    }
};

int main()
{
    long long l, r;
    cin >> l >> r;

    Solution s;
    cout << s.beautifulNumbers(l, r) << endl;

    return 0;
}
