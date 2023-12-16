// https://codeforces.com/contest/225/problem/C

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define DEBUG 0
#define MAX_W 1001
#define MAX_H 1001
#define WHITE 0
#define BLACK 1

int h, w, x, y;
unsigned int cnts[MAX_W][2]; // 某一列 白、黑 子的个数
unsigned int sums[MAX_W][2]; // 1 - col 列 白、黑 子的总数
unsigned int mins[MAX_W][2]; // 第 col 列为全 白 或 黑 子的最小改动数目

int main()
{
    cin >> h >> w >> x >> y;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            char ch;
            cin >> ch;

            if ('.' == ch)
            {
                // white
                cnts[col][WHITE]++;
            }
            else
            {
                // black
                cnts[col][BLACK]++;
            }
        }
    }

    for (size_t col = 1; col <= w; col++)
    {
        sums[col][WHITE] = sums[col - 1][WHITE] + cnts[col][WHITE];
        sums[col][BLACK] = sums[col - 1][BLACK] + cnts[col][BLACK];

        // init
        mins[col][WHITE] = INT_MAX;
        mins[col][BLACK] = INT_MAX;
    }

    for (int col = 1; col <= w; col++)
    {
        for (int j = col - y + 1; j <= col - x + 1; j++)
        {
            if (0 < j)
            {
                // white - mins[col][WHITE]
                if (INT_MAX > mins[j - 1][BLACK])
                {
                    if (mins[col][WHITE] > (mins[j - 1][BLACK] + sums[col][WHITE] - sums[j - 1][WHITE]))
                    {
                        mins[col][WHITE] = mins[j - 1][BLACK] + sums[col][WHITE] - sums[j - 1][WHITE];
                    }
                }

                // black - mins[col][BLACK]
                if (INT_MAX > mins[j - 1][WHITE])
                {
                    if (mins[col][BLACK] > (mins[j - 1][WHITE] + sums[col][BLACK] - sums[j - 1][BLACK]))
                    {
                        mins[col][BLACK] = mins[j - 1][WHITE] + sums[col][BLACK] - sums[j - 1][BLACK];
                    }
                }
            }
        }
    }

    unsigned int ans = mins[w][WHITE];
    if (ans > mins[w][BLACK])
    {
        ans = mins[w][BLACK];
    }

    cout << ans << endl;

    return 0;
}
