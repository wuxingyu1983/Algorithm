// https://pintia.cn/problem-sets/91827364500/exam/problems/91827369576?type=7&page=27

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

#define DEBUG   0
#define MAX_H   21
#define MAX_W   11
#define QS_SIZE 60000
#define ST_BITS 2
#define ST_MASK 3

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)                           \
    NEW = OLD;                                                  \
    NEW &= ~(((unsigned long long)ST_MASK) << ((POS)*ST_BITS)); \
    NEW |= ((unsigned long long)(VAL)) << ((POS)*ST_BITS);

int h, w;
char cells[MAX_H][MAX_W];
int ans;

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    int sum;

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
        if ('#' == cells[1][col] || 'W' == cells[1][col] || 'L' == cells[1][col])
        {
        }
        else
        {
            unsigned int st = 0;

            setVal4St(st, st, (col - 1), 3);

            qs[act][qTail[act]].state = st;
            qs[act][qTail[act]].sum = 0;

            qTail[act]++;
        }
    }

    now_x = 0;
    now_y = w;
}

inline void addST(unsigned int st, int sum, int idx)
{
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(st);
    if (it == cnts[idx].end())
    {
        qs[idx][qTail[idx]].state = st;
        qs[idx][qTail[idx]].sum = sum;
        
        cnts[idx][st] = qTail[idx];                                                                                                          \
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
    while (true)
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
                unsigned int st = qs[act][iQ].state;
                int sum = qs[act][iQ].sum;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                if ('#' == cells[now_x][now_y])
                {
                    // do nothing
                    addST(st, sum, nAct);
                }
                else if ('W' == cells[now_x][now_y])
                {
                    // check
                    int cnt = 0;
                    for (size_t i = 0; i < now_y - 1; i++)
                    {
                        if (0 < (getVal4St(st, i)))
                        {
                            cnt++;
                        }
                    }

                    if (0 == (cnt & 1))
                    {
                        addST(st, sum, nAct);
                    }
                }
                else if ('L' == cells[now_x][now_y])
                {
                    // check
                    int cnt = 0;
                    for (size_t i = 0; i < now_y - 1; i++)
                    {
                        if (0 < (getVal4St(st, i)))
                        {
                            cnt++;
                        }
                    }

                    if (1 == (cnt & 1))
                    {
                        addST(st, sum, nAct);
                    }
                }
                else
                {
                    int left = 0, up = 0;
                    left = getVal4St(st, now_y - 1);
                    up = getVal4St(st, now_y);

                    sum += cells[now_x][now_y] - '0';

                    if (left && up)
                    {
                    }
                    else if (left)
                    {
                        if (h == now_x && 3 == left)
                        {
                            addST(st, sum, nAct);
                        }
                        else if (h > now_x)
                        {
                            if ('0' <= cells[now_x + 1][now_y] && '9' >= cells[now_x + 1][now_y])
                            {
                                addST(st, sum, nAct);
                            }
                        }

                        if (w > now_y)
                        {
                            if ('0' <= cells[now_x][now_y + 1] && '9' >= cells[now_x][now_y + 1])
                            {
                                setVal4St(st, st, (now_y - 1), 0);
                                setVal4St(st, st, now_y, left);

                                addST(st, sum, nAct);
                            }
                        }
                    }
                    else if (up)
                    {
                        if (w > now_y)
                        {
                            if ('0' <= cells[now_x][now_y + 1] && '9' >= cells[now_x][now_y + 1])
                            {
                                addST(st, sum, nAct);
                            }
                        }

                        if (h == now_x && 3 == left)
                        {
                            setVal4St(st, st, (now_y - 1), up);
                            setVal4St(st, st, now_y, 0);

                            addST(st, sum, nAct);
                        }
                        else if (h > now_x)
                        {
                            if ('0' <= cells[now_x + 1][now_y] && '9' >= cells[now_x + 1][now_y])
                            {
                                setVal4St(st, st, (now_y - 1), up);
                                setVal4St(st, st, now_y, 0);

                                addST(st, sum, nAct);
                            }
                        }
                    }
                    else
                    {
                        // 0 == left && 0 == up
                        // do nothing
                        addST(st, sum, nAct);

                        if (h > now_x && w > now_y)
                        {
                            if ('#' == cells[now_x + 1][now_y] || 'W' == cells[now_x + 1][now_y] || 'L' == cells[now_x + 1][now_y])
                            {
                                continue;
                            }

                            if ('#' == cells[now_x][now_y + 1] || 'W' == cells[now_x][now_y + 1] || 'L' == cells[now_x][now_y + 1])
                            {
                                continue;
                            }

                            setVal4St(st, st, (now_y - 1), 1);
                            setVal4St(st, st, now_y, 2);
                            
                            addST(st, sum, nAct);
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
