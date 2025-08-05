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
    int numberOfCombinations(string num)
    {
        int ret = 0;

        const int maxLen = 3502;
        const int mod = 1000000007;

        static int dp[maxLen][maxLen]; // dp[idx][len];    string 中的 idx 位置为终点，长度 <= len 的总数和

        if ('0' != num.at(0))
        {
            memset(dp, 0, sizeof(dp));

            for (int l = 0; l <= num.length(); l++)
            {
                dp[0][l] = 1;
            }

            for (int idx = 1; idx <= num.length(); idx++)
            {
                for (int l = 1; l <= idx; l++)
                {
                    // 比较以 idx 和 idx -l 为终点，长度为l的两个字符串
                    string subStr1 = num.substr(idx - l, l);

                    if ('0' != subStr1.at(0))
                    {
                        string subStr2 = "0";
                        if (0 <= idx - l - l)
                        {
                            subStr2 = num.substr(idx - l - l, l);
                        }
                        if ('0' != subStr2.at(0) && subStr2.compare(subStr1) <= 0)
                        {
                            // 有效
                            dp[idx][l] = dp[idx - l][l];
                        }
                        else
                        {
                            dp[idx][l] = dp[idx - l][l - 1];
                        }
                    }

                    dp[idx][l] += dp[idx][l - 1];
                    dp[idx][l] %= mod;
                }

                for (int l = idx + 1; l <= num.length(); l++)
                {
                    dp[idx][l] += dp[idx][l - 1];
                }
            }

            ret = dp[num.length()][num.length()];
        }

        return ret;
    }
};

int main()
{
    string num;
    cin >> num;

    Solution s;

    cout << s.numberOfCombinations(num) << endl;

    return 0;
}
