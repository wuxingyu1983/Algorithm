// https://codeforces.com/problemset/problem/1209/E1
// https://codeforces.com/contest/1209/problem/E2

#include <cmath>
#include <cstdio>
#include <vector>
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
#define MAX_H 12
#define MAX_W 2000

int raw[MAX_H][MAX_W];
int cells[MAX_H][MAX_H];
int dp[MAX_H][4096];
int h, w;
vector<int> subsets[4096];
vector<int> bits[4096];
int cached[4096];

void init()
{
    for (size_t i = 0; i < 4096; i++)
    {
        for (size_t j = 0; j <= i; j++)
        {
            if ((i & j) == j)
            {
                subsets[i].push_back(j);
            }
        }

        for (size_t j = 0; j < 12; j++)
        {
            if (i < (1 << j))
            {
                break;
            }
            else if ((i & (1 << j)))
            {
                bits[i].push_back(j);
            }
        }
    }
}

class colMax
{
public:
    int max;
    int col;

    colMax() {}
};

vector<colMax> colmax(4096);

bool comp(colMax &a, colMax &b)
{
    return (a.max > b.max);
}

int main()
{
    init();

    int t;
    scanf("%d", &t);

    for (size_t iT = 0; iT < t; iT++)
    {
        scanf("%d %d", &h, &w);

        for (size_t row = 0; row < h; row++)
        {
            for (size_t col = 0; col < w; col++)
            {
                scanf("%d", &(raw[row][col]));

                if (0 == row)
                {
                    colmax[col].max = raw[row][col];
                    colmax[col].col = col;
                }
                else
                {
                    if (colmax[col].max < raw[row][col])
                    {
                        colmax[col].max = raw[row][col];
                    }
                }
            }
        }

        // sort
        sort(colmax.begin(), colmax.begin() + w, comp);

        for (size_t col = 0; col < ((h > w) ? w : h); col++)
        {
            for (size_t row = 0; row < h; row++)
            {
                cells[row][col] = raw[row][colmax[col].col];
            }
        }

        // col = 0
        {
            for (size_t i = 1; i < (1 << h); i++)
            {
                int max = 0;
                for (size_t round = 0; round < h; round++)
                {
                    int tmp = 0;
                    for (vector<int>::iterator itP = bits[i].begin(); itP != bits[i].end(); itP++)
                    {
                        tmp += cells[((*itP) + round) % h][0];
                    }

                    if (max < tmp)
                    {
                        max = tmp;
                    }
                }
                dp[0][i] = max;
            }
        }

        for (size_t col = 1; col < ((h > w) ? w : h); col++)
        {
            for (size_t i = 1; i < (1 << h); i++)
            {
                int max = 0;

                for (size_t round = 0; round < h; round++)
                {
                    int tmp = 0;
                    for (vector<int>::iterator itP = bits[i].begin(); itP != bits[i].end(); itP++)
                    {
                        tmp += cells[((*itP) + round) % h][col];
                    }

                    if (max < tmp)
                    {
                        max = tmp;
                    }
                }

                cached[i] = max;
            }

            for (size_t i = 1; i < (1 << h); i++)
            {
                // dp[col][i]
                dp[col][i] = dp[col - 1][i];

                for (vector<int>::iterator it = subsets[i].begin(); it != subsets[i].end(); it++)
                {
                    if (dp[col][i] < (cached[*it] + dp[col - 1][i - *it]))
                    {
                        dp[col][i] = (cached[*it] + dp[col - 1][i - *it]);
                    }
                }
            }
        }

        printf("%d\n", dp[(h > w) ? w - 1 : h - 1][(1 << h) - 1]);
    }

    return 0;
}
