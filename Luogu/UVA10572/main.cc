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

#define DEBUG 0
#define MAX_MN 8
#define ST1_BITS 4
#define ST1_MASK 15
#define ST2_BITS 1
#define ST2_MASK 1
#define QS_SIZE 523114
#define ANY 2
#define BLACK 1
#define WHITE 0

class Record
{
public:
    unsigned long long state1; // 轮廓线段状态
    unsigned short state2;     // 轮廓cells状态
    unsigned long long cnt[3];

    unsigned char grid[8]; // 满足当前 state 状态下的 一组 可能的 grid

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
char cells[MAX_MN + 1][MAX_MN + 1];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2]; // key 是 blocks | st1 | st2 的组合，value 是在 qs 的下标
int act = 0;                                             // 当前生效的 map
int now_x, now_y;

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

    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].cnt[0] = 1;
    qs[act][0].cnt[1] = 0;
    qs[act][0].cnt[2] = 0;

    qTail[act]++;
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

    ret &= ~(((unsigned long long)ST1_MASK) << (pos * ST1_BITS));
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
            ret++;
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

int leftPlug, upPlug;
int leftCell, leftUpCell, upCell;

unsigned long long recode(unsigned long long st)
{
    unsigned long long ret = st;
    int now = 1;

    for (size_t i = 0; i <= w; i++)
    {
        int old = getVal4St1(ret, i);
        if (old == now)
        {
            now++;
        }
        else if (old > now)
        {
            for (size_t j = i; j <= w; j++)
            {
                int tmp = getVal4St1(ret, j);
                if (tmp == old)
                {
                    ret = setVal4St1(ret, j, now);
                }
                else if (tmp == now)
                {
                    ret = setVal4St1(ret, j, old);
                }
            }

            now++;
        }
    }

    return ret;
}

inline void addSts(unsigned long long newst1, unsigned short newst2, unsigned long long cnt0, unsigned long long cnt1, unsigned long long cnt2, Record &rec, int idx, int color)
{
    if (0 == cnt0 + cnt1 + cnt2)
    {
        return;
    }

    unsigned long long key = newst2;
    newst1 = recode(newst1);

    key |= (newst1 << (w + 1));

    int pInQ = qTail[idx];

    unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        // 加入队尾
        memcpy(&(qs[idx][pInQ]), &rec, sizeof(Record));

        qs[idx][pInQ].state1 = newst1;
        qs[idx][pInQ].state2 = newst2;
        qs[idx][pInQ].cnt[0] = cnt0;
        qs[idx][pInQ].cnt[1] = cnt1;
        qs[idx][pInQ].cnt[2] = cnt2;

        qs[idx][pInQ].grid[now_x - 1] &= 255 ^ (1 << (now_y - 1));
        if (color)
        {
            qs[idx][pInQ].grid[now_x - 1] |= 1 << (now_y - 1);
        }

        cnts[idx][key] = pInQ;
        qTail[idx]++;
    }
    else
    {
        pInQ = it->second;

        qs[idx][pInQ].cnt[0] += cnt0;
        qs[idx][pInQ].cnt[1] += cnt1;
        qs[idx][pInQ].cnt[2] += cnt2;
    }
}

inline void func(int color, Record &rec, unsigned long long st1, unsigned short st2, unsigned long long cnt0, unsigned long long cnt1, unsigned long long cnt2, int idx)
{
    if (color == leftCell && color == leftUpCell && color == upCell)
    {
        // 非法
        return;
    }

    // 2个 cell 颜色相同，他们之间一定有一个 plug

    unsigned short newSt2 = setVal4St2(st2, now_y - 1, color);

    if (0 == leftPlug && 0 == upPlug)
    {
        if (leftCell == color || upCell == color)
        {
            return;
        }

        // 找到最小的、未使用的
        int minUnused = getMinUnused(st1);

        // 拐角
        if (h > now_x && w > now_y && (1 - color) != cells[now_x + 1][now_y] && (1 - color) != cells[now_x][now_y + 1])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, minUnused);
            newSt1 = setVal4St1(newSt1, now_y, minUnused);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向下
        if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, minUnused);
            newSt1 = setVal4St1(newSt1, now_y, 0);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, minUnused);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 该 cell 自成一个联通块
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, 0);
            if (h == now_x && w == now_y)
            {
                // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                addSts(newSt1, newSt2, 0, cnt0, cnt1, rec, idx, color);
            }
            else
            {
                // 合法的
                addSts(newSt1, newSt2, 0, cnt0, 0, rec, idx, color);
            }
        }
    }
    else if (0 == leftPlug)
    {
        // 有 下 插头
        if (upCell != color || leftCell == color)
        {
            // 非法
            return;
        }

        // 拐角
        if (h > now_x && w > now_y && (1 - color) != cells[now_x + 1][now_y] && (1 - color) != cells[now_x][now_y + 1])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, upPlug);
            newSt1 = setVal4St1(newSt1, now_y, upPlug);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向下
        if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, upPlug);
            newSt1 = setVal4St1(newSt1, now_y, 0);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, upPlug);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 就此打住，可能形成一个联通块
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, 0);

            int plugCnt = getPlugCnt(st1, upPlug);
            if (1 == plugCnt)
            {
                if (h == now_x && w == now_y)
                {
                    // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                    addSts(newSt1, newSt2, 0, cnt0, cnt1, rec, idx, color);
                }
                else
                {
                    addSts(newSt1, newSt2, 0, cnt0, 0, rec, idx, color);
                }
            }
            else
            {
                addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
            }
        }
    }
    else if (0 == upPlug)
    {
        // 有 左 插头
        if (leftCell != color || color == upCell)
        {
            // 非法
            return;
        }

        // 拐角
        if (h > now_x && w > now_y && (1 - color) != cells[now_x + 1][now_y] && (1 - color) != cells[now_x][now_y + 1])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, leftPlug);
            newSt1 = setVal4St1(newSt1, now_y, leftPlug);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向下
        if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, leftPlug);
            newSt1 = setVal4St1(newSt1, now_y, 0);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, leftPlug);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 就此打住，可能形成一个联通块
        {
            unsigned long long newSt1 = st1;
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, 0);

            int plugCnt = getPlugCnt(st1, leftPlug);
            if (1 == plugCnt)
            {
                if (h == now_x && w == now_y)
                {
                    // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                    addSts(newSt1, newSt2, 0, cnt0, cnt1, rec, idx, color);
                }
                else
                {
                    addSts(newSt1, newSt2, 0, cnt0, 0, rec, idx, color);
                }
            }
            else
            {
                addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
            }
        }
    }
    else
    {
        // 2 个插头
        if (color != upCell || color != leftCell)
        {
            // 非法
            return;
        }

        unsigned long long newSt1 = st1;
        if (leftPlug != upPlug)
        {
            // leftPlug ==> upPlug
            newSt1 = updateSt1(newSt1, leftPlug, upPlug);
        }

        // 拐角
        if (h > now_x && w > now_y && (1 - color) != cells[now_x + 1][now_y] && (1 - color) != cells[now_x][now_y + 1])
        {
            newSt1 = setVal4St1(newSt1, now_y - 1, upPlug);
            newSt1 = setVal4St1(newSt1, now_y, upPlug);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向下
        if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
        {
            newSt1 = setVal4St1(newSt1, now_y - 1, upPlug);
            newSt1 = setVal4St1(newSt1, now_y, 0);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, upPlug);

            addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
        }

        // 就此打住，可能形成一个联通块
        {
            newSt1 = setVal4St1(newSt1, now_y - 1, 0);
            newSt1 = setVal4St1(newSt1, now_y, 0);

            int plugCnt = getPlugCnt(newSt1, upPlug);
            if (0 == plugCnt)
            {
                if (h == now_x && w == now_y)
                {
                    // 2 个联通块 只可能出现在 最后一个 cell，否则非法
                    addSts(newSt1, newSt2, 0, cnt0, cnt1, rec, idx, color);
                }
                else
                {
                    addSts(newSt1, newSt2, 0, cnt0, 0, rec, idx, color);
                }
            }
            else
            {
                addSts(newSt1, newSt2, cnt0, cnt1, cnt2, rec, idx, color);
            }
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
                char ch;
                cin >> ch;

                if ('#' == ch)
                {
                    cells[row][col] = BLACK;
                }
                else if ('o' == ch)
                {
                    cells[row][col] = WHITE;
                }
                else
                {
                    cells[row][col] = ANY;
                }
            }
        }

        init();
        unsigned short st2Mask = (1 << (w + 1)) - 1;

        while (0 < qTail[act])
        {
            int nAct = 1 - act;

            if (w == now_y)
            {
                now_x++;
                now_y = 1;

                if (h < now_x)
                {
                    // finished
                    unsigned long long sum = 0;
                    Record *example = NULL;

                    for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        if (0 == qs[act][iQ].state1)
                        {
                            sum += qs[act][iQ].cnt[2];
                            if (/*NULL == example &&*/ qs[act][iQ].cnt[2])
                            {
                                example = &(qs[act][iQ]);
                            }
                        }
                    }

                    // output
                    cout << sum << endl;
                    if (sum)
                    {
                        for (size_t row = 0; row < h; row++)
                        {
                            for (size_t col = 0; col < w; col++)
                            {
                                if (WHITE == (example->grid[row] & (1 << col)))
                                {
                                    cout << 'o';
                                }
                                else
                                {
                                    cout << '#';
                                }
                            }
                            cout << endl;
                        }
                    }

                    break;
                }
            }
            else
            {
                now_y++;
            }

            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st1 = qs[act][iQ].state1;
                unsigned short st2 = qs[act][iQ].state2;
                unsigned long long cnt0 = qs[act][iQ].cnt[0];
                unsigned long long cnt1 = qs[act][iQ].cnt[1];
                unsigned long long cnt2 = qs[act][iQ].cnt[2];

                if (1 == now_y)
                {
                    st1 <<= ST1_BITS;

                    st2 <<= ST2_BITS;
                    st2 &= st2Mask;
                }

                leftPlug = 0, upPlug = 0;
                leftCell = -1, leftUpCell = -1, upCell = -1;

                if (1 < now_y)
                {
                    leftPlug = getVal4St1(st1, now_y - 1);
                    leftCell = getVal4St2(st2, now_y - 2);
                }

                if (1 < now_x)
                {
                    upPlug = getVal4St1(st1, now_y);
                    upCell = getVal4St2(st2, now_y);
                }

                if (1 < now_x && 1 < now_y)
                {
                    leftUpCell = getVal4St2(st2, now_y - 1);
                }

                if (BLACK == cells[now_x][now_y])
                {
                    // black
                    func(BLACK, qs[act][iQ], st1, st2, cnt0, cnt1, cnt2, nAct);
                }
                else if (WHITE == cells[now_x][now_y])
                {
                    // white
                    func(WHITE, qs[act][iQ], st1, st2, cnt0, cnt1, cnt2, nAct);
                }
                else
                {
                    // 任意颜色
                    func(BLACK, qs[act][iQ], st1, st2, cnt0, cnt1, cnt2, nAct);
                    func(WHITE, qs[act][iQ], st1, st2, cnt0, cnt1, cnt2, nAct);
                }
            }

            // 准备下一轮
            qTail[act] = 0;
            cnts[act].clear();

            if (0 == qTail[nAct])
            {
                cout << 0 << endl;
                break;
            }

            act = nAct;
        }
    }

    return 0;
}
