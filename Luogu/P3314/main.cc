// https://www.luogu.com.cn/problem/P3314

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
#define MAX_W 10
#define MAX_H 10
#define MAX_K 11
#define ST_BITS 4
#define ST_MASK 15 
#define QS_SIZE 60000
#define MOD 25619849

class Record
{
public:
    unsigned long long state; // 轮廓线段状态
    unsigned int len;
    unsigned int cnt;

    Record() {}
};

unsigned int cells[MAX_H][MAX_W];
vector<unsigned int> paths[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)                                  \
    ST &= ~(((unsigned long long)ST_MASK) << ((POS) * ST_BITS)); \
    if (VAL)                                                     \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].len = 0;
    qs[act][0].cnt = 1;

    qTail[act]++;
}

int main()
{
    int k;

    while (true)
    {
        cin >> w >> h >> k;

        if (0 == w && 0 == h && 0 == k)
        {
            break;
        }

        for (size_t row = 1; row <= h; row ++)
        {
            for (size_t col = 1; col <= w; col ++)
            {
                cin >> cells[row][col];
                paths[row][col].clear();
            }
        }

        for (size_t i = 1; i <= k; i++)
        {
            unsigned int x, y;

            cin >> x >> y;
            paths[x + 1][y + 1].push_back(i);

            cin >> x >> y;
            paths[x + 1][y + 1].push_back(i);
        }

        
    }

    return 0;
}
