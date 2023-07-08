// https://vjudge.net/problem/ZOJ-3466

#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
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
#define MAX_N   26      // row
#define MAX_M   10      // col
#define BITS    2
#define MASK    3
#define PLUG_1  1
#define PLUG_2  2

class Line
{
public:
    /*
        已经处理过（x, y）格子后，状态为state的个数cnt
    */
    int x, y;
    long long state;

    Line()
    {
        x = y = 0;
        state = 0;
    }
};

queue<Line> lines;

unsigned char cells[MAX_N + 1][MAX_M + 1]; // 1 - obstacle

// 1 个 cell 6 个边（side）, 只能有2个插头（plug）

inline long long setState(long long state, int cell, int plug, int val)
{
    long long ret = state;
    int pos = cell * BITS + plug - 1;

    // clear
    ret &= ~(((long long)MASK) << pos);

    ret |= ((long long)val) << pos;

    return ret;
}

inline int getState(long long state, int cell, int plug)
{
    int ret = 0;

    ret = (state >> (cell * BITS + plug - 1)) & MASK;

    return 0;
}

inline int getSideState(long long state, int cell, int side)
{
    int ret = 0;

    if (side == getState(state, cell, PLUG_1))
    {
        ret = PLUG_1;
    }
    else if (side == getState(state, cell, PLUG_2))
    {
        ret = PLUG_2;
    }

    return ret;
}

map<long long, long long> cnts[2];
int act = 0; // 当前生效的 map
unsigned char flags[MAX_N + 1][MAX_M + 1];

void insertLine(Line &line, long long cnt)
{
    // 判断是否已经存在了
    map<long long, long long>::iterator it = cnts[1 - act].find(line.state);
    if (it == cnts[1 - act].end())
    {
        cnts[1 - act][line.state] = cnt;
        lines.push(line);
    }
    else
    {
        cnts[1 - act][line.state] = cnt + it->second;
    }
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    int n, m;
#if DEBUG
    fscanf(fp, "%d %d", &n, &m);
#else
    cin >> n >> m;
#endif

    int end_x = 0, end_y = 0;

    for (size_t i = 0; i < m; i++)
    {
        string str;

        cin >> str;

        int c = str[0] - 'A' + 1;
        int r = str[1] - 'A' + 1;

        cells[r][c] = 1;

        if (r > end_x)
        {
            end_x = r;
        }

        if (c > end_y)
        {
            end_y = c;
        }
    }

    m = n; 
    n = end_x;

    // start
    Line start;
    start.x = 0;
    start.y = m;
    start.state = 0;

    lines.push(start);

    flags[0][m] = 1;
    cnts[act][0] = 1;

    long long ans = 0;

    while (false == lines.empty())
    {
        Line pre = lines.front();
        lines.pop();

        int now_x = pre.x,
            now_y = pre.y;
        long long state = pre.state;

        if (0 == flags[now_x][now_y])
        {
            // 第一次访问 (now_x, now_y)
            flags[now_x][now_y] = 1;
            cnts[act].clear();
            act = 1 - act;
        }

        long long pre_cnt = cnts[act][state];

        if (m == pre.y)
        {
            now_x++;
            now_y = 1;
            state <<= 2;

            if (n < now_x)
            {
                continue;
            }
        }
        else
        {
            now_y++;
        }

        // (now_x, now_y) 将要处理的 cell
        if (1 == cells[now_x][now_y])
        {
            // 障碍物
            Line now;
            now.x = now_x;
            now.y = now_y;

            // 该 cell 的 6 条边 没有 插头
            state = setState(state, now_y, PLUG_1, 0);
            state = setState(state, now_y, PLUG_2, 0);

            now.state = state;

            insertLine(now, pre_cnt);
        }
        else
        {
            if (now_y & 1)
            {
                // 2 个可以 in 的边, 1, 2
                int st1 = getSideState(state, now_y, 1);
                int st2 = getSideState(state, now_y, 2);

                Line now;
                now.x = now_x;
                now.y = now_y;

                if (0 == st1 && 0 == st2)
                {
                    if (1 < now_y)
                    {
                        if (0 == cells[now_x + 1][now_y - 1])
                        {
                            state = setState(state, now_y, PLUG_1, 6);

                            if (n > now_x)
                            {
                                if (0 == cells[now_x + 1][now_y])
                                {
                                    state = setState(state, now_y, PLUG_2, 5);

                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }

                                if (m > now_y)
                                {
                                    if (0 == cells[now_x + 1][now_y + 1])
                                    {
                                        state = setState(state, now_y, PLUG_2, 4);

                                        now.state = state;

                                        insertLine(now, pre_cnt);
                                    }

                                    if (0 == cells[now_x][now_y + 1])
                                    {
                                        state = setState(state, now_y, PLUG_2, 3);

                                        now.state = state;

                                        insertLine(now, pre_cnt);
                                    }
                                }
                            }
                        }
                    }

                    if (n > now_x)
                    {
                        if (0 == cells[now_x + 1][now_y])
                        {
                            state = setState(state, now_y, PLUG_1, 5);

                            if (m > now_y)
                            {
                                if (0 == cells[now_x + 1][now_y + 1])
                                {
                                    state = setState(state, now_y, PLUG_2, 4);

                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }

                                if (0 == cells[now_x][now_y + 1])
                                {
                                    state = setState(state, now_y, PLUG_2, 3);

                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }
                            }
                        }
                    }

                    if (n > now_x && m < now_y)
                    {
                        if (0 == cells[now_x + 1][now_y + 1] && 0 == cells[now_x][now_y + 1])
                        {
                            state = setState(state, now_y, PLUG_1, 4);
                            state = setState(state, now_y, PLUG_2, 3);

                            now.state = state;

                            insertLine(now, pre_cnt);
                        }
                    }
                }
                else if ((0 == st1 && 0 < st2) || (0 < st1 && 0 == st2))
                {
                    int st = st1 + st2;

                    state = setState(state, now_y, PLUG_1, 0);
                    state = setState(state, now_y, PLUG_2, 0);

                    if (n > now_x)
                    {
                        if (1 < now_y && 0 == cells[now_x + 1][now_y - 1])
                        {
                            state = setState(state, now_y, st, 6);

                            now.state = state;

                            insertLine(now, pre_cnt);
                        }

                        if (0 == cells[now_x + 1][now_y])
                        {
                            state = setState(state, now_y, st, 5);

                            now.state = state;

                            insertLine(now, pre_cnt);
                        }

                        if (m > now_y && 0 == cells[now_x + 1][now_y + 1])
                        {
                            state = setState(state, now_y, st, 4);

                            now.state = state;

                            insertLine(now, pre_cnt);
                        }
                    }

                    if (m > now_y && 0 == cells[now_x][now_y + 1])
                    {
                        state = setState(state, now_y, st, 3);

                        now.state = state;

                        insertLine(now, pre_cnt);
                    }
                }
                else if (1 == st1 && 1 == st2)
                {
                    state = setState(state, now_y, PLUG_1, 0);
                    state = setState(state, now_y, PLUG_2, 0);

                    int s = 1;
                    for (size_t i = now_y + 1; i <= m; i++)
                    {
                        if (getState(state, i, PLUG_1))
                        {
                            s ++;
                        }

                        int side = getState(state, i, PLUG_2);
                        if (side)
                        {
                            s --;
                            if (0 == s)
                            {
                                state = setState(state, i, PLUG_1, side);
                                state = setState(state, i, PLUG_2, 0);

                                now.state = state;

                                insertLine(now, pre_cnt);

                                break;
                            }
                        }
                    }
                    
                }
                else if (2 == st1 && 2 == st2)
                {
                    state = setState(state, now_y, PLUG_1, 0);
                    state = setState(state, now_y, PLUG_2, 0);

                    int s = 1;
                    for (int i = now_y - 1; i >= 1; i--)
                    {
                        if (getState(state, i, PLUG_2))
                        {
                            s ++;
                        }

                        int side = getState(state, i, PLUG_1);
                        if (side)
                        {
                            s --;
                            if (0 == s)
                            {
                                state = setState(state, i, PLUG_2, side);
                                state = setState(state, i, PLUG_1, 0);

                                now.state = state;

                                insertLine(now, pre_cnt);

                                break;
                            }
                        }
                    }
                    
                }
                else if (2 == st1 && 1 == st2)
                {
                    state = setState(state, now_y, PLUG_1, 0);
                    state = setState(state, now_y, PLUG_2, 0);

                    now.state = state;

                    insertLine(now, pre_cnt);
                }
                else if (1 == st1 && 2 == st2)
                {
                    state = setState(state, now_y, PLUG_1, 0);
                    state = setState(state, now_y, PLUG_2, 0);

                    now.state = state;

                    insertLine(now, pre_cnt);

                    if (0 == state)
                    {
                        ans = pre_cnt;
                    }
                }
            }
            else
            {

            }
        }
    }

    cout << ans << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
