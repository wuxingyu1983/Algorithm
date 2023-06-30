// https://www.luogu.com.cn/problem/P3190

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
#define MAX_N       100    
#define MAX_M       6

class Line
{
public:
    /*
        已经处理过（x, y）格子后，状态为state的个数cnt
    */
    int x, y;
    int state;

    Line()
    {
        x = y = 0;
        state = 0;
    }
};

queue<Line> lines;

int cells[MAX_N + 1][MAX_M + 1];        // 1 - obstacle

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
unsigned char flags[MAX_N + 1][MAX_M + 1];

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
        if (it->second < cnt)
        {
            cnts[1 - act][line.state] = cnt;
        }
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

    for (size_t row = 1; row <= n; row++)
    {
        for (size_t col = 1; col <= m; col++)
        {
            int c;
#if DEBUG
            fscanf(fp, "%d", &c);
#else
            cin >> c;
#endif

            cells[row][col] = c;
            end_x = row;
            end_y = col;
        }
    }

    // start
    Line start;
    start.x = 0;
    start.y = m;
    start.state = 0;

    lines.push(start);

    flags[0][m] = 1;
    cnts[act][0] = 0;

    long long ans = LONG_LONG_MIN;

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

        long long pre_cnt = cnts[act][state];

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

        int i = (state >> ((now_y - 1) * 2)) & 3;
        int j = (state >> (now_y * 2)) & 3;

        Line now;
        now.x = now_x;
        now.y = now_y;

        if (0 == i && 0 == j)
        {
            if (m > now_y && end_x > now_x)
            {
                state = setState(state, (now_y - 1) * 2, 1);
                state = setState(state, now_y * 2, 2);

                now.state = state;

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }

            // 忽略该cell
            {
                now.state = state;

                insertLine(now, pre_cnt);
            }
        }
        else if (0 == i && 0 < j)
        {
            if (m > now_y)
            {
                now.state = state;
                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }

            if (end_x > now_x)
            {
                state = setState(state, (now_y - 1) * 2, j);
                state = setState(state, now_y * 2, 0);

                now.state = state;
                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
        }
        else if (0 < i && 0 == j)
        {
            if (end_x > now_x)
            {
                now.state = state;
                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }

            if (m > now_y)
            {
                state = setState(state, (now_y - 1) * 2, 0);
                state = setState(state, now_y * 2, i);

                now.state = state;
                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
        }
        else if (1 == i && 1 == j)
        {
            state = setState(state, (now_y - 1) * 2, 0);
            state = setState(state, now_y * 2, 0);

            int pos = (now_y + 1) * 2;
            int s = 1;
            while (pos <= m * 2)
            {
                if (1 == ((state >> pos) & 3))
                {
                    s++;
                }
                else if (2 == ((state >> pos) & 3))
                {
                    s--;
                    if (0 == s)
                    {
                        state = setState(state, pos, 1);
                        now.state = state;
                        insertLine(now, pre_cnt + cells[now_x][now_y]);
                        break;
                    }
                }

                pos += 2;
            }
        }
        else if (2 == i && 2 == j)
        {
            state = setState(state, (now_y - 1) * 2, 0);
            state = setState(state, now_y * 2, 0);

            int pos = (now_y - 2) * 2;
            int s = 1;
            while (0 <= pos)
            {
                if (2 == ((state >> pos) & 3))
                {
                    s++;
                }
                else if (1 == ((state >> pos) & 3))
                {
                    s--;
                    if (0 == s)
                    {
                        state = setState(state, pos, 2);
                        now.state = state;
                        insertLine(now, pre_cnt + cells[now_x][now_y]);
                        break;
                    }
                }

                pos -= 2;
            }
        }
        else if (2 == i && 1 == j)
        {
            state = setState(state, (now_y - 1) * 2, 0);
            state = setState(state, now_y * 2, 0);
            now.state = state;
            insertLine(now, pre_cnt + cells[now_x][now_y]);
        }
        else if (1 == i && 2 == j)
        {
            state = setState(state, (now_y - 1) * 2, 0);
            state = setState(state, now_y * 2, 0);

            if (0 == state)
            {
                pre_cnt += cells[now_x][now_y];
                if (ans < pre_cnt)
                {
                    ans = pre_cnt;
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
