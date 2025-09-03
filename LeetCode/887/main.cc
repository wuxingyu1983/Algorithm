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
#include <unordered_map>
#include <bitset>

using namespace std;

class Solution
{
public:
    int superEggDrop(int k, int n)
    {
        int ret = 0;

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        vector<vector<int>> firstIdx(k + 1, vector<int>(n + 1, 0));

        // init
        {
            for (size_t floor = 1; floor <= n; floor++)
            {
                dp[floor][1] = floor;
                firstIdx[1][floor] = floor;
            }

            for (size_t iK = 2; iK <= k; iK++)
            {
                dp[1][iK] = 1;
                firstIdx[iK][1] = 1;
            }
        }

        for (int floor = 2; floor <= n; floor++)
        {
            for (size_t iK = 2; iK <= k; iK++)
            {
                dp[floor][iK] = -1;
                for (size_t left = 1; left <= floor && firstIdx[iK - 1][left] && firstIdx[iK - 1][left] <= floor; left++)
                {
                    int stp = firstIdx[iK - 1][left];

                    int tmp = left;
                    if (floor > stp + 1)
                    {
                        if (tmp < dp[floor - stp - 1][iK])
                        {
                            tmp = dp[floor - stp - 1][iK];
                        }
                    }

                    if (floor > stp)
                        tmp += 1;

                    if (0 > dp[floor][iK] || dp[floor][iK] > tmp)
                    {
                        dp[floor][iK] = tmp;
                    }

                    if (0 == firstIdx[iK][dp[floor][iK]])
                    {
                        firstIdx[iK][dp[floor][iK]] = floor;
                    }
                }

                {
                    int mid = floor / 2;
                    if (1 & floor)
                    {
                        mid += 1;
                    }

                    int tmp = 0;
                    if (1 < mid)
                    {
                        tmp = dp[mid - 1][iK - 1];
                    }

                    if (tmp < dp[floor - mid][iK])
                    {
                        tmp = dp[floor - mid][iK];
                    }

                    tmp += 1;

                    if (0 > dp[floor][iK] || dp[floor][iK] > tmp)
                    {
                        dp[floor][iK] = tmp;
                    }

                    if (0 == firstIdx[iK][dp[floor][iK]])
                    {
                        firstIdx[iK][dp[floor][iK]] = floor;
                    }
                }
            }
        }

        ret = dp[n][k];

        return ret;
    }
};

int main()
{
    int n, k;
    cin >> k >> n;

    Solution s;
    cout << s.superEggDrop(k, n) << endl;

    return 0;
}
