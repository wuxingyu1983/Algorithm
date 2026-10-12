// https://atcoder.jp/contests/abc345/tasks/abc345_e

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
#include <unordered_set>
#include <unordered_map>
#include <deque>

using namespace std;

class Ball
{
public:
    int c; 
    long long v;

    Ball(int _c, long long _v) : c(_c), v(_v) {}
    Ball() : c(0), v(0) {}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<Ball> balls;
    for (int i = 0; i < n; i++)
    {
        int c;
        long long v;
        cin >> c >> v;

        if (balls.empty())
        {
            balls.push_back(Ball(c, v));
        }
        else
        {
            if (balls.back().c == c)
            {
                balls.back().v = max(balls.back().v, v);
                k--;
            }
            else
            {
                balls.push_back(Ball(c, v));
            }
        }
    }

    if (0 > k)
    {
        cout << -1 << "\n";
    }
    else
    {
        vector<vector<long long>> dp(balls.size(), vector<long long>(k + 1, 0));
        // init
        dp[0][0] = balls[0].v;
        for (int i = 1; i < balls.size(); i++)
        {
            dp[i][0] = dp[i - 1][0] + balls[i].v;
        }

        for (int i = 1; i < balls.size(); i++)
        {
            for (int ik = 1; ik <= min(k, i); ik++)
            {
                if (i == ik)
                {
                    dp[i][ik] = balls[i].v;
                }
                else
                {
                    for (int j = i - 1; j >= max(0, i - ik - 1); j--)
                    {
                        if (balls[i].c != balls[j].c && 0 < dp[j][ik - (i - j - 1)])
                        {
                            dp[i][ik] = max(dp[i][ik], dp[j][ik - (i - j - 1)] + balls[i].v);
                        }
                    }
                }
            }
        }

        cout << dp[balls.size() - 1][k] << "\n";
    }

    return 0;
}
