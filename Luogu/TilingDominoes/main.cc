// https://www.luogu.com.cn/problem/UVA11270
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2245

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
#define MAX_MN 101
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 2100

class Record
{
public:
    unsigned short state; // 轮廓线段状态
    unsigned long long count;

    Record() {}
};

long long cells[MAX_MN][MAX_MN];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned short, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long ans;

int main()
{
    while (cin >> h >> w)
    {
        if (h < w)
        {
            swap(h, w);
        }

        // init
        act = 0;

        now_x = 0;
        now_y = w;

        qs[act][0].state = 0;
        qs[act][0].count = 1;

        qTail[0] = 1;
        qTail[1] = 0;

        
    }

    return 0;
}
