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

    vector<Ball> balls(n);
    for (int i = 0; i < n; i++)
    {
        cin >> balls[i].c >> balls[i].v;
    }

    

    return 0;
}
