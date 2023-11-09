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
#define QS_SIZE 60000
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

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int vrts;  // 垂直插头个数
    bool have3;         // 是否已经出现 3 插头
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

    qs[act][0].state = 0;
    qs[act][0].vrts = 0;
    qs[act][0].have3 = false;
    qs[act][0].sum = 0;

    qTail[act]++;

    now_x = 0;
    now_y = w;
}

inline void addST(unsigned int st, unsigned int vrts, bool have3, unsigned int sum, int idx)
{
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(st);
    if (it == cnts[idx].end())
    {
        qs[idx][qTail[idx]].state = st;
        qs[idx][qTail[idx]].vrts = vrts;
        qs[idx][qTail[idx]].have3 = have3;
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
                    // TBD
                    for (int iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        if (qs[act][iQ].state)
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
                bool have3 = qs[act][iQ].have3;
                unsigned int sum = qs[act][iQ].sum;

                if (1 == now_y)
                {
                    if (1 < now_x && false == have3)
                    {
                        continue;
                    }

                    st <<= ST_BITS;
                    vrts = 0;
                }

                if ('#' == cells[now_x][now_y])
                {
                    // 障碍物
                    // do nothing
                    addST(st, vrts, have3, sum, nAct);
                }
                else if ('W' == cells[now_x][now_y])
                {
                    // check
                    if (0 == (vrts & 1))
                    {
                        addST(st, vrts, have3, sum, nAct);
                    }
                }
                else if ('L' == cells[now_x][now_y])
                {
                    if (1 == (vrts & 1))
                    {
                        addST(st, vrts, have3, sum, nAct);
                    }
                }
                else
                {
                    int left = getVal4St(st, now_y - 1);
                    int up = getVal4St(st, now_y);

                    if (left && up)
                    {

                    }
                    else if (left || up)
                    {
                        int val = left + up;
                        if (3 == val && now_x == h)
                        {
                            unsigned int newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 0);
                            setVal4St(newSt, newSt, now_y, 0);

                            addST(st, vrts + 1, have3, sum + (cells[now_x][now_y] - '0'), nAct);
                        }
                        else
                        {
                            if (h > now_x && '#' != cells[now_x + 1][now_y] && 'W' != cells[now_x + 1][now_y] && 'L' != cells[now_x + 1][now_y])
                            {
                                unsigned int newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, val);
                                setVal4St(newSt, newSt, now_y, 0);

                                addST(st, vrts + 1, have3, sum + (cells[now_x][now_y] - '0'), nAct);
                            }

                            if (w > now_y && '#' != cells[now_x][now_y + 1] && 'W' != cells[now_x][now_y + 1] && 'L' != cells[now_x][now_y + 1])
                            {
                                unsigned int newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, 0);
                                setVal4St(newSt, newSt, now_y, val);

                                addST(st, vrts + 1, have3, sum + (cells[now_x][now_y] - '0'), nAct);
                            }
                        }                        
                    }
                    else
                    {
                        // 0 == left && 0 == up

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
