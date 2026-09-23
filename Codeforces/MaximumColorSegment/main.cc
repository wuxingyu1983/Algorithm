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

const int MAX_MN = 3001;

int sum[MAX_MN][MAX_MN];
int anes[MAX_MN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    string str;
    cin >> str;

    int ans = 1;
    
    for (int i = 1; i < n; i++)
    {
        if (str.at(i - 1) != str.at(i))
            ans ++;
    }
    
    int round = n / k;

    vector<vector<vector<int>>> dp(
        k,
        vector<vector<int>>(
            round + 1,
            vector<int>(round + 1, 0)));

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

                    for (int j = im - 2; j < ir - 1; j++)
                    {
                        dp[ik][ir][im] = max(dp[ik][ir][im], dp[ik][j][im - 1] + pre + aft);
                    }


                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
