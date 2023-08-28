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

inline unsigned long long setVal4St1(unsigned long long st, int pos, unsigned long long val)
{
    unsigned long long ret = st;

    ret &= ~(ST1_MASK << (pos * ST1_BITS));
    ret |= val << (pos * ST1_BITS);

    return ret;
}

inline int getVal4St2(unsigned short st, int pos)
{
    int ret = 0;

    ret = (st >> (pos * ST2_BITS)) & ST2_MASK;

    return ret;
}

inline unsigned short setVal4St2(unsigned short st, int pos, unsigned short val)
{
    unsigned short ret = st;

    ret &= ~(ST2_MASK << (pos * ST2_BITS));
    ret |= val << (pos * ST2_BITS);

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

inline int getPlugCnt(unsigned long long st, int plug)
{
    int ret = 0;

    for (size_t i = 0; i <= w; i++)
    {
        int v = getVal4St1(st, i);
        if (v == plug)
        {
            ret ++;
        } 
    }

    return ret;
}

inline unsigned long long updateSt1(unsigned long long st, int from, int to)
{
    unsigned long long ret = st;

    for (size_t i = 0; i <= w; i++)
    {
        int v = getVal4St1(ret, i);
        if (v == from)
        {
            ret = setVal4St1(ret, i, to);
        } 
    }

    return ret;
}

unsigned long long st1;
unsigned short st2;
unsigned long long cnt;
int leftPlug, upPlug;
int leftCell, leftUpCell, upCell;

inline void addSts(unsigned char blks, unsigned long long newst1, unsigned short newst2, Record &rec, int idx, int color)
{
    unsigned long long key = 0;

    key = newst2 | (newst1 << (w + 1)) | (blks << ((w + 1) * (ST1_BITS + ST2_BITS)));

    unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        // 加入队尾
        memcpy(&(qs[idx][qTail[idx]]), &rec, sizeof(Record));

        qs[idx][qTail[idx]].blocks = blks;
        qs[idx][qTail[idx]].state1 = newst1;
        qs[idx][qTail[idx]].state2 = newst2;
        qs[idx][qTail[idx]].cnt = cnt;

        qs[idx][qTail[idx]].grid[now_x - 1] &= 255 ^ (1 << (now_y - 1));
        if (color)
        {
            qs[idx][qTail[idx]].grid[now_x - 1] |= 1 << (now_y - 1);
        }

        cnts[idx][key] = qTail[idx];
        qTail[idx] ++;
    }
    else
    {
        qs[idx][it->second].cnt += cnt;
    }
}

inline void func(int color, Record &rec, int blks, int idx)
{
    if (color == leftCell && color == leftUpCell && color == upCell)
    {
        // 非法
        return;
    }

    unsigned short newSt2 = st2;
    newSt2 = setVal4St2(newSt2, now_x - 1, color);

    if (0 == leftPlug && 0 == upPlug)
    {
        // 找到最小的、未使用的
        int minUnused = getMinUnused(st1);

        // 拐角
        if (h > now_x && w > now_y)
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, minUnused);
            newSt1 = setVal4St1(newSt1, now_x, minUnused);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }

        // 向下
        if (h > now_x)
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, minUnused);
            newSt1 = setVal4St1(newSt1, now_x, 0);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }

        // 向右
        if (w > now_y)
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, 0);
            newSt1 = setVal4St1(newSt1, now_x, minUnused);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }

        // 该 cell 自成一个联通块
        {
            blks ++;
            if (2 < blks)
            {
                // 多余2个联通块，非法
                return;
            }
            else if (2 == blks && false == (h == now_x && w == now_y))
            {
                // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                return;
            }
            else
            {
                // 合法的
                unsigned long long newSt1 = st1;
                newSt1 = setVal4St1(newSt1, now_x - 1, 0);
                newSt1 = setVal4St1(newSt1, now_x, 0);

                addSts(blks, newSt1, newSt2, rec, idx, color);
            }
        }
    }
    else if (0 == leftPlug)
    {
        // 有 下 插头
        if (upCell != color)
        {
            // 非法
            return;
        }

        // 向下
        if (h > now_x)
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, upPlug);
            newSt1 = setVal4St1(newSt1, now_x, 0);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }

        // 向右
        if (w > now_y)
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, 0);
            newSt1 = setVal4St1(newSt1, now_x, upPlug);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }

        // 就此打住，可能形成一个联通块
        {
            int cnt = getPlugCnt(st1, upPlug);
            if (1 == cnt)
            {
                blks++;
                if (2 < blks)
                {
                    // 多余2个联通块，非法
                    return;
                }
                else if (2 == blks && false == (h == now_x && w == now_y))
                {
                    // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                    return;
                }
            }

            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, 0);
            newSt1 = setVal4St1(newSt1, now_x, 0);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }
    }
    else if (0 == upPlug)
    {
        // 有 左 插头
        if (leftCell != color)
        {
            // 非法
            return;
        }

        // 向下
        if (h > now_x)
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, leftPlug);
            newSt1 = setVal4St1(newSt1, now_x, 0);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }

        // 向右
        if (w > now_y)
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, 0);
            newSt1 = setVal4St1(newSt1, now_x, leftPlug);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }

        // 就此打住，可能形成一个联通块
        {
            int cnt = getPlugCnt(st1, leftPlug);
            if (1 == cnt)
            {
                blks++;
                if (2 < blks)
                {
                    // 多余2个联通块，非法
                    return;
                }
                else if (2 == blks && false == (h == now_x && w == now_y))
                {
                    // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                    return;
                }
            }

            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_x - 1, 0);
            newSt1 = setVal4St1(newSt1, now_x, 0);

            addSts(blks, newSt1, newSt2, rec, idx, color);
        }
    }
    else
    {
        // 2 个插头
        if (leftCell != upCell || color != leftCell)
        {
            // 非法
            return;
        }

        unsigned long long newSt1 = st1;
        if (leftPlug != upPlug)
        {
            newSt1 = updateSt1(newSt1, leftPlug, upPlug);
        }
        newSt1 = setVal4St1(newSt1, now_x - 1, 0);
        newSt1 = setVal4St1(newSt1, now_x, 0);

        int cnt = getPlugCnt(newSt1, upPlug);
        if (0 == cnt)
        {
            blks++;
            if (2 < blks)
            {
                // 多余2个联通块，非法
                return;
            }
            else if (2 == blks && false == (h == now_x && w == now_y))
            {
                // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                return;
            }
        }

        addSts(blks, newSt1, newSt2, rec, idx, color);
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
                unsigned char blks = qs[act][iQ].blocks;
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
                    func(BLACK, qs[act][iQ], blks, nAct);
                }
                else if ('o' == cells[now_x][now_y])
                {
                    // white
                    func(WHITE, qs[act][iQ], blks, nAct);
                }
                else
                {
                    // 任意颜色
                    func(BLACK, qs[act][iQ], blks, nAct);
                    func(WHITE, qs[act][iQ], blks, nAct);
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
