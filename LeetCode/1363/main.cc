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
    string largestMultipleOfThree(vector<int> &digits)
    {
        string strRet = "";

        int cnt[10];
        memset(cnt, 0, sizeof(cnt));

        for (size_t i = 0; i < digits.size(); i++)
        {
            cnt[digits[i]]++;
        }

        int dp[10][3];
        memset(dp, -1, sizeof(dp)); // dp[digit][mod 3]  最大数字为 digit ，总和 mod 3 的最大长度

        dp[0][0] = cnt[0];

        for (size_t num = 1; num < 10; num++)
        {
            int n = cnt[num];
            for (int i = 0; i < 3 && n - i >= 0; i++)
            {
                for (size_t mod = 0; mod < 3; mod++)
                {
                    if (0 <= dp[num - 1][mod])
                    {
                        int newMod = (mod + (n - i) * num) % 3;
                        if (dp[num][newMod] < dp[num - 1][mod] + n - i)
                        {
                            dp[num][newMod] = dp[num - 1][mod] + n - i;
                        }
                    }
                }
            }
        }

        if (0 <= dp[9][0])
        {
            if (cnt[0] == dp[9][0] && 0 < cnt[0])
            {
                strRet = "0";
            }
            else
            {
                int mod = 0;
                for (int num = 9; num > 0; num--)
                {
                    int n = cnt[num];
                    for (int i = 0; i < 3 && n - i >= 0; i++)
                    {
                        int newMod = (mod + 6 - ((n - i) * num) % 3) % 3;
                        if (0 <= dp[num - 1][newMod] && dp[num][mod] == n - i + dp[num - 1][newMod])
                        {
                            if (0 < (n - i))
                            {
                                strRet.append(n - i, '0' + num);
                            }

                            mod = newMod;

                            break;
                        }
                    }
                }

                if (0 < cnt[0])
                {
                    strRet.append(cnt[0], '0');
                }
            }
        }

        return strRet;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> digits;
    for (size_t i = 0; i < n; i++)
    {
        int d;
        cin >> d;

        digits.push_back(d);
    }

    Solution s;
    cout << s.largestMultipleOfThree(digits) << endl;

    return 0;
}
