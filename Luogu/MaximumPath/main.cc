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
int n;      // row
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
    now_y = 3;

    qs[act][0].state = 0;
    qs[act][0].sum = 0;

    qTail[act]++;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;

        if (3 == now_y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                // TBD
                break;
            }
        }
        else
        {
            now_y++;
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st = qs[act][iQ].state;
            long long sum = qs[act][iQ].sum;

            if (1 == now_y)
            {
                st <<= ST_BITS;
            }

            unsigned int left = getVal4St(st, now_y - 1);
            unsigned int up = getVal4St(st, now_y);

            if (1 == now_x && 1 == now_y)
            {
                // 起点
                
            }
            else if (n == now_x && 3 == now_y)
            {
                // 终点
            }
            else
            {

            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
