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
    bool isMatch(string s, string p)
    {
        bool bRet = false;

        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (size_t iP = 1; iP <= p.length(); iP++)
        {
            char chP = p.at(iP - 1);
            for (size_t iS = 1; iS <= s.length(); iS++)
            {
                char chS = s.at(iS - 1);

                if ('*' == chP)
                {
                    dp[iS][iP] = dp[iS - 1][iP - 1] + dp[iS - 1][iP] + dp[iS][iP - 1];
                }
                else if ('.' == chP)
                {
                    dp[iS][iP] = dp[iS - 1][iP - 1];
                }
                else
                {
                    if (chS == chP)
                    {
                        dp[iS][iP] = dp[iS - 1][iP - 1];
                    }
                }
            }
        }

        if (dp[s.length()][p.length()])
        {
            bRet = true;
        }

        return bRet;
    }

private:
    char dp[21][21];
};

int main()
{
    string str, pat;
    cin >> str;
    cin >> pat;

    Solution s;
    if (s.isMatch(str, pat))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}
