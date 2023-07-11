// https://vjudge.net/problem/ZOJ-3466

#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <unordered_map>
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

#define DEBUG 0
#define MAX_N 8  // row
#define MAX_M 10 // col
#define BITS 2
#define MASK 3
#define MASK3 63

int n, m;

class Line
{
public:
    /*
        已经处理过（x, y）格子后，状态为state的个数cnt
    */
    char x, y;
    long long state;

    Line()
    {
        x = y = 0;
        state = 0;
    }
};

unsigned char cells[MAX_N + 1][MAX_M + 1]; // 1 - obstacle

inline long long setState(long long state, int pos, int val)
{
    long long ret = state;

    // clear
    ret &= ~(((long long)MASK) << (pos * BITS));

    ret |= ((long long)val) << (pos * BITS);

    return ret;
}

inline long long setState3(long long state, int pos, int val)
{
    long long ret = state;

    // clear
    ret &= ~(((long long)MASK3) << (pos * BITS));

    ret |= ((long long)val) << (pos * BITS);

    return ret;
}

inline int getState(long long st, int pos)
{
    int ret = 0;

    ret = (st >> (pos * BITS)) & MASK;

    return ret;
}

unordered_map<long long, long long> cnts[2];
int act = 0; // 当前生效的 map

inline void insertLine(Line &line, long long cnt)
{
    // 判断是否已经存在了
    unordered_map<long long, long long>::iterator it = cnts[1 - act].find(line.state);
    if (it == cnts[1 - act].end())
    {
        cnts[1 - act][line.state] = cnt;
    }
    else
    {
        cnts[1 - act][line.state] = cnt + it->second;
    }
}

int main()
{
    while (scanf("%d %d", &n, &m))
    {
        if (0 >= n)
        {
            break;
        }

        // init
        cnts[0].clear();
        cnts[1].clear();
        act = 0;
        long long ans = 0;
        memset(cells, 0, sizeof(cells));

        char str[5];

        for (int i = 0; i < m; i++)
        {
            scanf("%s", str);

            int c = str[0] - 'A' + 1;
            int r = str[1] - 'A' + 1;

            cells[r][c] = 1;
        }

        m = n;
        n = MAX_N;

        // start
        Line start;
        start.x = 0;
        start.y = m;
        start.state = 0;

        cnts[act][0] = 1;

        int now_x = 0;
        int now_y = m;

        while (cnts[act].size())
        {
            if (m == now_y)
            {
                now_x++;
                now_y = 1;

                if (n < now_x)
                {
                    break;
                }
            }
            else
            {
                now_y++;
            }

            while (!cnts[act].empty())
            { 
                unordered_map<long long, long long>::iterator it = cnts[act].begin();
                long long state = it->first;
                if (1 == now_y && 0 == (now_x & 1))
                {
                    state <<= 2 * BITS;
                }
                long long pre_cnt = it->second;

                Line now;
                now.x = now_x;
                now.y = now_y;

                // (now_x, now_y) 将要处理的 cell
                if (1 == cells[now_x][now_y])
                {
                    // 障碍物
                    now.state = state;

                    insertLine(now, pre_cnt);

                    if (n == now_x && m == now_y)
                    {
                        if (0 == state)
                        {
                            ans += pre_cnt;
                        }
                    }
                }
                else
                {
                    int i = getState(state, 2 * (now_y - 1));
                    int j = getState(state, 2 * (now_y - 1) + 1);
                    int k = getState(state, 2 * now_y);

                    int cnt = 0;
                    int st = i + j + k;
                    if (i)
                    {
                        cnt++;
                    }

                    if (j)
                    {
                        cnt++;
                    }

                    if (k)
                    {
                        cnt++;
                    }

                    if (0 == cnt)
                    {
                        if (1 == (now_x & 1))
                        {
                            if (n > now_x && m > now_y)
                            {
                                if (0 == cells[now_x + 1][now_y] && 0 == cells[now_x + 1][now_y + 1])
                                {
                                    state = setState3(state, 2 * (now_y - 1), 9);
                                    /*
                                    state = setState(state, 2 * (now_y - 1), 1);
                                    state = setState(state, 2 * (now_y - 1) + 1, 2);
                                    state = setState(state, 2 * now_y, 0);
                                    */
                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }

                                if (0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                                {
                                    state = setState3(state, 2 * (now_y - 1), 33);
                                    /*
                                    state = setState(state, 2 * (now_y - 1), 1);
                                    state = setState(state, 2 * (now_y - 1) + 1, 0);
                                    state = setState(state, 2 * now_y, 2);
                                    */
                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }

                                if (0 == cells[now_x + 1][now_y + 1] && 0 == cells[now_x][now_y + 1])
                                {
                                    state = setState3(state, 2 * (now_y - 1), 36);
                                    /*
                                    state = setState(state, 2 * (now_y - 1), 0);
                                    state = setState(state, 2 * (now_y - 1) + 1, 1);
                                    state = setState(state, 2 * now_y, 2);
                                    */
                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }
                            }
                        }
                        else
                        {
                            if (n > now_x)
                            {
                                if (1 < now_y && 0 == cells[now_x + 1][now_y - 1] && 0 == cells[now_x + 1][now_y])
                                {
                                    state = setState3(state, 2 * (now_y - 1), 9);
                                    /*
                                    state = setState(state, 2 * (now_y - 1), 1);
                                    state = setState(state, 2 * (now_y - 1) + 1, 2);
                                    state = setState(state, 2 * now_y, 0);
                                    */
                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }

                                if (1 < now_y && m > now_y && 0 == cells[now_x + 1][now_y - 1] && 0 == cells[now_x][now_y + 1])
                                {
                                    state = setState3(state, 2 * (now_y - 1), 33);
                                    /*
                                    state = setState(state, 2 * (now_y - 1), 1);
                                    state = setState(state, 2 * (now_y - 1) + 1, 0);
                                    state = setState(state, 2 * now_y, 2);
                                    */
                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }

                                if (m > now_y && 0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                                {
                                    state = setState3(state, 2 * (now_y - 1), 36);
                                    /*
                                    state = setState(state, 2 * (now_y - 1), 0);
                                    state = setState(state, 2 * (now_y - 1) + 1, 1);
                                    state = setState(state, 2 * now_y, 2);
                                    */
                                    now.state = state;

                                    insertLine(now, pre_cnt);
                                }
                            }
                        }
                    }
                    else if (1 == cnt)
                    {
                        if (1 == (now_x & 1))
                        {
                            if (n > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                state = setState3(state, 2 * (now_y - 1), st);
                                /*
                                state = setState(state, 2 * (now_y - 1), st);
                                state = setState(state, 2 * (now_y - 1) + 1, 0);
                                state = setState(state, 2 * now_y, 0);
                                */
                                now.state = state;

                                insertLine(now, pre_cnt);
                            }

                            if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y + 1])
                            {
                                state = setState(state, 2 * (now_y - 1), st * 4);
                                /*
                                state = setState(state, 2 * (now_y - 1), 0);
                                state = setState(state, 2 * (now_y - 1) + 1, st);
                                state = setState(state, 2 * now_y, 0);
                                */
                                now.state = state;

                                insertLine(now, pre_cnt);
                            }
                        }
                        else
                        {
                            if (n > now_x && 1 < now_y && 0 == cells[now_x + 1][now_y - 1])
                            {
                                state = setState3(state, 2 * (now_y - 1), st);
                                /*
                                state = setState(state, 2 * (now_y - 1), st);
                                state = setState(state, 2 * (now_y - 1) + 1, 0);
                                state = setState(state, 2 * now_y, 0);
                                */
                                now.state = state;

                                insertLine(now, pre_cnt);
                            }

                            if (n > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                state = setState3(state, 2 * (now_y - 1), st * 4);
                                /*
                                state = setState(state, 2 * (now_y - 1), 0);
                                state = setState(state, 2 * (now_y - 1) + 1, st);
                                state = setState(state, 2 * now_y, 0);
                                */
                                now.state = state;

                                insertLine(now, pre_cnt);
                            }
                        }

                        if (m > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            state = setState3(state, 2 * (now_y - 1), st * 16);
                            /*
                            state = setState(state, 2 * (now_y - 1), 0);
                            state = setState(state, 2 * (now_y - 1) + 1, 0);
                            state = setState(state, 2 * now_y, st);
                            */
                            now.state = state;

                            insertLine(now, pre_cnt);
                        }
                    }
                    else if (2 == cnt)
                    {
                        if (2 == st)
                        {
                            // 1, 1
                            state = setState3(state, 2 * (now_y - 1), 0);
                            /*
                            state = setState(state, 2 * (now_y - 1), 0);
                            state = setState(state, 2 * (now_y - 1) + 1, 0);
                            state = setState(state, 2 * now_y, 0);
                            */
                            int pos = 2 * now_y + 1;
                            int s = 1;
                            while (pos <= m * 2)
                            {
                                int st = getState(state, pos);
                                if (1 == st)
                                {
                                    s++;
                                }
                                else if (2 == st)
                                {
                                    s--;
                                    if (0 == s)
                                    {
                                        state = setState(state, pos, 1);
                                        now.state = state;
                                        insertLine(now, pre_cnt);
                                        break;
                                    }
                                }

                                pos++;
                            }
                        }
                        else if (4 == st)
                        {
                            // 2, 2
                            state = setState3(state, 2 * (now_y - 1), 0);
                            /*
                            state = setState(state, 2 * (now_y - 1), 0);
                            state = setState(state, 2 * (now_y - 1) + 1, 0);
                            state = setState(state, 2 * now_y, 0);
                            */
                            int pos = 2 * (now_y - 1) - 1;
                            int s = 1;
                            while (0 <= pos)
                            {
                                int st = getState(state, pos);
                                if (2 == st)
                                {
                                    s++;
                                }
                                else if (1 == st)
                                {
                                    s--;
                                    if (0 == s)
                                    {
                                        state = setState(state, pos, 2);
                                        now.state = state;
                                        insertLine(now, pre_cnt);
                                        break;
                                    }
                                }

                                pos--;
                            }
                        }
                        else if (3 == st)
                        {
                            // 1, 2 or 2, 1
                            state = setState3(state, 2 * (now_y - 1), 0);
                            /*
                            state = setState(state, 2 * (now_y - 1), 0);
                            state = setState(state, 2 * (now_y - 1) + 1, 0);
                            state = setState(state, 2 * now_y, 0);
                            */
                            now.state = state;

                            insertLine(now, pre_cnt);

                            if (n == now_x && m == now_y)
                            {
                                if (0 == state)
                                {
                                    ans += pre_cnt;
                                }
                            }
                        }
                    }
                }

                cnts[act].erase(it);
            }

            cnts[act].clear();
            act = 1 - act;
        }

        printf("%lld\n", ans);
    }

    return 0;
}
