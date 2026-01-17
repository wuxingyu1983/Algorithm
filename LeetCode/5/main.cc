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
    string longestPalindrome(string s)
    {
        memset(dp, 0, sizeof(dp));

        int start = 0;
        int max = 1;
        int len = s.length();

        for (int pos = 0; pos < len; pos++)
        {
            dp[pos][1] = 1;
        }

        for (int step = 2; step <= len; step++)
        {
            for (int pos = 0; pos <= len - step; pos++)
            {
                if (s.at(pos) == s.at(pos + step - 1))
                {
                    if (2 == step)
                    {
                        dp[pos][step] = 1;
                        start = pos;
                        max = step;
                    }
                    else
                    {
                        dp[pos][step] = dp[pos + 1][step - 2];
                        if (1 == dp[pos][step])
                        {
                            start = pos;
                            max = step;
                        }
                    }
                }
            }
        }

        string ret(s.begin() + start, s.begin() + start + max);
        return ret;
    }

private:
    char dp[1001][1001]; // dp[pos][len]
};

int main()
{
    string str;
    cin >> str;

    Solution s;
    cout << s.longestPalindrome(str) << endl;

    return 0;
}
