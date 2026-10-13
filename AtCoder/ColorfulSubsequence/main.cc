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

class Item
{
public:
    long long fstV, sndV;
    int fstC, sndC;

    Item(long long _fstV, long long _sndV, int _fstC, int _sndC) : fstV(_fstV), sndV(_sndV), fstC(_fstC), sndC(_sndC) {}
    Item() : fstV(-1), sndV(-1), fstC(-1), sndC(-1) {}
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
        vector<vector<Item>> dp(2, vector<Item>(k + 1));

        Item initItem;
        int act = 0;

        // init
        dp[act][0].fstC = balls[0].c;
        dp[act][0].fstV = balls[0].v;

        if (0 < k)
        {
            dp[act][1].fstC = 0;
            dp[act][1].fstV = 0;
        }

        act = 1 - act;

        for (int i = 2; i <= balls.size(); i++)
        {
            fill(dp[act].begin(), dp[act].end(), initItem);

            for (int j = 0; j <= min(k, i); j++)
            {
                // dp[i][j], balls[i - 1]
                if (j > 0)
                {
                    // balls[i - 1] 删掉
                    dp[act][j].fstV = dp[1 - act][j - 1].fstV;
                    dp[act][j].fstC = dp[1 - act][j - 1].fstC;
                    dp[act][j].sndV = dp[1 - act][j - 1].sndV;
                    dp[act][j].sndC = dp[1 - act][j - 1].sndC;

                    // balls[i - 1] 保留
                    long long newV = -1;
                    if (0 <= dp[1 - act][j].fstV && dp[1 - act][j].fstC != balls[i - 1].c)
                    {
                        newV = dp[1 - act][j].fstV + balls[i - 1].v;
                    }
                    else if (0 <= dp[1 - act][j].sndV && dp[1 - act][j].sndC != balls[i - 1].c)
                    {
                        newV = dp[1 - act][j].sndV + balls[i - 1].v;
                    }

                    if (0 <= newV)
                    {
                        if (newV >= dp[act][j].fstV)
                        {
                            if (dp[act][j].fstC != balls[i - 1].c)
                            {
                                dp[act][j].sndV = dp[act][j].fstV;
                                dp[act][j].sndC = dp[act][j].fstC;
                            }

                            dp[act][j].fstV = newV;
                            dp[act][j].fstC = balls[i - 1].c;
                        }
                        else if (newV > dp[act][j].sndV && dp[act][j].fstC != balls[i - 1].c)
                        {
                            dp[act][j].sndV = newV;
                            dp[act][j].sndC = balls[i - 1].c;
                        }
                    }
                }
                else
                {
                    // 0 == j
                    dp[act][j].fstV = dp[1 - act][j].fstV + balls[i - 1].v;
                    dp[act][j].fstC = balls[i - 1].c;
                }
            }

            if (i != balls.size())
            {
                act = 1 - act;
            }
        }

        cout << dp[act][k].fstV << "\n";
    }

    return 0;
}
