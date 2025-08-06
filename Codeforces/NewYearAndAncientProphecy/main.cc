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

        const int maxLen = 5002;
        const int mod = 1000000007;

        vector< vector<int> > dp(maxLen, vector<int>(maxLen, 0));  // dp[idx][len];    string 中的 idx 位置为终点，长度 <= len 的总数和

        if ('0' != num.at(0))
        {
            for (int l = 0; l <= num.length(); l++)
            {
                dp[0][l] = 1;
            }

            for (int idx = 1; idx <= num.length(); idx++)
            {
                for (int l = 1; l <= idx; l++)
                {
                    // 比较以 idx 和 idx -l 为终点，长度为l的两个字符串
                    //                    string subStr1 = num.substr(idx - l, l);
                    char subCh1 = num.at(idx - l);

                    if ('0' != subCh1)
                    {
                        //                        string subStr2 = "0";
                        char subCh2 = '0';
                        if (0 <= idx - l - l)
                        {
                            //                            subStr2 = num.substr(idx - l - l, l);
                            subCh2 = num.at(idx - 2 * l);
                        }
                        //                        if ('0' != subStr2.at(0) && subStr2.compare(subStr1) <= 0)
                        //                        if ('0' != subCh2 && compare(num, idx - 2 * l, idx - l, l) <= 0)
                        if ('0' != subCh2 && num.compare(idx - 2 * l, l, num, idx - l, l) < 0)
                        {
                            // str2 <= str1, 有效
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
                    dp[idx][l] = dp[idx][l - 1];
                }
            }

            ret = dp[num.length()][num.length()];
        }

        return ret;
    }

private:
    int compare(string &str, int idx1, int idx2, int len)
    {
        int ret = 0;

        char ch1, ch2;
        for (size_t i = 0; i < len; i++)
        {
            ch1 = str.at(idx1 + 1);
            ch2 = str.at(idx2 + i);

            if (ch1 < ch2)
            {
                ret = -1;
                break;
            }
            else if (ch1 > ch2)
            {
                ret = 1;
                break;
            }
        }

        return ret;
    }
};

int main()
{
    int n;
    cin >> n;

    string num;
    cin >> num;

    Solution s;

    cout << s.numberOfCombinations(num) << endl;

    return 0;
}
