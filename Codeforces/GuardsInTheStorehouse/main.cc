// https://codeforces.com/problemset/problem/845/F
// https://www.luogu.com.cn/problem/CF845F

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
#define MAX_W 17
#define MAX_H 17
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 600000
#define MOD 1000000007

class Record
{
public:
    unsigned int state1; // 轮廓线插头状态
    unsigned int state2; // 轮廓线cell状态 
    unsigned char missed;   // 未被保护到的 cell 个数，0，1
    unsigned int cnt;

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2][2];
int act = 0; // 当前生效的 map
int now_x, now_y;

int main()
{
    cin >> h >> w;

    if (h < w)
    {
        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[col][row];
            }
        }

        swap(h, w);
    }
    else
    {
        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
            }
        }
    }

    return 0;
}
