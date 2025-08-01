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
        memset(rmds, 0, sizeof(rmds));

        int tmp = 1;
        for (size_t i = 0; i < n; i++)
        {
            rmds[i] = tmp % k;
            tmp = (10 * tmp) % k;
        }

        int dp[maxN][9];
        memset(dp, 0, sizeof(dp));

        int idx;
        if (n % 2)
        {
            idx = (n - 1) / 2;

            for (size_t i = 1; i < 10; i++)
            {
                int rd = i * rmds[idx] % k;
                dp[idx][rd] = i;
            }
            

        }
        else
        {
            idx = n / 2;

            for (size_t i = 1; i < 10; i++)
            {
                int rd = i * (rmds[i] * rmds[i - 1]) % k;
                dp[idx][rd] = i;
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
