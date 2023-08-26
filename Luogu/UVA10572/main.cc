// https://www.luogu.com.cn/problem/UVA10572

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
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

#define DEBUG       0
#define MAX_MN      8

class Record
{
public:
    unsigned long long state1;          // 轮廓线段状态
    unsigned short state2;              // 轮廓cells状态
    unsigned long long cnt;

    unsigned char grid[8];              // 满足当前 state 状态下的 一组 可能的 grid

    Record() {}
};

char cells[MAX_MN + 1][MAX_MN + 1];
int h, w;

void init()
{
    // 每一个 test 前，初始化

}

int main()
{
    int t;

    cin >> t;

    for (size_t it = 0; it < t; it++)
    {
        cin >> h >> w;

        for (size_t row = 1; row <= h; row ++)
        {
            for (size_t col = 1; col <= w; col ++)
            {
                cin >> cells[row][col];
            }
        }

        
    }
    

    return 0;
}
