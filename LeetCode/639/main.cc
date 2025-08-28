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
    int numDecodings(string s)
    {
        int ret = 0;

        const int mod = 1000000007;
        vector<long long> dp(s.length() + 1, 0);

        dp[0] = 1;

        if ('*' == s.at(0))
        {
            dp[1] = 9;
        }
        else if ('0' != s.at(0))
        {
            dp[1] = 1;
        }

        for (size_t i = 1; i < s.length(); i++)
        {
            if ('*' == s.at(i))
            {
                dp[i + 1] = dp[i] * 9;

                switch (s.at(i - 1))
                {
                case '*':
                    dp[i + 1] += dp[i - 1] * 15;
                    break;
                case '1':
                    dp[i + 1] += dp[i - 1] * 9;
                    break;
                case '2':
                    dp[i + 1] += dp[i - 1] * 6;
                    break;
                default:
                    break;
                }
            }
            else if ('0' == s.at(i))
            {
                switch (s.at(i - 1))
                {
                case '*':
                    dp[i + 1] += dp[i - 1] * 2;
                    break;
                case '1':
                    dp[i + 1] += dp[i - 1];
                    break;
                case '2':
                    dp[i + 1] += dp[i - 1];
                    break;
                default:
                    break;
                }
            }
            else
            {
                dp[i + 1] = dp[i];

                if ('*' == s.at(i - 1))
                {
                    int tmp = s.at(i) - '0';
                    if (10 + tmp <=26)
                    {
                        dp[i + 1] += dp[i - 1];
                    }
                    
                    if (20 + tmp <=26)
                    {
                        dp[i + 1] += dp[i - 1];
                    }
                }
                else
                {
                    int tmp = 10 * (s.at(i - 1) - '0') + s.at(i) - '0';
                    if (tmp <= 26 && tmp >= 10)
                    {
                        dp[i + 1] += dp[i - 1];
                    }
                }
            }
            
            dp[i + 1] %= mod;
        }
        
        ret = dp[s.length()];

        return ret;
    }
};

int main()
{
    string str;
    cin >> str;

    Solution s;
    cout << s.numDecodings(str) << endl;

    return 0;
}
