// https://vjudge.net/problem/HDU-4113
// https://acm.hdu.edu.cn/showproblem.php?pid=4113
// 射线法 http://www.xiaobaigis.com/gisarticles/GiSArticle?ID=110

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
#define MAX_HW 10
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int vrts;  // 垂直插头个数
    unsigned int len;

    Record() {}
};

char cells[MAX_HW][MAX_HW];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)     \
    NEW = OLD;                            \
    NEW &= ~(ST_MASK << ((POS)*ST_BITS)); \
    NEW |= (VAL) << ((POS)*ST_BITS);

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
    qs[act][0].vrts = 0;
    qs[act][0].len = 0;

    qTail[act]++;
}

inline void addSts(unsigned int st, unsigned int vrts, unsigned int len, int idx)
{
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(st);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = st;
        qs[idx][pInQ].vrts = vrts;
        qs[idx][pInQ].len = len;

        cnts[idx][st] = pInQ;
        qTail[idx]++;
    }
    else
    {
        if (len < qs[idx][it->second].len)
        {
            qs[idx][it->second].len = len;
        }
    }
}

int main()
{
    int t;
    cin >> t;

    for (int it = 1; it <= t; it++)
    {
        cin >> h >> w;

        int lastO_x, lastO_y;

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];

                if ('o' == cells[row][col])
                {
                    lastO_x = row;
                    lastO_y = col;
                }
            }
        }

        h ++;
        w ++;

        int ans = -1;
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
                unsigned int st = qs[act][iQ].state;
                unsigned int vrts = qs[act][iQ].vrts;
                unsigned int len = qs[act][iQ].len;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                    vrts = 0;
                }

                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                if (left && up)
                {
                    if (h > now_x && w > now_y)
                    {
                        if ('o' == cells[now_x][now_y])
                        {
                            if (0 == (vrts & 1))
                            {
                                // 非法
                                continue;
                            }
                        }
                        else if ('x' == cells[now_x][now_y])
                        {
                            if (1 == (vrts & 1))
                            {
                                // 非法
                                continue;
                            }
                        }
                    }

                    unsigned int newSt = st;
                    setVal4St(newSt, newSt, now_y - 1, 0);
                    setVal4St(newSt, newSt, now_y, 0);

                    if (1 == left && 1 == up)
                    {
                        int pos = now_y + 1;
                        int s = 1;
                        while (pos <= w)
                        {
                            int v = getVal4St(newSt, pos);
                            if (1 == v)
                            {
                                s++;
                            }
                            else if (2 == v)
                            {
                                s--;
                                if (0 == s)
                                {
                                    setVal4St(newSt, newSt, pos, 1);
                                    break;
                                }
                            }

                            pos++;
                        }
                    }
                    else if (2 == left && 2 == up)
                    {
                        int pos = now_y - 2;
                        int s = 1;
                        while (0 <= pos)
                        {
                            int v = getVal4St(newSt, pos);
                            if (2 == v)
                            {
                                s++;
                            }
                            else if (1 == v)
                            {
                                s--;
                                if (0 == s)
                                {
                                    setVal4St(newSt, newSt, pos, 2);
                                    break;
                                }
                            }

                            pos--;
                        }
                    }
                    else if (2 == left && 1 == up)
                    {
                        // do nothing
                    }
                    else
                    {
                        // 1 == leftPlug && 2 == upPlug
                        // 行程回路，判断是否有效
                        if (0 == newSt)
                        {
                            if ((now_x > lastO_x + 1) || (now_x == lastO_x + 1 && now_y > lastO_y))
                            {
                                // 合法
                                if (0 > ans || ans > len)
                                {
                                    ans = len;
                                }
                            }
                        }

                        continue;
                    }

                    addSts(newSt, vrts, len, nAct);
                }
                else if (left || up)
                {
                    int val = left + up;

                    if (w > now_y)
                    {
                        // --
                        bool flag = true;
                        if (h > now_x)
                        {
                            if ('o' == cells[now_x][now_y])
                            {
                                if (0 == (vrts & 1))
                                {
                                    // 非法
                                    flag = false;
                                }
                            }
                            else if ('x' == cells[now_x][now_y])
                            {
                                if (1 == (vrts & 1))
                                {
                                    // 非法
                                    flag = false;
                                }
                            }
                        }

                        if (flag)
                        {
                            unsigned newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 0);
                            setVal4St(newSt, newSt, now_y, val);

                            addSts(st, vrts, len + 1, nAct);
                        }
                    }

                    if (h > now_x)
                    {
                        // |
                        bool flag = true;
                        if (w > now_y)
                        {
                            if ('o' == cells[now_x][now_y])
                            {
                                if (1 == (vrts & 1))
                                {
                                    // 非法
                                    flag = false;
                                }
                            }
                            else if ('x' == cells[now_x][now_y])
                            {
                                if (0 == (vrts & 1))
                                {
                                    // 非法
                                    flag = false;
                                }
                            }
                        }

                        if (flag)
                        {
                            unsigned newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, val);
                            setVal4St(newSt, newSt, now_y, 0);

                            addSts(st, vrts + 1, len + 1, nAct);
                        }
                    }
                }
                else
                {
                    // 0 == left && 0 == up
                    {
                        // 没有引出新的线段
                        bool flag = true;
                        if ('o' == cells[now_x][now_y])
                        {
                            if (0 == (vrts & 1))
                            {
                                // 非法
                                flag = false;
                            }
                        }
                        else if ('x' == cells[now_x][now_y])
                        {
                            if (1 == (vrts & 1))
                            {
                                // 非法
                                flag = false;
                            }
                        }

                        if (flag)
                        {
                            addSts(st, vrts, len, nAct);
                        }
                    }

                    if (h > now_x && w > now_y)
                    {
                        bool flag = true;
                        if ('o' == cells[now_x][now_y])
                        {
                            if (1 == (vrts & 1))
                            {
                                // 非法
                                flag = false;
                            }
                        }
                        else if ('x' == cells[now_x][now_y])
                        {
                            if (0 == (vrts & 1))
                            {
                                // 非法
                                flag = false;
                            }
                        }

                        if (flag)
                        {
                            unsigned newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 1);
                            setVal4St(newSt, newSt, now_y, 2);

                            addSts(st, vrts + 1, len + 2, nAct);
                        }
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        printf("Case #%d: %d\n", it, ans);
    }

    return 0;
}
