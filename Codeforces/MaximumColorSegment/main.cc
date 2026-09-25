// https://codeforces.com/problemset/problem/2172/L

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
#include <deque>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    string str;
    cin >> str;

    int base = 1;
    
    for (int i = 1; i < n; i++)
    {
        if (str.at(i - 1) != str.at(i))
            base ++;
    }
    
    int round = n / k;

    vector<vector<vector<int>>> dp(
        k,
        vector<vector<int>>(
            round + 1,
            vector<int>(round + 1, 0)));

    vector<vector<vector<int>>> preMax(
        k,
        vector<vector<int>>(
            round + 1,
            vector<int>(round + 1, 0)));

    vector<vector<int>> sum(
        k,
        vector<int>(m + 1, 0)
    );

    vector<vector<int>> anes(
        k,
        vector<int>(m + 1, 0)
    );

    for (int ik = 0; ik < k; ik++)
    {
        for (int ir = 0; ir < round; ir++)
        {
            int leftPos = ik + ir * k;
            int rightPos = leftPos + k - 1;
            
            if (n <= rightPos)
            {
                break;
            }

            for (int im = 1; im <= min(m, round); im++)
            {
                if (1 == im)
                {
                    if (0 < leftPos)
                    {
                        if (str.at(leftPos) == str.at(leftPos - 1))
                        {
                            dp[ik][ir][im] ++;
                        }
                        else
                        {
                            dp[ik][ir][im] --;
                        }
                    }

                    if (rightPos < n - 1)
                    {
                        if (str.at(rightPos) == str.at(rightPos + 1))
                        {
                            dp[ik][ir][im] ++;
                        }
                        else
                        {
                            dp[ik][ir][im] --;
                        }
                    }

                    sum[ik][im] = max(sum[ik][im], dp[ik][ir][im]);
                    if (0 == ir)
                        preMax[ik][ir][im] = dp[ik][ir][im];
                    else
                        preMax[ik][ir][im] = max(preMax[ik][ir - 1][im], dp[ik][ir][im]);
                }
                else
                {
                    if (ir + 1 >= im)
                    {
                        dp[ik][ir][im] = dp[ik][ir - 1][im - 1];

                        if (str.at(leftPos) == str.at(leftPos - 1))
                        {
                            dp[ik][ir][im] --;
                        }
                        else
                        {
                            dp[ik][ir][im] ++;
                        }

                        if (rightPos < n - 1)
                        {
                            if (str.at(rightPos) == str.at(rightPos + 1))
                            {
                                dp[ik][ir][im]++;
                            }
                            else
                            {
                                dp[ik][ir][im]--;
                            }
                        }
                    }

                    int pre = 0;
                    if (0 < leftPos)
                    {
                        if (str.at(leftPos) == str.at(leftPos - 1))
                        {
                            pre = 1;
                        }
                        else
                        {
                            pre = -1;
                        }
                    }
                    int aft = 0;
                    if (rightPos < n - 1)
                    {
                        if (str.at(rightPos) == str.at(rightPos + 1))
                        {
                            aft = 1;
                        }
                        else
                        {
                            aft = -1;
                        }
                    }

                    if (1 < ir)
                    {
                        dp[ik][ir][im] = max(dp[ik][ir][im], preMax[ik][ir - 2][im - 1] + pre + aft);
                    }
                    sum[ik][im] = max(sum[ik][im], dp[ik][ir][im]);
                    if (0 == ir)
                        preMax[ik][ir][im] = dp[ik][ir][im];
                    else
                        preMax[ik][ir][im] = max(preMax[ik][ir - 1][im], dp[ik][ir][im]);
                }
            }
        }
    }

    int ans = 0;
    if (0 < m)
    {
        for (int ik = 0; ik < k; ik++)
        {
            for (int j = m; j >= 0; j--)
            {
                if (0 == ik)
                {
                    anes[ik][j] = sum[ik][j];
                    ans = max(ans, anes[ik][j]);
                }
                else
                {
                    for (int l = m; l >= 0; l--)
                    {
                        if (j + l <= m)
                        {
                            anes[ik][j + l] = max(anes[ik][j + l], sum[ik][j] + anes[ik - 1][l]);
                            ans = max(ans, anes[ik][j + l]);
                        }
                    }
                }
            }
        }
    }

    cout << ans + base << "\n";

    return 0;
}
