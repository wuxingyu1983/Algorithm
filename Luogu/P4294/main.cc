// https://www.luogu.com.cn/problem/P4294

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
#define MAX_W 11 
#define MAX_H 11
#define ST_BITS 3
#define ST_MASK 15
#define QS_SIZE 600000

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

class Record
{
public:
    unsigned int state; // 轮廓线cell状态
    unsigned int cnt;
    char recd[MAX_H][MAX_W];

    unsigned char minUnused;

    Record() {}
};

int cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

// 最小表示法重编码
#define recode(NEWST, ST, UNUSED)                 \
    int bb[10];                                   \
    memset(bb, -1, sizeof(bb));                   \
    int bn = 1;                                   \
    bb[0] = 0;                                    \
    for (int i = 0; i <= w; i++)                  \
    {                                             \
        int tmp = getVal4St1(ST, i);              \
        if (tmp)                                  \
        {                                         \
            if (0 > bb[tmp])                      \
            {                                     \
                bb[tmp] = bn++;                   \
            }                                     \
            setVal4St1(NEWST, NEWST, i, bb[tmp]); \
        }                                         \
    }                                             \
    UNUSED = bn;

void init()
{
    act = 0;
    
    now_x = 0;
    now_y = w;

    qs[act][0].minUnused = 1;

    qTail[act]++;
}

int main()
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



    return 0;
}
