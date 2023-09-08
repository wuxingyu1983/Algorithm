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
#define QS_SIZE 60000
#define ANY 2
#define BLACK 1
#define WHITE 0

class Record
{
public:
    unsigned long long state1; // 轮廓线段状态
    unsigned short state2;     // 轮廓cells状态
    unsigned long long cnt;

    unsigned char grid[8]; // 满足当前 state 状态下的 一组 可能的 grid
    unsigned char minUnused;

    Record()
    {
        minUnused = 1;
    }
};

Record qs[2][QS_SIZE];
int qTail[2];
char cells[MAX_MN + 1][MAX_MN + 1];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2][512];
int act = 0;                                             // 当前生效的 map
int now_x, now_y;
unsigned long long sum;
unsigned char example[8];

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;
    sum = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    for (int i = (1 << (w + 1)) - 1; i >= 0; i--)
    {
        cnts[0][i].clear();
        cnts[1][i].clear();
    }

    now_x = 0;
    now_y = w;

    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].cnt = 1;
    qs[act][0].minUnused = 1;

    qTail[act]++;
}

#define getVal4St1(ST, POS) ((ST) >> ((POS) * ST1_BITS)) & ST1_MASK

#define setVal4St1(NEW, OLD, POS, VAL)                            \
    NEW = OLD;                                                    \
    NEW &= ~(((unsigned long long)ST1_MASK) << ((POS)*ST1_BITS)); \
    NEW |= ((unsigned long long)(VAL)) << ((POS)*ST1_BITS);

#define getVal4St2(ST, POS) ((ST) >> ((POS) * ST2_BITS)) & ST2_MASK

#define setVal4St2(NEW, OLD, POS, VAL)      \
    NEW = OLD;                              \
    NEW &= ~(ST2_MASK << ((POS)*ST2_BITS)); \
    NEW |= (VAL) << ((POS)*ST2_BITS);

#define getPlugCnt(CNT, ST, PLUG)        \
    for (size_t i = 0; i <= w; i++)      \
    {                                    \
        if (PLUG == (getVal4St1(ST, i))) \
        {                                \
            CNT++;                       \
        }                                \
    }

int leftPlug, upPlug;
int leftCell, upCell;

class Key
{
public:
    unsigned long long key;
    unsigned char minUnused;

    Key(){}
};

unordered_map<unsigned long long, Key> keyMap;

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

inline void addSts(unsigned long long st1, unsigned short st2, unsigned long long cnt, Record &rec, int idx, int color)
{
    unsigned long long newst1 = 0;
    unsigned char minUnused = 1;

    unordered_map<unsigned long long, Key>::iterator itK = keyMap.find(st1);
    if (itK == keyMap.end())
    {
        recode(newst1, st1, minUnused)

        Key elem;
        elem.key = newst1;
        elem.minUnused = minUnused;
        keyMap[st1] = elem;
    }
    else
    {
        newst1 = itK->second.key;
        minUnused = itK->second.minUnused;
    }

    unsigned long long key = newst1;

    unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx][st2].find(key);
    if (it == cnts[idx][st2].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state1 = newst1;
        qs[idx][pInQ].state2 = st2;
        qs[idx][pInQ].cnt = cnt;
        qs[idx][pInQ].minUnused = minUnused;

        memcpy(qs[idx][pInQ].grid, rec.grid, 8);
        qs[idx][pInQ].grid[now_x - 1] &= 255 ^ (1 << (now_y - 1));
        if (color)
        {
            qs[idx][pInQ].grid[now_x - 1] |= 1 << (now_y - 1);
        }

        cnts[idx][st2][key] = pInQ;
        qTail[idx]++;
    }
    else
    {
        qs[idx][it->second].cnt += cnt;
    }
}

inline bool checkValid(int color, unsigned long long st1, unsigned short st2)
{
    bool ret = true;

    // 判断 now_x 行 now_y + 1 到 w
    for (size_t y = now_y + 1; y <= w; y++)
    {
        if (color == cells[now_x][y])
        {
            return false;
        }

        int plug = getVal4St1(st1, y);
        int cell = getVal4St2(st2, y);

        if (plug)
        {
            if (color == cell)
            {
                return false;
            }
        }
        else
        {
            // plug == 0
            if (1 - color == cell)
            {
                return false;
            }
        }
    }

    if (h > now_x)
    {
        // 判断 now_x + 1 行
        for (size_t y = 1; y < now_y; y++)
        {
            if (color == cells[now_x + 1][y])
            {
                return false;
            }

            int plug = getVal4St1(st1, y - 1);
            int cell = getVal4St2(st2, y - 1);

            if (plug)
            {
                if (color == cell)
                {
                    return false;
                }
            }
            else
            {
                // plug == 0
                if (1 - color == cell)
                {
                    return false;
                }
            }
        }

        for (size_t y = now_y; y <= w; y++)
        {
            if (color == cells[now_x + 1][y])
            {
                return false;
            }
        }
    }

    return ret;
}

inline void func(int color, Record &rec, unsigned long long st1, unsigned short st2, unsigned long long cnt, unsigned char minUnused, int idx)
{
    // 2个 cell 颜色相同，他们之间一定有一个 plug
    unsigned short newSt2 = st2;
    setVal4St2(newSt2, st2, now_y - 1, color);

    int rightPlug = 0;
    int rightCell = -1;
    if (w > now_y && 1 < now_x)
    {
        rightPlug = getVal4St1(st1, now_y + 1);
        rightCell = getVal4St2(st2, now_y + 1);
    }

    if (0 == leftPlug && 0 == upPlug)
    {
        if (leftCell == color || upCell == color)
        {
            return;
        }

        // 拐角
        if (h > now_x && w > now_y && (1 - color) != cells[now_x + 1][now_y] && (1 - color) != cells[now_x][now_y + 1])
        {
            if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
            {
                unsigned long long newSt1 = st1;
                setVal4St1(newSt1, newSt1, now_y - 1, minUnused);
                setVal4St1(newSt1, newSt1, now_y, minUnused);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 向下
        if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
        {
            unsigned long long newSt1 = st1;
            setVal4St1(newSt1, newSt1, now_y - 1, minUnused);
            setVal4St1(newSt1, newSt1, now_y, 0);

            addSts(newSt1, newSt2, cnt, rec, idx, color);
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
            {
                unsigned long long newSt1 = st1;
                setVal4St1(newSt1, newSt1, now_y - 1, 0);
                setVal4St1(newSt1, newSt1, now_y, minUnused);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 该 cell 自成一个联通块
        {
            if (h > now_x && color == cells[now_x + 1][now_y])
            {
                return;
            }
            if (w > now_y && color == cells[now_x][now_y + 1])
            {
                return;
            }

            // 合法的
            if (h == now_x || (h - 2 < now_x && w - 2 < now_y))
            {
                if (checkValid(color, st1, st2))
                {
                    if (0 == sum)
                    {
                        memcpy(example, rec.grid, 8);
                        example[now_x - 1] &= 255 ^ (1 << (now_y - 1));
                        if (color)
                        {
                            example[now_x - 1] |= 1 << (now_y - 1);
                        }

                        for (size_t y = now_y; y < w; y++)
                        {
                            example[now_x - 1] &= 255 ^ (1 << y);
                            if (1 - color)
                            {
                                example[now_x - 1] |= 1 << y;
                            }
                        }

                        if (h > now_x)
                        {
                            if (1 - color)
                            {
                                example[h - 1] = 255;
                            }
                            else
                            {
                                example[h - 1] = 0;
                            }
                        }
                    }
                    sum += cnt;
                }
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
            if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
            {
                unsigned long long newSt1 = st1;
                setVal4St1(newSt1, newSt1, now_y - 1, upPlug);
                setVal4St1(newSt1, newSt1, now_y, upPlug);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 向下
        if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
        {
            unsigned long long newSt1 = st1;
            setVal4St1(newSt1, newSt1, now_y - 1, upPlug);
            setVal4St1(newSt1, newSt1, now_y, 0);

            addSts(newSt1, newSt2, cnt, rec, idx, color);
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
            {
                unsigned long long newSt1 = st1;
                setVal4St1(newSt1, newSt1, now_y - 1, 0);
                setVal4St1(newSt1, newSt1, now_y, upPlug);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 就此打住，可能形成一个联通块
        {
            if (h > now_x && color == cells[now_x + 1][now_y])
            {
                return;
            }
            if (w > now_y && color == cells[now_x][now_y + 1])
            {
                return;
            }

            unsigned long long newSt1 = st1;
            setVal4St1(newSt1, newSt1, now_y - 1, 0);
            setVal4St1(newSt1, newSt1, now_y, 0);

            int plugCnt = 0;
            getPlugCnt(plugCnt, st1, upPlug)
            if (1 == plugCnt)
            {
                if (h == now_x || (h - 2 < now_x && w - 2 < now_y))
                {
                    if (checkValid(color, st1, st2))
                    {
                        if (0 == sum)
                        {
                            memcpy(example, rec.grid, 8);
                            example[now_x - 1] &= 255 ^ (1 << (now_y - 1));
                            if (color)
                            {
                                example[now_x - 1] |= 1 << (now_y - 1);
                            }

                            for (size_t y = now_y; y < w; y++)
                            {
                                example[now_x - 1] &= 255 ^ (1 << y);
                                if (1 - color)
                                {
                                    example[now_x - 1] |= 1 << y;
                                }
                            }

                            if (h > now_x)
                            {
                                if (1 - color)
                                {
                                    example[h - 1] = 255;
                                }
                                else
                                {
                                    example[h - 1] = 0;
                                }
                            }
                        }
                        sum += cnt;
                    }
                }
            }
            else
            {
                addSts(newSt1, newSt2, cnt, rec, idx, color);
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

        int lleftPlug = 0;
        if (1 < now_y)
        {
            lleftPlug = getVal4St1(st1, now_y - 2);
        }

        if (0 == lleftPlug)
        {
            // 拐角
            if (h > now_x && w > now_y && (1 - color) != cells[now_x + 1][now_y] && (1 - color) != cells[now_x][now_y + 1])
            {
                if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
                {
                    unsigned long long newSt1 = st1;
                    setVal4St1(newSt1, newSt1, now_y - 1, leftPlug);
                    setVal4St1(newSt1, newSt1, now_y, leftPlug);

                    addSts(newSt1, newSt2, cnt, rec, idx, color);
                }
            }

            // 向下
            if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
            {
                unsigned long long newSt1 = st1;
                setVal4St1(newSt1, newSt1, now_y - 1, leftPlug);
                setVal4St1(newSt1, newSt1, now_y, 0);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
            {
                unsigned long long newSt1 = st1;
                setVal4St1(newSt1, newSt1, now_y - 1, 0);
                setVal4St1(newSt1, newSt1, now_y, leftPlug);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 就此打住，可能形成一个联通块
        {
            if (h > now_x && color == cells[now_x + 1][now_y])
            {
                return;
            }
            if (w > now_y && color == cells[now_x][now_y + 1])
            {
                return;
            }

            unsigned long long newSt1 = st1;
            setVal4St1(newSt1, newSt1, now_y - 1, 0);
            setVal4St1(newSt1, newSt1, now_y, 0);

            int plugCnt = 0;
            getPlugCnt(plugCnt, st1, leftPlug)
            if (1 == plugCnt)
            {
                if (h == now_x || (h - 2 < now_x && w - 2 < now_y))
                {
                    if (checkValid(color, st1, st2))
                    {
                        if (0 == sum)
                        {
                            memcpy(example, rec.grid, 8);
                            example[now_x - 1] &= 255 ^ (1 << (now_y - 1));
                            if (color)
                            {
                                example[now_x - 1] |= 1 << (now_y - 1);
                            }

                            for (size_t y = now_y; y < w; y++)
                            {
                                example[now_x - 1] &= 255 ^ (1 << y);
                                if (1 - color)
                                {
                                    example[now_x - 1] |= 1 << y;
                                }
                            }

                            if (h > now_x)
                            {
                                if (1 - color)
                                {
                                    example[h - 1] = 255;
                                }
                                else
                                {
                                    example[h - 1] = 0;
                                }
                            }
                        }
                        sum += cnt;
                    }
                }
            }
            else
            {
                addSts(newSt1, newSt2, cnt, rec, idx, color);
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
            for (size_t i = 0; i <= w; i++)
            {
                int v = getVal4St1(newSt1, i);
                if (v == leftPlug)
                {
                    setVal4St1(newSt1, newSt1, i, upPlug);
                }
            }
        }

        int lleftPlug = 0;
        if (1 < now_y)
        {
            lleftPlug = getVal4St1(st1, now_y - 2);
        }

        if (0 == lleftPlug)
        {
            // 拐角
            if (h > now_x && w > now_y && (1 - color) != cells[now_x + 1][now_y] && (1 - color) != cells[now_x][now_y + 1])
            {
                if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
                {
                    setVal4St1(newSt1, newSt1, now_y - 1, upPlug);
                    setVal4St1(newSt1, newSt1, now_y, upPlug);

                    addSts(newSt1, newSt2, cnt, rec, idx, color);
                }
            }

            // 向下
            if (h > now_x && (1 - color) != cells[now_x + 1][now_y])
            {
                setVal4St1(newSt1, newSt1, now_y - 1, upPlug);
                setVal4St1(newSt1, newSt1, now_y, 0);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 向右
        if (w > now_y && (1 - color) != cells[now_x][now_y + 1])
        {
            if (0 > rightCell || (rightPlug && rightCell == color) || (0 == rightPlug && (1 - color) == rightCell))
            {
                setVal4St1(newSt1, newSt1, now_y - 1, 0);
                setVal4St1(newSt1, newSt1, now_y, upPlug);

                addSts(newSt1, newSt2, cnt, rec, idx, color);
            }
        }

        // 就此打住，可能形成一个联通块
        {
            if (h > now_x && color == cells[now_x + 1][now_y])
            {
                return;
            }
            if (w > now_y && color == cells[now_x][now_y + 1])
            {
                return;
            }

            setVal4St1(newSt1, newSt1, now_y - 1, 0);
            setVal4St1(newSt1, newSt1, now_y, 0);

            int plugCnt = 0;
            getPlugCnt(plugCnt, newSt1, upPlug)
            if (0 == plugCnt)
            {
                if (h == now_x || (h - 2 < now_x && w - 2 < now_y))
                {
                    if (checkValid(color, st1, st2))
                    {
                        if (0 == sum)
                        {
                            memcpy(example, rec.grid, 8);
                            example[now_x - 1] &= 255 ^ (1 << (now_y - 1));
                            if (color)
                            {
                                example[now_x - 1] |= 1 << (now_y - 1);
                            }

                            for (size_t y = now_y; y < w; y++)
                            {
                                example[now_x - 1] &= 255 ^ (1 << y);
                                if (1 - color)
                                {
                                    example[now_x - 1] |= 1 << y;
                                }
                            }

                            if (h > now_x)
                            {
                                if (1 - color)
                                {
                                    example[h - 1] = 255;
                                }
                                else
                                {
                                    example[h - 1] = 0;
                                }
                            }
                        }
                        sum += cnt;
                    }
                }
            }
            else
            {
                addSts(newSt1, newSt2, cnt, rec, idx, color);
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
                unsigned long long cnt = qs[act][iQ].cnt;
                unsigned char minUnused = qs[act][iQ].minUnused;

                if (1 == now_y)
                {
                    st1 <<= ST1_BITS;

                    st2 <<= ST2_BITS;
                    st2 &= st2Mask;
                }

                leftPlug = 0, upPlug = 0;
                leftCell = -1, upCell = -1;

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

                if (BLACK == cells[now_x][now_y])
                {
                    // black
                    func(BLACK, qs[act][iQ], st1, st2, cnt, minUnused, nAct);
                }
                else if (WHITE == cells[now_x][now_y])
                {
                    // white
                    func(WHITE, qs[act][iQ], st1, st2, cnt, minUnused, nAct);
                }
                else
                {
                    // 任意颜色
                    func(BLACK, qs[act][iQ], st1, st2, cnt, minUnused, nAct);
                    func(WHITE, qs[act][iQ], st1, st2, cnt, minUnused, nAct);
                }
            }

            // 准备下一轮
            qTail[act] = 0;
            for (int i = (1 << (w + 1)) - 1; i >= 0; i--)
            {
                cnts[act][i].clear();
            }

            act = nAct;
        }

        // output
        printf("%lld\n", sum);
        if (sum)
        {
            for (size_t row = 0; row < h; row++)
            {
                for (size_t col = 0; col < w; col++)
                {
                    if (WHITE == (example[row] & (1 << col)))
                    {
                        printf("o");
                    }
                    else
                    {
                        printf("#");
                    }
                }
                printf("\n");
            }
        }
    }

    return 0;
}
