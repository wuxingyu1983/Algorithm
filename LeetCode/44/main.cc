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

        char dp[2001][2001];
        memset(dp, 0, 2001 * 2001);
        dp[0][0] = 1;

        int len_s = s.length();
        int len_p = p.length();

        for (size_t iP = 1; iP <= len_p; iP++)
        {
            char chP = p.at(iP - 1);

            // iS = 0
            if ('*' == chP)
            {
                dp[iP][0] = dp[iP - 1][0];
            }

            for (size_t iS = 1; iS <= len_s; iS++)
            {
                if ('?' == chP)
                {
                    dp[iP][iS] = dp[iP - 1][iS - 1];
                }
                else if ('*' == chP)
                {
                    dp[iP][iS] = dp[iP - 1][iS - 1] | dp[iP][iS - 1] | dp[iP - 1][iS];
                }
                else
                {
                    if (chP == s.at(iS - 1))
                    {
                        dp[iP][iS] = dp[iP - 1][iS - 1];
                    }
                    else
                    {
                        dp[iP][iS] = 0;
                    }
                }
            }
        }

        if (dp[len_p][len_s])
        {
            bRet = true;
        }

        return bRet;
    }
};

int main()
{
    string s, p;

    cin >> s;
    cin >> p;

    Solution sol;

    if (sol.isMatch(s, p))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}
