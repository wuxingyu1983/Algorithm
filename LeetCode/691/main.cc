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
    int minStickers(vector<string> &stickers, string target)
    {
        // init
        finalSt = (1 << target.length()) - 1;
        dp = new int *[stickers.size() + 1];
        for (size_t i = 0; i <= stickers.size(); i++)
        {
            dp[i] = new int[finalSt + 1];
            memset(dp[i], -1, sizeof(int) * (finalSt + 1));
        }
        dp[0][0] = 0;

        for (size_t i = 1; i <= stickers.size(); i++)
        {
            for (size_t st = 0; st <= finalSt; st++)
            {
                if (0 <= dp[i - 1][st])
                {
                    
                }
            }
        }

        return dp[stickers.size()][finalSt];
    }

private:
    int **dp;
    int finalSt;
};

int main()
{
    string target;
    cin >> target;

    vector<string> stickers;
    string str;
    while (cin >> str)
    {
        stickers.push_back(str);
        if (cin.get() == '\n')
            break;
    }

    Solution s;
    cout << s.minStickers(stickers, target) << endl;

    return 0;
}
