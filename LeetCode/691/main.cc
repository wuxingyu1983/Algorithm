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
                    // 忽略该 string
                    if (0 > dp[i][st] || dp[i][st] > dp[i - 1][st])
                    {
                        dp[i][st] = dp[i - 1][st];
                    }

                    int newSt = st;
                    int cnt = dp[i - 1][st];

                    while (func(stickers[i - 1], target, i, newSt, cnt))
                    {
                    }
                }
            }
        }

        return dp[stickers.size()][finalSt];
    }

private:
    int **dp;
    int finalSt;

    int func(string sticker, string target, int rd, int &newSt, int &cnt)
    {
        int iRet = 0;

        for (size_t iS = 0; iS < sticker.length(); iS++)
        {
            for (size_t iT = 0; iT < target.length(); iT++)
            {
                if (0 == (newSt & (1 << iT)))
                {
                    if (sticker.at(iS) == target.at(iT))
                    {
                        newSt |= 1 << iT;
                        iRet++;

                        break;
                    }
                }
            }
        }

        if (iRet)
        {
            cnt++;
            if (0 > dp[rd][newSt] || cnt < dp[rd][newSt])
            {
                dp[rd][newSt] = cnt;
            }
        }

        return iRet;
    }
};

int main()
{
    string target;
    cin >> target;

    int n;
    cin >> n;

    vector<string> stickers;
    string str;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        stickers.push_back(str);
    }

    Solution s;
    cout << s.minStickers(stickers, target) << endl;

    return 0;
}
