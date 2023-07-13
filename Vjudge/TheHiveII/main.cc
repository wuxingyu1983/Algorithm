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
#define MAX_N 10 // row
#define MAX_M 8  // col
#define ST_BITS 2
#define CELL_BITS 8
#define MASK 3
#define MASK4 255
#define Q_SIZE 800000

int n, m;

unsigned char cells[MAX_N + 1][MAX_M + 1]; // 1 - obstacle

// pos : 0 - 同层插头 1，2，3 分别对应左下，正下，右下插头
inline long long setState(long long state, int cell, int pos, int val)
{
    long long ret = state;
    cell--;
    // clear
    ret &= ~(((long long)MASK) << (cell * CELL_BITS + pos * ST_BITS));

    ret |= ((long long)val) << (cell * CELL_BITS + pos * ST_BITS);

    return ret;
}
inline long long setCellState(long long state, int cell, int val)
{
    long long ret = state;
    cell--;

    // clear
    ret &= ~(((long long)MASK4) << (cell * CELL_BITS));

    ret |= ((long long)val) << (cell * CELL_BITS);

    return ret;
}

inline int getState(long long st, int cell, int pos)
{
    int ret = 0;
    cell--;

    ret = (st >> (cell * CELL_BITS + pos * ST_BITS)) & MASK;

    return ret;
}

inline int getState(long long st, int pos)
{
    int ret = 0;

    ret = (st >> (pos * 2)) & MASK;

    return ret;
}

inline long long setState(long long state, int pos, int val)
{
    long long ret = state;

    // clear
    ret &= ~(((long long)MASK) << (pos * 2));

    ret |= ((long long)val) << (pos * 2);

    return ret;
}

unordered_map<long long, long long> cnts[2];
int act = 0; // 当前生效的 map
long long qs[2][Q_SIZE];
int qTail[2];

inline long long proc11(long long state, int pos)
{
    pos *= 4;
    int s = 1;
    while (pos < m * 4)
    {
        int st = (state >> (pos * 2)) & MASK;
        if (1 == st)
        {
            s++;
        }
        else if (2 == st)
        {
            s--;
            if (0 == s)
            {
                state &= ~(((long long)MASK) << (pos * 2));
                state |= ((long long)1) << (pos * 2);
                break;
            }
        }

        pos++;
    }

    return state;
}

inline long long proc22(long long state, int pos)
{
    pos = 4 * (pos - 1) - 1;
    int s = 1;
    while (0 <= pos)
    {
        int st = (state >> (pos * 2)) & MASK;
        if (2 == st)
        {
            s++;
        }
        else if (1 == st)
        {
            s--;
            if (0 == s)
            {
                state &= ~(((long long)MASK) << (pos * 2));
                state |= ((long long)2) << (pos * 2);
                break;
            }
        }

        pos--;
    }

    return state;
}

int main()
{
    long long tmp;
    while (scanf("%d %d", &n, &m))
    {
        if (0 >= n)
        {
            break;
        }

        // init
        act = 0;
        long long ans = 0;
        memset(cells, 0, sizeof(cells));
        qTail[0] = 0;
        qTail[1] = 0;

        char str[5];

        for (int i = 0; i < m; i++)
        {
            scanf("%s", str);

            int r = str[0] - 'A' + 1;
            int c = str[1] - 'A' + 1;

            cells[r][c] = 1;
        }

        m = MAX_M;

        int end_x = 0, end_y = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (0 == cells[i][j])
                {
                    end_x = i;
                    end_y = j;
                }
            }
        }

        // start
        cnts[act][0] = 1;
        qs[act][0] = 0;
        qTail[act]++;

        int now_x = 0;
        int now_y = m;

        while (qTail[act])
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

            if (1 == cells[now_x][now_y])
            {
                if (now_y & 1 && m > now_y)
                {
                    for (size_t iQs = 0; iQs < qTail[act]; iQs++)
                    {
                        long long state = qs[act][iQs];
                        long long pre_cnt = cnts[act][state];
                        // 同 col 上一个 cell 的 右下插头，由于接下来的处理过程会清除掉该状态，将其移到后一列cell中
                        int k = getState(state, now_y, 3);
                        if (k)
                        {
                            state = setState(state, now_y + 1, 1, k);
                            state = setCellState(state, now_y, 0);
                        }

                        cnts[1 - act][state] = pre_cnt;
                        qs[1 - act][qTail[1 - act]++] = state;
                    }

                    cnts[act].clear();
                    qTail[act] = 0;
                    act = 1 - act;
                }
                continue;
            }

            for (size_t iQs = 0; iQs < qTail[act]; iQs++)
            {
                long long state = qs[act][iQs];
                long long pre_cnt = cnts[act][state];

                // (now_x, now_y) 将要处理的 cell
                if (now_y & 1)
                {
                    // 2 in, 4 out
                    int i = 0, j = 0;
                    if (1 < now_y)
                    {
                        // 同 row 上一个 cell 的 同层插头
                        i = getState(state, now_y - 1, 0); // 一个 cell 用 8 bits 表示，4 个边
                        // 清空
                        if (i)
                        {
                            state = setState(state, now_y - 1, 0, 0);
                        }
                    }
                    if (1 < now_x)
                    {
                        // 同 col 上一个 cell 的 正下插头
                        j = getState(state, now_y, 2); // 一个 cell 用 8 bits 表示，4 个边

                        if (m > now_y)
                        {
                            // 同 col 上一个 cell 的 右下插头，由于接下来的处理过程会清除掉该状态，将其移到后一列cell中
                            int k = getState(state, now_y, 3);

                            state = setState(state, now_y + 1, 1, k);
                        }
                    }

                    if (0 == i && 0 == j)
                    {
                        // 6 种可能性
                        if (1 < now_y && n > now_x && 0 == cells[now_x + 1][now_y - 1])
                        {
                            if (0 == cells[now_x + 1][now_y])
                            {
                                // 1, 2插头
                                state = setCellState(state, now_y, (1 << 2) + (2 << 4));

                                if (tmp = cnts[1 - act][state])
                                {
                                    cnts[1 - act][state] = tmp + pre_cnt;
                                }
                                else
                                {
                                    cnts[1 - act][state] = pre_cnt;
                                    qs[1 - act][qTail[1 - act]++] = state;
                                }
                            }

                            if (m > now_y && 0 == cells[now_x + 1][now_y + 1])
                            {
                                // 1, 3
                                state = setCellState(state, now_y, (1 << 2) + (2 << 6));

                                if (tmp = cnts[1 - act][state])
                                {
                                    cnts[1 - act][state] = tmp + pre_cnt;
                                }
                                else
                                {
                                    cnts[1 - act][state] = pre_cnt;
                                    qs[1 - act][qTail[1 - act]++] = state;
                                }
                            }

                            if (m > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                // 1, 0
                                state = setCellState(state, now_y, (1 << 2) + (2 << 0));

                                if (tmp = cnts[1 - act][state])
                                {
                                    cnts[1 - act][state] = tmp + pre_cnt;
                                }
                                else
                                {
                                    cnts[1 - act][state] = pre_cnt;
                                    qs[1 - act][qTail[1 - act]++] = state;
                                }
                            }
                        }

                        if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y])
                        {
                            if (0 == cells[now_x + 1][now_y + 1])
                            {
                                // 2, 3
                                state = setCellState(state, now_y, (1 << 4) + (2 << 6));

                                if (tmp = cnts[1 - act][state])
                                {
                                    cnts[1 - act][state] = tmp + pre_cnt;
                                }
                                else
                                {
                                    cnts[1 - act][state] = pre_cnt;
                                    qs[1 - act][qTail[1 - act]++] = state;
                                }
                            }

                            if (0 == cells[now_x][now_y + 1])
                            {
                                // 2, 0
                                state = setCellState(state, now_y, (1 << 4) + (2 << 0));

                                if (tmp = cnts[1 - act][state])
                                {
                                    cnts[1 - act][state] = tmp + pre_cnt;
                                }
                                else
                                {
                                    cnts[1 - act][state] = pre_cnt;
                                    qs[1 - act][qTail[1 - act]++] = state;
                                }
                            }
                        }

                        if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y + 1] && 0 == cells[now_x][now_y + 1])
                        {
                            // 3, 0
                            state = setCellState(state, now_y, (1 << 6) + (2 << 0));

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }
                    }
                    else if ((0 == i && 0 < j) || (0 < i && 0 == j))
                    {
                        int st = i + j;

                        if (1 < now_y && n > now_x && 0 == cells[now_x + 1][now_y - 1])
                        {
                            // 1
                            state = setCellState(state, now_y, st << 2);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }

                        if (n > now_x && 0 == cells[now_x + 1][now_y])
                        {
                            // 2
                            state = setCellState(state, now_y, st << 4);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }

                        if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y + 1])
                        {
                            // 3
                            state = setCellState(state, now_y, st << 6);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }

                        if (m > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            // 0
                            state = setCellState(state, now_y, st << 0);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }
                    }
                    else if (1 == i && 1 == j)
                    {
                        state = setCellState(state, now_y, 0);
                        state = proc11(state, now_y);

                        if (tmp = cnts[1 - act][state])
                        {
                            cnts[1 - act][state] = tmp + pre_cnt;
                        }
                        else
                        {
                            cnts[1 - act][state] = pre_cnt;
                            qs[1 - act][qTail[1 - act]++] = state;
                        }
                    }
                    else if (2 == i && 2 == j)
                    {
                        state = setCellState(state, now_y, 0);
                        state = proc22(state, now_y);

                        if (tmp = cnts[1 - act][state])
                        {
                            cnts[1 - act][state] = tmp + pre_cnt;
                        }
                        else
                        {
                            cnts[1 - act][state] = pre_cnt;
                            qs[1 - act][qTail[1 - act]++] = state;
                        }
                    }
                    else
                    {
                        // 1, 2 or 2, 1
                        state = setCellState(state, now_y, 0);

                        if (tmp = cnts[1 - act][state])
                        {
                            cnts[1 - act][state] = tmp + pre_cnt;
                        }
                        else
                        {
                            cnts[1 - act][state] = pre_cnt;
                            qs[1 - act][qTail[1 - act]++] = state;
                        }

                        if (1 == i && 2 == j)
                        {
                            if (end_x == now_x && end_y == now_y)
                            {
                                if (0 == state)
                                {
                                    ans += pre_cnt;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // 4 in, 2 out
                    int i = 0, j = 0, k = 0, l = 0;
                    int cnt = 0;
                    int st = 0;
                    int pos1 = 0, pos2 = 0;

                    // 同层上一个cell的插头
                    if (1 < now_y)
                    {
                        if (i = getState(state, now_y - 1, 0))
                        {
                            cnt++;
                            st += i;

                            // clear
                            state = setState(state, now_y - 1, 0, 0);

                            if (1 == i)
                            {
                                pos1 = 0;
                            }
                            else
                            {
                                pos2 = 0;
                            }
                        }
                    }

                    // 上层 左下，正下 插头
                    if (j = getState(state, now_y, 1))
                    {
                        cnt++;
                        st += j;

                        if (1 == j)
                        {
                            pos1 = 1;
                        }
                        else if (2 == j)
                        {
                            pos2 = 1;
                        }
                    }

                    if (k = getState(state, now_y, 2))
                    {
                        cnt++;
                        st += k;

                        if (1 == k)
                        {
                            pos1 = 2;
                        }
                        else if (2 == k)
                        {
                            pos2 = 2;
                        }
                    }

                    // 上层下一列的左下插头
                    if (m > now_y)
                    {
                        if (l = getState(state, now_y + 1, 1))
                        {
                            cnt++;
                            st += l;

                            // clean
                            state = setState(state, now_y + 1, 1, 0);

                            if (1 == l)
                            {
                                pos1 = 3;
                            }
                            else
                            {
                                pos2 = 3;
                            }
                        }
                    }

                    if (0 == cnt)
                    {
                        if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                        {
                            // 2, 0
                            state = setCellState(state, now_y, (1 << 4) + (2 << 0));

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }
                    }
                    else if (1 == cnt)
                    {
                        if (n > now_x && 0 == cells[now_x + 1][now_y])
                        {
                            // 2
                            state = setCellState(state, now_y, st << 4);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }

                        if (m > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            // 0
                            state = setCellState(state, now_y, st << 0);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }
                    }
                    else if (2 == cnt)
                    {
                        if (2 == st)
                        {
                            // 1, 1
                            state = setCellState(state, now_y, 0);
                            state = proc11(state, now_y);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }
                        else if (4 == st)
                        {
                            // 2, 2
                            state = setCellState(state, now_y, 0);
                            state = proc22(state, now_y);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }
                        }
                        else
                        {
                            // 1, 2 or 2, 1
                            state = setCellState(state, now_y, 0);

                            if (tmp = cnts[1 - act][state])
                            {
                                cnts[1 - act][state] = tmp + pre_cnt;
                            }
                            else
                            {
                                cnts[1 - act][state] = pre_cnt;
                                qs[1 - act][qTail[1 - act]++] = state;
                            }

                            if (pos1 < pos2)
                            {
                                if (end_x == now_x && end_y == now_y)
                                {
                                    if (0 == state)
                                    {
                                        ans += pre_cnt;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            cnts[act].clear();
            qTail[act] = 0;
            act = 1 - act;
        }

        printf("%lld\n", ans);
    }

    return 0;
}
