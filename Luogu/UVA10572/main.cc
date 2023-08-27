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
#define ST1_BITS    4
#define ST1_MASK    15
#define ST2_BITS    1
#define ST2_MASK    1
#define QS_SIZE     165536
#define BLACK       1
#define WHITE       0

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

inline int getVal4St1(unsigned long long st, int pos)
{
    int ret = 0;

    ret = (st >> (pos * ST1_BITS)) & ST1_MASK;

    return ret;
}

inline int getVal4St2(unsigned short st, int pos)
{
    int ret = 0;

    ret = (st >> (pos * ST2_BITS)) & ST2_MASK;

    return ret;
}

inline int getMinUnused(unsigned long long st)
{
    int ret = 0;
    unsigned char flags[16] = {0};

    for (size_t i = 0; i <= w; i++)
    {
        int v = getVal4St1(st, i);
        flags[v] = 1;
    }

    for (size_t i = 1; i <= w; i++)
    {
        if (0 == flags[i])
        {
            ret = i;
            break;
        }
    }
    

    return ret;
}

unsigned char blks;
unsigned long long st1;
unsigned short st2;
unsigned long long cnt;
int leftPlug, upPlug;
int leftCell, leftUpCell, upCell;

inline void func(int color)
{
    if (color == leftCell && color == leftUpCell && color == upCell)
    {
        // 非法
        return;
    }

    if (0 == leftPlug && 0 == upPlug)
    {
        // 找到最小的、未使用的
        int minUnused = getMinUnused(st1);

        // 拐角
        if (h > now_x && w > now_y)
        {
        }

        // 向下
        if (h > now_x)
        {
        }

        // 向右
        if (w > now_y)
        {
        }

        // 该 cell 自成一个联通块
    }
    else if (0 == leftPlug)
    {

        // 就此打住，形成一个联通块
    }
    else if (0 == upPlug)
    {

        // 就此打住，形成一个联通块
    }
    else
    {
        // 2 个插头
        if (leftCell != upCell)
        {
            // 非法
            return;
        }
    }
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
        unsigned short st2Mask = (1 << w) - 1;

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
                blks = qs[act][iQ].blocks;
                st1 = qs[act][iQ].state1;
                st2 = qs[act][iQ].state2;
                cnt = qs[act][iQ].cnt;

                if (1 == now_y)
                {
                    st1 <<= ST1_BITS;

                    st2 <<= ST2_BITS;
                    st2 &= st2Mask;
                }

                int leftPlug = 0, upPlug = 0;
                int leftCell = -1, leftUpCell = -1, upCell = -1;

                if (1 < now_x)
                {
                    leftPlug = getVal4St1(st1, now_x - 1);
                    leftCell = getVal4St2(st2, now_x - 2);
                }

                if (1 < now_y)
                {
                    upPlug = getVal4St1(st1, now_x);
                    upCell = getVal4St2(st2, now_x);
                }

                if (1 < now_x && 1 < now_y)
                {
                    leftUpCell = getVal4St2(st2, now_x - 1);
                }

                if ('#' == cells[now_x][now_y])
                {
                    // black
                    func(BLACK);
                }
                else if ('o' == cells[now_x][now_y])
                {
                    // white
                    func(WHITE);
                }
                else
                {
                    // 任意颜色
                    func(BLACK);
                    func(WHITE);
                }
            }

            // 准备下一轮
            qTail[act] = 0;
            cnts[act].clear();

            act = nAct;
        }
    }

    return 0;
}
