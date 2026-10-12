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
    int c, v;

    Ball(int _c, int _v) : c(_c), v(_v) {}
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
        int c, v;
        cin >> c >> v;

        if (balls.empty())
        {
            balls.push_back(Ball(c, v));
        }
        else
        {
            if (balls.back().c == c)
            {
                balls.back().v += max(balls.back().v, v);
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
    }

    return 0;
}
