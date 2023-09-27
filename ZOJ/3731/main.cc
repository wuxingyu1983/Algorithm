// https://pintia.cn/problem-sets/91827364500/exam/problems/91827369576?type=7&page=27

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

#define DEBUG   0
#define MAX_H   21
#define MAX_W   11

int h, w;
char cells[MAX_H][MAX_W];
int first_start, first_end;
int last_start, last_end;
int ans;

inline void init()
{
    ans = -1;

    first_start = last_start = 1;
    first_end = last_end = w;

    for (size_t col = 1; col <= w; col++)
    {
        if ('W' == cells[1][col])
        {
            first_start = col + 1;
        }
        
        if ('W' == cells[h][col])
        {
            last_start = col + 1;
        }
    }

    for (size_t col = w; col >= 1; col--)
    {
        if ('L' == cells[1][col])
        {
            first_end = col - 1;
        }

        if ('L' == cells[h][col])
        {
            last_end = col - 1;
        }
    }
}

int main()
{
    while (true)
    {
        cin >> h >> w;

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
            }
        }

        init();

        if (first_start <= first_end && last_start <= last_end)
        {
            
        }

        cout << ans << endl;
    }

    return 0;
}