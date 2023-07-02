// https://vjudge.net/problem/UVALive-2738

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
#define MAX_N 1001

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

inline int setState(int state, int pos, int val)
{
    int ret = state;

    // clear
    ret &= ~(3 << pos);

    ret |= val << pos;

    return ret;
}

map<int, long long> cnts[2];
int act = 0; // 当前生效的 map
unsigned char flags[MAX_N][5];

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
        cnts[1 - act][line.state] = cnt + it->second;
    }
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    while (true)
    {
        string str_n;

        cin >> str_n;

        if ("#" == str_n)
        {
            break;
        }

        int n = stoi(str_n);

        // init
        cnts[0].clear();
        cnts[1].clear();
        act = 0;
        memset(flags, 0, MAX_N * 5);

        int m = 4;
        int end_x = n, end_y = 4;

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

                    insertLine(now, pre_cnt);
                }
            }
            else if (0 == i && 0 < j)
            {
                if (m > now_y)
                {
                    now.state = state;
                    insertLine(now, pre_cnt);
                }

                if (end_x > now_x)
                {
                    state = setState(state, (now_y - 1) * 2, j);
                    state = setState(state, now_y * 2, 0);

                    now.state = state;
                    insertLine(now, pre_cnt);
                }
            }
            else if (0 < i && 0 == j)
            {
                if (end_x > now_x)
                {
                    now.state = state;
                    insertLine(now, pre_cnt);
                }

                if (m > now_y)
                {
                    state = setState(state, (now_y - 1) * 2, 0);
                    state = setState(state, now_y * 2, i);

                    now.state = state;
                    insertLine(now, pre_cnt);
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
                            insertLine(now, pre_cnt);
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
                            insertLine(now, pre_cnt);
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
                insertLine(now, pre_cnt);
            }
            else if (1 == i && 2 == j)
            {
                if (end_x == now_x && end_y == now_y)
                {
                    state = setState(state, (now_y - 1) * 2, 0);
                    state = setState(state, now_y * 2, 0);

                    if (0 == state)
                    {
                        ans = pre_cnt;
                    }
                }
            }
        }

        cout << ans << endl;
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
