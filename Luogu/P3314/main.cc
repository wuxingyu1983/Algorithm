// https://www.luogu.com.cn/problem/P3314

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
#define MAX_H 10
#define MAX_K 11
#define ST_BITS 4
#define ST_MASK 15 
#define QS_SIZE 600000
#define MOD 25619849

class Record
{
public:
    unsigned long long state; // 轮廓线段状态
    unsigned int len;
    unsigned int cnt;

    Record() {}
};

unsigned int cells[MAX_H][MAX_W];
vector<unsigned int> paths[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)                                  \
    ST &= ~(((unsigned long long)ST_MASK) << ((POS) * ST_BITS)); \
    if (VAL)                                                     \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

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
    qs[act][0].len = 0;
    qs[act][0].cnt = 1;

    qTail[act]++;
}

int main()
{
    int k;

    while (true)
    {
        cin >> w >> h >> k;

        if (0 == w && 0 == h && 0 == k)
        {
            break;
        }

        for (size_t row = 1; row <= h; row ++)
        {
            for (size_t col = 1; col <= w; col ++)
            {
                cin >> cells[row][col];
                paths[row][col].clear();
            }
        }

        for (size_t i = 1; i <= k; i++)
        {
            unsigned int x, y;

            cin >> x >> y;
            paths[x + 1][y + 1].push_back(i);

            cin >> x >> y;
            paths[x + 1][y + 1].push_back(i);
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

                    break;
                }
            }
            else
            {
                now_y++;
            }

            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st = qs[act][iQ].state;
                unsigned int len = qs[act][iQ].len;
                unsigned int cnt = qs[act][iQ].cnt;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                if (1 == cells[now_x][now_y])
                {
                    // 障碍物
                    // do nothing

                }
                else
                {
                    int left = getVal4St(st, now_y - 1);
                    int up = getVal4St(st, now_y);

                    if (0 < paths[now_x][now_y].size())
                    {
                        // 电源

                    }
                    else
                    {
                        // 普通格子
                        if (left && up)
                        {
                            if (left == up)
                            {
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, 0);
                                    setVal4St(newSt, now_y, 0);

                                    // TBD, addSt
                                }

                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    for (size_t color = 1; color <= k; color++)
                                    {
                                        unsigned long long newSt = st;
                                        setVal4St(newSt, now_y - 1, color);
                                        setVal4St(newSt, now_y, color);

                                        // TBD, addSt
                                    }
                                }
                            }
                            else
                            {
                                if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    // left ==> down, up ==> right
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, left);
                                    setVal4St(newSt, now_y, up);

                                    // TBD, addSt
                                }
                            }
                        }
                        else if (left || up)
                        {
                            int val = left + up;
                            if (h > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                unsigned long long newSt = st;
                                setVal4St(newSt, now_y - 1, val);
                                setVal4St(newSt, now_y, 0);

                                // TBD, addSt

                            }

                            if (w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                unsigned long long newSt = st;
                                setVal4St(newSt, now_y - 1, 0);
                                setVal4St(newSt, now_y, val);

                                // TBD, addSt
                            }
                        }
                        else
                        {
                            // 0 == left && 0 == up
                            {
                                unsigned long long newSt = st;
                                setVal4St(newSt, now_y - 1, 0);
                                setVal4St(newSt, now_y, 0);

                                // TBD, addSt
                            }

                            if (h > now_x && 0 == cells[now_x + 1][now_y] && w > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                for (size_t color = 1; color <= k; color++)
                                {
                                    unsigned long long newSt = st;
                                    setVal4St(newSt, now_y - 1, color);
                                    setVal4St(newSt, now_y, color);

                                    // TBD, addSt
                                }
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

    return 0;
}
