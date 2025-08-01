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
    string largestPalindrome(int n, int k)
    {
        string str;

        const int maxN = 100002;
        
        int rmds[maxN];
        memset(rmds, -1, sizeof(rmds));

        int tmp = 1;
        for (size_t i = 0; i < n; i++)
        {
            rmds[i] = tmp % k;
            tmp = (10 * tmp) % k;
        }

        int dp[maxN][9];
        memset(dp, -1, sizeof(dp));

        int idx;
        if (n % 2)
        {
            idx = (n - 1) / 2;

            for (size_t i = 0; i < 10; i++)
            {
                int rd = i * rmds[idx] % k;
                dp[idx][rd] = i;
            }
        }
        else
        {
            idx = n / 2;

            for (size_t i = 0; i < 10; i++)
            {
                int rd = i * (rmds[i] * rmds[i - 1]) % k;
                dp[idx][rd] = i;
            }
        }

        for (size_t i = idx + 1; i < n; i++)
        {
            for (size_t num = 0; num < 10; num++)
            {
                int rd = num * (rmds[i] + rmds[n - 1 - i]) % k;

                for (size_t r = 0; r < 9; r++)
                {
                    if (0 <= dp[i - 1][r])
                    {
                        dp[i][(rd + r) % k] = num;
                    }
                }
            }
        }

        return str;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;

    Solution s;
    
    cout << s.largestPalindrome(n, k) << endl;

    return 0;
}
