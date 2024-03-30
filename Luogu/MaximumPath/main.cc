// https://www.luogu.com.cn/problem/CF762D
// https://codeforces.com/problemset/problem/762/D

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
#define MAX_N 100001
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 6000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    long long sum;

    Record() {}
};

long long cells[MAX_N][4];
Record qs[2][QS_SIZE];
int qTail[2];
int n;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;
long long ans;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

int main()
{
    cin >> n;

    for (size_t col = 1; col <= 3; col++)
    {
        for (size_t row = 1; row <= n; row++)
        {
            cin >> cells[row][col];
        }
    }

    // init
    ans = 0;

    act = 0;

    now_x = 0;
    now_y = n;

    qs[act][0].state = 0;
    qs[act][0].sum = 0;

    qTail[act]++;



    return 0;
}
