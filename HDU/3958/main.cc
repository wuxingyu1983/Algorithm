// https://vjudge.net/problem/HDU-3958
// https://acm.hdu.edu.cn/showproblem.php?pid=3958

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
#define MAX_H 21
#define ST1_BITS 2
#define ST1_MASK 3
#define ST2_BITS 1
#define ST2_MASK 1
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state1;   // 轮廓线段状态
    unsigned short state2; // 轮廓cells状态
    unsigned int len;
    char grid[MAX_H][MAX_W]; // 满足当前 state 状态下的 一组 可能的 grid

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St1(ST, POS) ((ST) >> ((POS)*ST1_BITS)) & ST1_MASK

#define setVal4St1(NEW, OLD, POS, VAL)      \
    NEW = OLD;                              \
    NEW &= ~(ST1_MASK << ((POS)*ST1_BITS)); \
    NEW |= (VAL) << ((POS)*ST1_BITS);

#define getVal4St2(ST, POS) ((ST) >> ((POS)*ST2_BITS)) & ST2_MASK

#define setVal4St2(NEW, OLD, POS, VAL)      \
    NEW = OLD;                              \
    NEW &= ~(ST2_MASK << ((POS)*ST2_BITS)); \
    NEW |= (VAL) << ((POS)*ST2_BITS);

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
    qs[act][0].len = 0;

    qTail[act]++;
}

int main()
{
    int t;
    cin >> t;

    int sx, sy, tx, ty;

    while (t --)
    {
        cin >> h >> w;

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];

                if ('S' == cells[row][col])
                {
                    sx = row;
                    sy = col;
                }

                if ('T' == cells[row][col])
                {
                    tx = row;
                    ty = col;
                }
            }
        }

        if (1 == (abs(sx - tx) + abs(sy - ty)))
        {

        }
        else
        {
            init();

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
                    unsigned int st1 = qs[act][iQ].state1;
                    unsigned short st2 = qs[act][iQ].state2;
                    unsigned int len = qs[act][iQ].len;

                    if (1 == now_y)
                    {
                        st1 <<= ST1_BITS;
                    }

                    int leftPlug = 0, upPlug = 0;
                    int leftCell = 0, upCell = 0; // 0 -- 障碍物, 1 -- path 的一部分

                    leftPlug = getVal4St1(st1, now_y - 1);
                    upPlug = getVal4St1(st1, now_y);
                    
                    leftCell = getVal4St2(st2, now_y - 1);
                    upCell = getVal4St2(st2, now_y);

                    if (leftPlug && upPlug)
                    {
                        if ('.' == cells[now_x][now_y])
                        {
                            unsigned int newSt1 = st1;
                            unsigned short newSt2 = st2;

                            if (3 == leftPlug && 3 == upPlug)
                            {
                                // do nothing
                            }
                            else if (3 == leftPlug || 3 == upPlug)
                            {
                                if (1 == leftPlug || 1 == upPlug)
                                {
                                    int pos = now_y + 1;
                                    int s = 1;
                                    while (pos <= w)
                                    {
                                        int v = getVal4St1(newSt1, pos);
                                        if (1 == v)
                                        {
                                            s++;
                                        }
                                        else if (2 == v)
                                        {
                                            s--;
                                            if (0 == s)
                                            {
                                                setVal4St1(newSt1, newSt1, pos, 3);
                                                break;
                                            }
                                        }

                                        pos++;
                                    }
                                }
                                else
                                {
                                    // 2 == leftPlug || 2 == upPlug
                                    int pos = now_y - 2;
                                    int s = 1;
                                    while (0 <= pos)
                                    {
                                        int v = getVal4St1(newSt1, pos);
                                        if (2 == v)
                                        {
                                            s++;
                                        }
                                        else if (1 == v)
                                        {
                                            s--;
                                            if (0 == s)
                                            {
                                                setVal4St1(newSt1, newSt1, pos, 3);
                                                break;
                                            }
                                        }

                                        pos--;
                                    }
                                }
                            }
                            else
                            {
                                // leftPlug 和 upPlug 都不为 3
                                if (1 == leftPlug && 1 == upPlug)
                                {
                                    int pos = now_y + 1;
                                    int s = 1;
                                    while (pos <= w)
                                    {
                                        int v = getVal4St1(newSt1, pos);
                                        if (1 == v)
                                        {
                                            s++;
                                        }
                                        else if (2 == v)
                                        {
                                            s--;
                                            if (0 == s)
                                            {
                                                setVal4St1(newSt1, newSt1, pos, 1);
                                                break;
                                            }
                                        }

                                        pos++;
                                    }
                                }
                                else if (2 == leftPlug && 2 == upPlug)
                                {
                                    int pos = now_y - 2;
                                    int s = 1;
                                    while (0 <= pos)
                                    {
                                        int v = getVal4St1(newSt1, pos);
                                        if (2 == v)
                                        {
                                            s++;
                                        }
                                        else if (1 == v)
                                        {
                                            s--;
                                            if (0 == s)
                                            {
                                                setVal4St1(newSt1, newSt1, pos, 2);
                                                break;
                                            }
                                        }

                                        pos--;
                                    }
                                }
                                else if (2 == leftPlug && 1 == upPlug)
                                {
                                    // do nothing
                                }
                                else
                                {
                                    // 1 == leftPlug && 2 == upPlug
                                    // 非法
                                    continue;
                                }
                            }

                            setVal4St1(newSt1, newSt1, now_y - 1, 0);
                            setVal4St1(newSt1, newSt1, now_y, 0);

                            setVal4St2(newSt2, newSt2, now_y, 1);       // 1 -- path 的一部分

                            //  TBD -- addSt

                        }
                    }
                    else if (leftPlug || upPlug)
                    {
                        if (1 == leftCell && 1 == upCell)
                        {
                        }
                        else
                        {
                            unsigned int newSt1 = st1;
                            unsigned short newSt2 = st2;
                            int val = leftPlug + upPlug;

                            if ('.' == cells[now_x][now_y])
                            {
                                // 左、上没有路径
                                if (h > now_x && 'B' != cells[now_x + 1][now_y])
                                {
                                    setVal4St1(newSt1, newSt1, now_y - 1, val);
                                    setVal4St1(newSt1, newSt1, now_y, 0);

                                    setVal4St2(newSt2, newSt2, now_y, 1);       // 1 -- path 的一部分

                                    //  TBD -- addSt
                                }

                                if (w > now_y && 'B' != cells[now_x][now_y + 1])
                                {
                                    setVal4St1(newSt1, newSt1, now_y - 1, 0);
                                    setVal4St1(newSt1, newSt1, now_y, val);

                                    setVal4St2(newSt2, newSt2, now_y, 1);       // 1 -- path 的一部分

                                    //  TBD -- addSt
                                }
                            }
                            else if ('S' == cells[now_x][now_y] || 'T' == cells[now_x][now_y])
                            {
                                if (1 == val)
                                {
                                    int pos = now_y + 1;
                                    int s = 1;
                                    while (pos <= w)
                                    {
                                        int v = getVal4St1(newSt1, pos);
                                        if (1 == v)
                                        {
                                            s++;
                                        }
                                        else if (2 == v)
                                        {
                                            s--;
                                            if (0 == s)
                                            {
                                                setVal4St1(newSt1, newSt1, pos, 3);
                                                break;
                                            }
                                        }

                                        pos++;
                                    }
                                }
                                else
                                {
                                    // 2 == val
                                    int pos = now_y - 2;
                                    int s = 1;
                                    while (0 <= pos)
                                    {
                                        int v = getVal4St1(newSt1, pos);
                                        if (2 == v)
                                        {
                                            s++;
                                        }
                                        else if (1 == v)
                                        {
                                            s--;
                                            if (0 == s)
                                            {
                                                setVal4St1(newSt1, newSt1, pos, 3);
                                                break;
                                            }
                                        }

                                        pos--;
                                    }
                                }

                                setVal4St1(newSt1, newSt1, now_y - 1, 0);
                                setVal4St1(newSt1, newSt1, now_y, 0);

                                setVal4St2(newSt2, newSt2, now_y, 1); // 1 -- path 的一部分

                                //  TBD -- addSt
                            }
                        }
                    }
                    else
                    {
                        // 0 == leftPlug && 0 == upPlug
                        unsigned int newSt1 = st1;
                        unsigned short newSt2 = st2;

                        if ('B' == cells[now_x][now_y])
                        {
                            setVal4St2(newSt2, newSt2, now_y, 0);       // 0 -- 障碍物(B)

                            //  TBD -- addSt
                        }
                        else if ('.' == cells[now_x][now_y])
                        {
                            // 设置 W
                            setVal4St2(newSt2, newSt2, now_y, 0);       // 0 -- 障碍物(W)

                            //  TBD -- addSt


                            if (0 == leftCell && 0 == upCell)
                            {
                                // 左、上没有路径
                                if (h > now_x && w > now_y && 'B' != cells[now_x + 1][now_y] && 'B' != cells[now_x][now_y + 1])
                                {
                                    setVal4St1(newSt1, newSt1, now_y - 1, 1);
                                    setVal4St1(newSt1, newSt1, now_y, 2);

                                    setVal4St2(newSt2, newSt2, now_y, 1);       // 1 -- path 的一部分

                                    //  TBD -- addSt
                                }
                            }
                        }
                        else if ('S' == cells[now_x][now_y] || 'T' == cells[now_x][now_y])
                        {
                            if (0 == leftCell && 0 == upCell)
                            {
                                // 左、上没有路径
                                if (h > now_x && 'B' != cells[now_x + 1][now_y])
                                {
                                    setVal4St1(newSt1, newSt1, now_y - 1, 3);
                                    setVal4St1(newSt1, newSt1, now_y, 0);

                                    setVal4St2(newSt2, newSt2, now_y, 1);       // 1 -- path 的一部分

                                    //  TBD -- addSt
                                }

                                if (w > now_y && 'B' != cells[now_x][now_y + 1])
                                {
                                    setVal4St1(newSt1, newSt1, now_y - 1, 0);
                                    setVal4St1(newSt1, newSt1, now_y, 3);

                                    setVal4St2(newSt2, newSt2, now_y, 1);       // 1 -- path 的一部分

                                    //  TBD -- addSt
                                }
                            }
                        }
                    }
                }

                qTail[act] = 0;
                cnts[act].clear();
                act = nAct;
            }
        }

        // 空格
        string str;
        getline(cin, str);
    }

    return 0;
}
