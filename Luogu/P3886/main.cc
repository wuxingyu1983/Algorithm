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

#define DEBUG       0
#define MAX_MN      9

class Line
{
public:
    /*
        已经处理过（x, y）格子后，状态为state的个数cnt
    */
    int x, y;
    long long state;
    int nextIdx;

    Line()
    {
        x = y = 0;
        state = 0;
        nextIdx = 0;
    }
};

queue<Line> lines;
int ans = INT32_MIN;
int cells[MAX_MN + 1][MAX_MN + 1];
int n, m;

inline long long setState(long long state, int pos, int val)
{
    long long ret = state;

    // 4 bits
    pos *= 4;

    // clear
    ret &= ~(15 << pos);

    ret |= val << pos;

    return ret;
}

inline int getState(const long long state, const int pos)
{
    int ret = 0;

    if (0 <= pos)
    {
        ret = (state >> (4 * pos)) & 15;
    }

    return ret;
}

inline long long setAllState(const long long state, const int startPos, const int m, const int oldVal, const int newVal)
{
    long long ret = state;

    for (size_t i = startPos; i <= m; i++)
    {
        if (oldVal == (state >> (4 * i)))
        {
            ret = setState(state, i, newVal);
        }
    }

    return ret; 
}

map<long long, int> cnts[2];
int act = 0;        // 当前生效的 map
unsigned char flags[MAX_MN + 1][MAX_MN + 1];

inline bool stateRightful(long long state)
{
    bool ret = true;
    int pre = 0;

    for (size_t i = 1; i <= m; i++)
    {
        if (0 != (state & 15))
        {
            if (0 == pre)
            {
                pre = state & 15;
            }
            else
            {
                if (pre != (state & 15))
                {
                    ret = false;
                    break;
                }
            }
        }

        state >>= 4;
    }

    return ret;
}

void insertLine(Line &line, int cnt)
{
    // 判断是否已经存在了
    map<long long, int>::iterator it = cnts[1 - act].find(line.state);
    if (it == cnts[1 - act].end())
    {
        cnts[1 - act][line.state] = cnt;
        lines.push(line);

        if (stateRightful(line.state))
        {
            if (cnt > ans)
            {
                ans = cnt;
            }
        }
    }
    else
    {
        if (cnt > it->second)
        {
            cnts[1 - act][line.state] = cnt;

            if (stateRightful(line.state))
            {
                if (cnt > ans)
                {
                    ans = cnt;
                }
            }
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
    start.nextIdx = 1;

    lines.push(start);

    flags[0][m] = 1;
    cnts[act][0] = 0;

    while (false == lines.empty())
    {
        Line pre = lines.front();
        lines.pop();

        int now_x = pre.x,
            now_y = pre.y;
        long long state = pre.state;
        int nxtIdx = pre.nextIdx;

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
            now_x ++;
            now_y = 1;

            if (n < now_x)
            {
                continue;
            }
        }
        else
        {
            now_y ++;
        }

        // now_x, now_y 将要处理的cell
        // state 还未处理 (now_x, now_y) 的状态

        {
            // 忽略该 cell 
            Line now;
            now.x = now_x;
            now.y = now_y;

            state = setState(state, now_y, 0);
            now.state = state;

            if (m == now_y)
            {
                if (1 & now_x)
                {
                    now.nextIdx = 9;    // 1001
                }
                else
                {
                    now.nextIdx = 1;    // 0001
                }
            }
            else
            {
                now.nextIdx = nxtIdx;
            }

            insertLine(now, pre_cnt);
        }

        {
            Line now;
            now.x = now_x;
            now.y = now_y;

            int i = getState(state, now_y - 1);
            int j = getState(state, now_y);

            if (0 == i && 0 == j)
            {
                state = setState(state, now_y, nxtIdx);
                now.state = state;
                now.nextIdx = ++ nxtIdx;

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
            else if (0 < i && 0 == j)
            {
                state = setState(state, now_y, i);
                now.state = state;
                now.nextIdx = nxtIdx;

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
            else if (0 == i && 0 < j)
            {
                if ((8 < nxtIdx && 8 < j) || (8 > nxtIdx && 8 > j))
                {
                    state = setState(state, now_y, j);
                    now.state = state;
                    now.nextIdx = nxtIdx;

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
                else
                {
                    state = setAllState(state, now_y, m, j, nxtIdx);
                    now.state = state;
                    now.nextIdx = ++nxtIdx;

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
            }
            else
            {
                // 0 < i && 0 < j
                if (i == j)
                {
                    state = setState(state, now_y, i);
                    now.state = state;
                    now.nextIdx = nxtIdx;

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
                else if ((8 < i && 8 < j) || (8 > i && 8 > j))
                {
                    state = setAllState(state, 1, m, j, i);
                    now.state = state;
                    now.nextIdx = nxtIdx;

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
                else
                {
                    state = setAllState(state, now_y, m, j, i);
                    now.state = state;
                    now.nextIdx = nxtIdx;

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
