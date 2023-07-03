// https://www.luogu.com.cn/problem/P3272

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

#define DEBUG       0
#define MAX_MN      100
#define MOD         20110520

class Line
{
public:
    /*
        已经处理过（x, y）格子后，状态为state的个数cnt
    */
    int x, y;
    int state;      // 每 2 bits 表示一条边的状态，0 - 没有插头，其余的表示有插头，1 - 还未经过拐角， 2 - 拐角的插头，3 - 经过了拐角，至少延长了一个cell的插头

    Line()
    {
        x = y = 0;
        state = 0;
    }
};

queue<Line> lines;

unsigned char cells[MAX_MN + 1][MAX_MN + 1];        // 1 - obstacle

inline int setState(int state, int pos, int val)
{
    int ret = state;

    // clear
    ret &= ~(3 << pos);

    ret |= val << pos;

    return ret;
}

map<int, long long> cnts[2];
int act = 0;        // 当前生效的 map
unsigned char flags[MAX_MN + 1][MAX_MN + 1];

void insertLine(Line &line, long long cnt)
{
    // 判断是否已经存在了
    map<int, long long>::iterator it = cnts[1 - act].find(line.state);
    if (it == cnts[1 - act].end())
    {
        cnts[1 - act][line.state] = cnt;
        lines.push(line);
    }
    else
    {
        cnts[1 - act][line.state] = (cnt + it->second) % MOD;
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

    // m 取小的那一个
    if (n >= m)
    {
        for (size_t row = 1; row <= n; row++)
        {
            for (size_t col = 1; col <= m; col++)
            {
                char c;
#if DEBUG
                fscanf(fp, "%c", &c);
#else
                cin >> c;
#endif
                if ('*' == c)
                {
                    cells[row][col] = 1;
                }
                else
                {
                    end_x = row;
                    end_y = col;
                }
            }
        }
    }
    else
    {
        // n < m
        for (size_t row = 1; row <= n; row++)
        {
            for (size_t col = 1; col <= m; col++)
            {
                char c;
#if DEBUG
                fscanf(fp, "%c", &c);
#else
                cin >> c;
#endif
                if ('*' == c)
                {
                    cells[col][row] = 1;
                }
                else
                {
                    end_x = col;
                    end_y = row;
                }
            }
        }

        swap(n, m);
    }

    // start
    Line start;
    start.x = 0;
    start.y = m;
    start.state = 0;

    lines.push(start);

    flags[0][m] = 1;
    cnts[act][0] = 1;

    int ans = 0;

    while (false == lines.empty())
    {
        Line pre = lines.front();
        lines.pop();

        int now_x = pre.x,
            now_y = pre.y;
        int state = pre.state;

        if (0 == flags[now_x][now_y])
        {
            // 第一次访问 (now_x, now_y)
            flags[now_x][now_y] = 1;
            cnts[act].clear();
            act = 1 - act;
        }

        int pre_cnt = cnts[act][state];

        if (m == pre.y)
        {
            now_x++;
            now_y = 1;
            state <<= 2;
        }
        else
        {
            now_y++;
        }

        if (1 == cells[now_x][now_y])
        {
            // 障碍物
            Line now;
            now.x = now_x;
            now.y = now_y;
            now.state = state;

            insertLine(now, pre_cnt);
        }
        else
        {
            int i = (state >> ((now_y - 1) * 2)) & 3;
            int j = (state >> (now_y * 2)) & 3;

            Line now;
            now.x = now_x;
            now.y = now_y;

            if (0 == i && 0 == j)
            {
                if (m > now_y && end_x > now_x && 0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                {
                    state = setState(state, (now_y - 1) * 2, 2);
                    state = setState(state, now_y * 2, 2);

                    now.state = state;

                    insertLine(now, pre_cnt);
                }

                if (m > now_y && 0 == cells[now_x][now_y + 1])
                {
                    state = setState(state, (now_y - 1) * 2, 0);
                    state = setState(state, now_y * 2, 1);

                    now.state = state;

                    insertLine(now, pre_cnt);
                }

                if (n > now_x && 0 == cells[now_x + 1][now_y])
                {
                    state = setState(state, (now_y - 1) * 2, 1);
                    state = setState(state, now_y * 2, 0);

                    now.state = state;

                    insertLine(now, pre_cnt);
                }
            }
            else if (0 == i && 0 < j)
            {
                if (1 == j)
                {
                    if (n > now_x && 0 == cells[now_x + 1][now_y])
                    {
                        state = setState(state, (now_y - 1) * 2, 1);
                        state = setState(state, now_y * 2, 0);

                        now.state = state;
                        insertLine(now, pre_cnt);
                    }

                    if (m > now_y && 0 == cells[now_x][now_y + 1])
                    {
                        state = setState(state, (now_y - 1) * 2, 0);
                        state = setState(state, now_y * 2, 2);

                        now.state = state;
                        insertLine(now, pre_cnt);
                    }
                }
                else
                {
                    // j == 2 or 3
                    if (n > now_x && 0 == cells[now_x + 1][now_y])
                    {
                        state = setState(state, (now_y - 1) * 2, 3);
                        state = setState(state, now_y * 2, 0);

                        now.state = state;
                        insertLine(now, pre_cnt);
                    }

                    {
                        // 就此打住了
                        state = setState(state, (now_y - 1) * 2, 0);
                        state = setState(state, now_y * 2, 0);

                        if (end_x == now_x && end_y == now_y)
                        {
                            if (0 == state)
                            {
                                ans += pre_cnt;
                                ans &= MOD;
                            }
                        }
                        else
                        {
                            now.state = state;
                            insertLine(now, pre_cnt);
                        }
                    }
                }
            }
            else if (0 < i && 0 == j)
            {
                if (1 == i)
                {
                    if (n > now_x && 0 == cells[now_x + 1][now_y])
                    {
                        state = setState(state, (now_y - 1) * 2, 2);
                        state = setState(state, now_y * 2, 0);

                        now.state = state;
                        insertLine(now, pre_cnt);
                    }

                    if (m > now_y && 0 == cells[now_x][now_y + 1])
                    {
                        state = setState(state, (now_y - 1) * 2, 0);
                        state = setState(state, now_y * 2, 1);

                        now.state = state;
                        insertLine(now, pre_cnt);
                    }
                }
                else
                {
                    // i == 2 or 3
                    if (m > now_y && 0 == cells[now_x][now_y + 1])
                    {
                        state = setState(state, (now_y - 1) * 2, 0);
                        state = setState(state, now_y * 2, 3);

                        now.state = state;
                        insertLine(now, pre_cnt);
                    }

                    {
                        // 就此打住了
                        state = setState(state, (now_y - 1) * 2, 0);
                        state = setState(state, now_y * 2, 0);

                        if (end_x == now_x && end_y == now_y)
                        {
                            if (0 == state)
                            {
                                ans += pre_cnt;
                                ans &= MOD;
                            }
                        }
                        else
                        {
                            now.state = state;
                            insertLine(now, pre_cnt);
                        }
                    }
                }
            }
            else if (1 == i && 1 == j)
            {
                state = setState(state, (now_y - 1) * 2, 0);
                state = setState(state, now_y * 2, 0);

                if (end_x == now_x && end_y == now_y)
                {
                    if (0 == state)
                    {
                        ans += pre_cnt;
                        ans &= MOD;
                    }
                }
                else
                {
                    now.state = state;
                    insertLine(now, pre_cnt);
                }
            }
        }
    }

    cout << ans << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
