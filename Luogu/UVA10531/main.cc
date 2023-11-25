// https://www.luogu.com.cn/problem/UVA10531

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
#define MAX_H 6
#define MAX_W 7
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int total;
    unsigned int cnt[31];

    Record() {}
};

float cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state = 3;
    qs[act][0].total = 0;
    memset(qs[act][0].cnt, 0, sizeof(qs[act][0].cnt));

    qTail[act]++;
}

int main()
{
    int t;
    cin >> t;

    for (size_t iT = 0; iT < t; iT ++)
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
