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

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        // init
        mod = 1000000007;
        n = hats.size();
        int finalSt = (1 << n) - 1;
        memset(dp, -1, sizeof(dp));

        for (size_t i = 0; i < n; i++)
        {
            for (vector<int>::iterator it = hats[i].begin(); it != hats[i].end(); it++)
            {
                likes[*it].push_back(i);
            }
        }

        dp[0][0] = 1;

        for (size_t h = 1; h <= 40; h++)
        {
            for (size_t st = 0; st <= finalSt; st++)
            {
                if (0 <= dp[h -1][st])
                {
                    // 该帽子[h]不戴，直接考虑下一个帽子
                    if (0 > dp[h][st])
                    {
                        dp[h][st] = dp[h - 1][st];
                    }
                    else
                    {
                        // 0 <= dp[h][st]
                        dp[h][st] += dp[h - 1][st];
                        dp[h][st] %= mod;
                    }

                    // 尝试戴该帽子
                    for (vector<int>::iterator it = likes[h].begin(); it != likes[h].end(); it++)
                    {
                        if (0 == (st & (1 << *it)))
                        {
                            int newSt = st | (1 << *it);

                            if (0 > dp[h][newSt])
                            {
                                dp[h][newSt] = dp[h - 1][st];
                            }
                            else
                            {
                                dp[h][newSt] += dp[h - 1][st];
                                dp[h][newSt] %= mod;
                            }
                        }
                    }
                }
            }
        }
        
        return dp[40][finalSt] >= 0 ? dp[40][finalSt] : 0;
    }

private:
    int n;
    int mod;
    vector<int> likes[41];
    int dp[41][1024];
};

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> vec;

    for (size_t i = 0; i < n; i++)
    {
        vec.push_back(vector<int>());

        int hat;
        while (cin >> hat)
        {
            vec[i].push_back(hat);
            if (cin.get() == '\n')
                break;
        }
    }

    Solution s;
    cout << s.numberWays(vec) << endl;

    return 0;
}