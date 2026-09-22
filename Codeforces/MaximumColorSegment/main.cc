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

short dp[MAX_MN][MAX_MN];       // dp[pos][已经执行过的反转次数] = segments 个数

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    string str;
    cin >> str;

    for (int j = 0; j <= m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (i + k >= n)
            {
                break;
            }

            if (0 == j)
            {
                int pos = i;
                if (0 == pos)
                {
                    dp[i][j] += 1;
                }
                else
                {
                    if (str.at(pos - 1) != str.at(pos))
                    {
                        dp[i][j] ++;
                    }
                }

                if (pos + k < n)
                {
                    if (str.at(pos + k) != str.at(pos + k - 1))
                    {
                        dp[i][j] ++;
                    }
                }

                pos -= k;
                if (0 <= pos)
                {
                    dp[i][j] += dp[pos][j];
                }
            }
            else
            {
                if (1 == j)
                {
                }
                else
                {
                }
            }
        }
    }

    return 0;
}
