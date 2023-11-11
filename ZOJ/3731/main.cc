// https://pintia.cn/problem-sets/91827364500/exam/problems/91827369576?type=7&page=27
// https://vjudge.net/problem/HDU-4796
// https://acm.hdu.edu.cn/showproblem.php?pid=4796

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
#define MAX_H 21
#define MAX_W 11
#define QS_SIZE 70000
#define ST_BITS 2
#define ST_MASK 3

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)     \
    NEW = OLD;                            \
    NEW &= ~(ST_MASK << ((POS)*ST_BITS)); \
    NEW |= (VAL) << ((POS)*ST_BITS);

int h, w;
char cells[MAX_H][MAX_W];
int ans;
char flag[1048576];

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int vrts;  // 垂直插头个数
    unsigned int sum;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

inline void init()
{
    ans = -1;
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    for (size_t col = 1; col <= w; col++)
    {
        if ('#' != cells[1][col] && 'W' != cells[1][col] && 'L' != cells[1][col])
        {
            qs[act][qTail[act]].state = 3 << ((col - 1)*ST_BITS);
            qs[act][qTail[act]].vrts = 0;
            qs[act][qTail[act]].sum = 0;

            qTail[act]++;
        }
    }

    now_x = 0;
    now_y = w;
}

inline bool isDigit(char ch)
{
    bool ret = false;

    if ('#' != ch && 'W' != ch && 'L' != ch)
    {
        ret = true;
    }

    return ret;
}

inline void addST(unsigned int st, unsigned int vrts, unsigned int sum, int idx)
{
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(st);
    if (it == cnts[idx].end())
    {
        qs[idx][qTail[idx]].state = st;
        qs[idx][qTail[idx]].vrts = vrts;
        qs[idx][qTail[idx]].sum = sum;

        cnts[idx][st] = qTail[idx];
        qTail[idx]++;
    }
    else
    {
        if (sum < qs[idx][it->second].sum)
        {
            qs[idx][it->second].sum = sum;
        }
    }
}

int main()
{
    for (size_t i = 0; i < 10; i++)
    {
        flag[3 << (i * ST_BITS)] = 1;
    }

    while (scanf("%d %d", &h, &w) == 2)
    {
        for (int row = 1; row <= h; row++)
        {
            for (int col = 1; col <= w; col++)
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
                now_x++;
                now_y = 1;

                if (h < now_x)
                {
                    // finished
                    for (int iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        if (flag[qs[act][iQ].state])
                        {
                            if (0 > ans || ans > qs[act][iQ].sum)
                            {
                                ans = qs[act][iQ].sum;
                            }
                        }
                    }
                    break;
                }
            }
            else
            {
                now_y++;
            }

            for (int iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned int st = qs[act][iQ].state;
                unsigned int vrts = qs[act][iQ].vrts;
                unsigned int sum = qs[act][iQ].sum;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                    vrts = 0;
                }

                if ('#' == cells[now_x][now_y])
                {
                    // 障碍物
                    // do nothing
                    addST(st, vrts, sum, nAct);
                }
                else if ('W' == cells[now_x][now_y])
                {
                    // check
                    if (0 == (vrts & 1))
                    {
                        addST(st, vrts, sum, nAct);
                    }
                }
                else if ('L' == cells[now_x][now_y])
                {
                    if (1 == (vrts & 1))
                    {
                        addST(st, vrts, sum, nAct);
                    }
                }
                else
                {
                    int left = getVal4St(st, now_y - 1);
                    int up = getVal4St(st, now_y);

                    if (left && up)
                    {
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
                        else if (1 == left && 2 == up)
                        {
                            // 闭环，回路，非法
                            continue;
                        }
                        else
                        {
                            // left 和 up 中至少 有一个 3
                            if (3 == left && 3 == up)
                            {
                                // do nothin
                            }
                            else if (1 == left || 1 == up)
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
                                            setVal4St(newSt, newSt, pos, 3);
                                            break;
                                        }
                                    }

                                    pos++;
                                }
                            }
                            else
                            {
                                // 其中为 2
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
                                            setVal4St(newSt, newSt, pos, 3);
                                            break;
                                        }
                                    }

                                    pos--;
                                }
                            }
                        }

                        addST(newSt, vrts, sum + (cells[now_x][now_y] - '0'), nAct);
                    }
                    else if (left || up)
                    {
                        int val = left + up;

                        if (h == now_x || (h > now_x && isDigit(cells[now_x + 1][now_y])))
                        {
                            // |
                            unsigned int newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, val);
                            setVal4St(newSt, newSt, now_y, 0);

                            addST(newSt, vrts + 1, sum + (cells[now_x][now_y] - '0'), nAct);
                        }

                        if (w > now_y && isDigit(cells[now_x][now_y + 1]))
                        {
                            // --
                            unsigned int newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 0);
                            setVal4St(newSt, newSt, now_y, val);

                            addST(newSt, vrts, sum + (cells[now_x][now_y] - '0'), nAct);
                        }
                    }
                    else
                    {
                        // 0 == left && 0 == up
                        {
                            // do nothing
                            addST(st, vrts, sum, nAct);
                        }

                        if ((h == now_x || (h > now_x && isDigit(cells[now_x + 1][now_y]))) && w > now_y && isDigit(cells[now_x][now_y + 1]))
                        {
                            unsigned int newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 1);
                            setVal4St(newSt, newSt, now_y, 2);

                            addST(newSt, vrts + 1, sum + (cells[now_x][now_y] - '0'), nAct);
                        }
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        cout << ans << endl;
    }

    return 0;
}
