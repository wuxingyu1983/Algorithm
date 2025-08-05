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

        const int maxLen = 3500;
        const int mod = 1000000007;

        int dp[maxLen][maxLen];
        memset(dp, 0, sizeof(dp));



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
