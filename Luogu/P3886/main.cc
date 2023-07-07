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
#define MAX_MN      10
#define MASK        7
#define BITS        3

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
int ans = INT32_MIN;
int cells[MAX_MN + 1][MAX_MN + 1];
int n, m;

int setState(int state, int pos, int val)
{
    // clear
    state &= ~(MASK << (pos * BITS));
    state |= val << (pos * BITS);

    return state;
}

int getState(int state, int pos)
{
    int ret = 0;

    if (0 <= pos)
    {
        ret = (state >> (BITS * pos)) & MASK;
    }

    return ret;
}

int setAllState(int state, const int startPos, const int endPos, const int oldVal, const int newVal)
{
    for (int i = startPos; i <= endPos; i++)
    {
        if (oldVal == getState(state, i))
        {
            state = setState(state, i, newVal);
        }
    }

    return state;
}

map<int, int> cnts[MAX_MN + 1][MAX_MN + 1];

bool can_use(int state)
{
    int tot0 = 0, tot1 = 0;
    for (int i = 1; i <= m; ++i)
    {
        tot0 += getState(state, i) == 0;
        tot1 += getState(state, i) == 1;
        if (getState(state, i) > 1)
        {
            return false;
        }
    }
    if (!tot1)
        return false;
    return true;
}

void min_express(int &zt)
{
    int tot = 0, id[MAX_MN] = {0};
    for (int i = 1; i <= m; ++i)
    {
        int now = getState(zt, i);
        if (!now)
            continue;
        if (id[now] != 0)
        {
            zt = setState(zt, i, id[now]);
        }
        else
        {
            zt = setState(zt, i, id[now] = ++tot);
        }
    }
}

void insertLine(Line &line, int cnt)
{
    min_express(line.state);

    if (can_use(line.state))
    {
        if (cnt > ans)
        {
            ans = cnt;
        }
    }
    
    // 判断是否已经存在了
    map<int, int>::iterator it = cnts[line.x][line.y].find(line.state);
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

int count(int zt, int val)
{
    int ret = -1;
    for (int i = 1; i <= m; ++i)
    {
        ret += (getState(zt, i) == val);
    }
    return ret;
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

    cnts[0][m][0] = 0;

    while (false == lines.empty())
    {
        Line pre = lines.front();
        lines.pop();

        int now_x = pre.x,
            now_y = pre.y;
        int state = pre.state;

        int pre_cnt = cnts[now_x][now_y][state];

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

        int i = getState(state, now_y - 1);
        int j = getState(state, now_y);
        
        // now_x, now_y 将要处理的cell
        // state 还未处理 (now_x, now_y) 的状态
        {
            // 忽略该 cell
            if (0 == j || count(state, j))
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
                now.state = setState(state, now_y, 7);

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
            else if (0 < i && 0 == j)
            {
                now.state = setState(state, now_y, i);

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
            else if (0 == i && 0 < j)
            {
                now.state = state;

                insertLine(now, pre_cnt + cells[now_x][now_y]);
            }
            else
            {
                // 0 < i && 0 < j
                if (i == j)
                {
                    now.state = state;

                    insertLine(now, pre_cnt + cells[now_x][now_y]);
                }
                else
                {
                    now.state = setAllState(state, 1, m, j, i);

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
