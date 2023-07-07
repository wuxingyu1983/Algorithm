// https://www.luogu.com.cn/problem/P3886

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

#define DEBUG 0
#define MAX_MN 10

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
int ans = INT32_MIN;
int cells[MAX_MN + 1][MAX_MN + 1];
int n, m;

long long setState(long long state, int pos, int val)
{
    long long ret = state;

    // clear
    ret &= ~(((long long)15) << (pos * 4));

    ret |= ((long long)val) << (pos * 4);

    return ret;
}

int getState(const long long state, const int pos)
{
    int ret = 0;

    if (0 <= pos)
    {
        ret = (state >> (4 * pos)) & 15;
    }

    return ret;
}

long long setAllState(const long long state, const int startPos, const int endPos, const int oldVal, const int newVal)
{
    long long ret = state;

    for (int i = startPos; i <= endPos; i++)
    {
        if (oldVal == getState(ret, i))
        {
            ret = setState(ret, i, newVal);
        }
    }

    return ret;
}

bool haveState(const long long state, const int startPos, const int endPos, const int val)
{
    bool ret = false;

    for (int i = startPos; i <= endPos; i++)
    {
        if (val == getState(state, i))
        {
            ret = true;
            break;
        }
    }

    return ret;
}

map<long long, int> cnts[MAX_MN + 1][MAX_MN + 1];
// int act = 0;        // 当前生效的 map
unsigned char flags[MAX_MN + 1][MAX_MN + 1];

bool stateRightful(long long state)
{
    bool ret = true;
    int pre = 0;

    for (int i = 1; i <= m; i++)
    {
        int st = getState(state, i);
        if (0 != st)
        {
            if (0 == pre)
            {
                pre = st;
            }
            else
            {
                if (pre != st)
                {
                    ret = false;
                    break;
                }
            }
        }
    }

    return ret;
}

int getLastIdx(long long state, int toPos)
{
    int ret = 0;

    for (size_t i = 1; i <= toPos; i++)
    {
        int idx = getState(state, i);
        if (idx > ret)
        {
            ret = idx;
        }
    }

    return ret;
}

long long preProc(long long state, int startPos, int endPos, int lastIdx)
{
    for (int i = startPos; i <= endPos; i++)
    {
        int st = getState(state, i);
        if (st > lastIdx)
        {
            state = setState(state, i, 8 + st);
        }
    }
    return state;
}

long long postProc(long long state)
{
    state = preProc(state, 1, m, 0);

    int idx = 1;

    for (int i = 1; i <= m; i++)
    {
        int st = getState(state, i);
        if (idx < st)
        {
            state = setAllState(state, i, m, st, idx);
            idx++;
        }
    }

    return state;
}

void insertLine(Line &line, int cnt)
{
    if (m == line.y)
    {
        line.state = postProc(line.state);
    }

    if (stateRightful(line.state))
    {
        if (cnt > ans)
        {
            ans = cnt;
        }
    }

    // 判断是否已经存在了
    map<long long, int>::iterator it = cnts[line.x][line.y].find(line.state);
    if (it == cnts[line.x][line.y].end())
    {
        cnts[line.x][line.y][line.state] = cnt;
        lines.push(line);
    }
    else
    {
        if (cnt > it->second)
        {
            cnts[line.x][line.y][line.state] = cnt;
        }
    }
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

#if DEBUG
    fscanf(fp, "%d", &n);
#else
    cin >> n;
#endif

    m = n;

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

            if (c > ans)
            {
                ans = c;
            }
        }
    }

    if (ans <= 0)
    {
        cout << ans << endl;
        return 0;
    }

    // start
    Line start;
    start.x = 0;
    start.y = m;
    start.state = 0;

    lines.push(start);

    flags[0][m] = 1;
    cnts[0][m][0] = 0;

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
            //            cnts[act].clear();
            //            act = 1 - act;
        }

        int pre_cnt = cnts[now_x][now_y][state];

        if (m == pre.y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                continue;
            }

            // pre process
            state = preProc(state, 1, m, 0);
        }
        else
        {
            now_y++;
        }

        int lastIdx = getLastIdx(state, now_y - 1);

        int i = getState(state, now_y - 1);
        int j = getState(state, now_y);

        // now_x, now_y 将要处理的cell
        // state 还未处理 (now_x, now_y) 的状态
        {
            // 忽略该 cell
            if (8 > j || haveState(state, now_y + 1, m, j) || haveState(state, 1, now_y - 1, j))
            {
                Line now;
                now.x = now_x;
                now.y = now_y;

                now.state = setState(state, now_y, 0);

                insertLine(now, pre_cnt);
            }
        }

        {
            Line now;
            now.x = now_x;
            now.y = now_y;

            if (0 == i && 0 == j)
            {
                now.state = setState(state, now_y, lastIdx + 1);

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
            else if (0 < i && 0 == j)
            {
                now.state = setState(state, now_y, i);

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
            else if (0 == i && 0 < j)
            {
                if (8 > j)
                {
                    now.state = state;

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
                else
                {
                    //  j >= 8
                    now.state = setAllState(state, now_y, m, j, lastIdx + 1);

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
            }
            else
            {
                // 0 < i && 0 < j
                if (i == j)
                {
                    now.state = state;

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
                else if (8 > j)
                {
                    if (i > j)
                    {
                        swap(i, j);
                    }
                    // i < j
                    now.state = setAllState(state, 1, m, j, i);

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
                else
                {
                    // j >= 8
                    now.state = setAllState(state, now_y, m, j, i);

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
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
