// https://www.luogu.com.cn/problem/AT_abc211_e

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
#define MAX_NK 9
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态

    unsigned int minUnused;

    Record() {}
};

char cells[MAX_NK][MAX_NK];
Record qs[2][QS_SIZE];
int qTail[2];
int n, k;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

// 最小表示法重编码
#define recode(ST, UNUSED)             \
    int bb[10];                        \
    memset(bb, -1, sizeof(bb));        \
    int bn = 1;                        \
    bb[0] = 0;                         \
    for (int i = 0; i <= n; i++)       \
    {                                  \
        int tmp = getVal4St(ST, i);    \
        if (tmp)                       \
        {                              \
            if (0 > bb[tmp])           \
            {                          \
                bb[tmp] = bn++;        \
            }                          \
            setVal4St(ST, i, bb[tmp]); \
        }                              \
    }                                  \
    UNUSED = bn;

int main()
{
    cin >> n;
    cin >> k;

    for (size_t row = 1; row <= n; row++)
    {
        for (size_t col = 1; col <= n; col++)
        {
            cin >> cells[row][col];
        }
    }

    return 0;
}