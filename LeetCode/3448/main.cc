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
    long long countSubstrings(string s)
    {
        long long ret = 0;

        vector<vector<long long>> dp(s.length(), vector<long long>(81, 0));

        int digit = s.at(0) - '0';
        for (size_t num = 1; num <= 9; num++)
        {
            dp[0][(num - 1) * 9 + digit % num]++;
        }

        if (0 < digit)
        {
            ret += dp[0][(digit - 1) * 9];
        }

        for (size_t i = 1; i < s.length(); i++)
        {
            int digit = s.at(i) - '0';

            for (size_t num = 1; num <= 9; num++)
            {
                dp[i][(num - 1) * 9 + digit % num]++;

                for (size_t oldMod = 0; oldMod < num; oldMod++)
                {
                    if (0 < dp[i - 1][(num - 1) * 9 + oldMod])
                    {
                        int newMod = (oldMod * 10 + digit) % num;
                        dp[i][(num - 1) * 9 + newMod] += dp[i - 1][(num - 1) * 9 + oldMod];
                    }
                }
            }

            if (0 < digit)
            {
                ret += dp[i][(digit - 1) * 9];
            }
        }

        return ret;
    }
};

int main()
{
    string str;
    cin >> str;

    Solution s;

    cout << s.countSubstrings(str) << endl;

    return 0;
}
