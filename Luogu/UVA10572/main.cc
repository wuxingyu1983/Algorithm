// https://www.luogu.com.cn/problem/UVA10572

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

#define DEBUG       0
#define MAX_MN      8
#define QS_SIZE     165536

class Record
{
public:
    unsigned char blocks;               // 已经完结的联通块
    unsigned long long state1;          // 轮廓线段状态
    unsigned short state2;              // 轮廓cells状态
    unsigned long long cnt;

    unsigned char grid[8];              // 满足当前 state 状态下的 一组 可能的 grid

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
char cells[MAX_MN + 1][MAX_MN + 1];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];    // key 是 blocks | st1 | st2 的组合，value 是在 qs 的下标
int act = 0;                  // 当前生效的 map
int now_x, now_y;

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    now_x =0;
    now_y = w;

    qs[act][0].blocks = 0;
    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].cnt = 1;

    qTail[act] ++;
}

int main()
{
    int t;

    cin >> t;

    for (size_t it = 0; it < t; it++)
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

        while (0 < qTail[act])
        {
            int nAct = 1 - act;

            if (w == now_y)
            {
                now_x ++;
                now_y = 1;

                if (h < now_x)
                {
                    // finished
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
                
            }

            // 准备下一轮
            qTail[act] = 0;
            cnts[act].clear();

            act = nAct;
        }
    }

    return 0;
}
