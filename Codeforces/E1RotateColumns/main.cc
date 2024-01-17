// https://codeforces.com/problemset/problem/1209/E1

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

        // init
        if (0 < iT)
        {
            memset(dp, 0, sizeof(dp));
        }

        // sort
        sort(colmax.begin(), colmax.begin() + w, comp);
        
        for (size_t col = 0; col < (h > w) ? w : h; col++)
        {
            for (size_t row = 0; row < h; row++)
            {
                cells[row][col] = raw[row][colmax[col].col];
            }
        }
        

//        printf("%d\n", ans);
    }

    return 0;
}
