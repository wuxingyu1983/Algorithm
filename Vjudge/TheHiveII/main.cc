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
#define BITS 2
#define MASK3 63

int n, m;

unsigned char cells[MAX_N + 1][MAX_M + 1]; // 1 - obstacle

// pos : 0 - 同层插头 1，2，3 分别对应左下，正下，右下插头
#define setState4(ST, CELL, POS, VAL) \
    ST &= ~(((long long)MASK) << (((CELL) - 1) * CELL_BITS + (POS) * ST_BITS)); \
    ST |= ((long long)(VAL)) << (((CELL) - 1) * CELL_BITS + (POS) * ST_BITS);

#define setCellState(ST, CELL, VAL) \
    ST &= ~(((long long)MASK4) << (((CELL) - 1) * CELL_BITS)); \
    ST |= ((long long)(VAL)) << (((CELL - 1)) * CELL_BITS);

#define setState3(ST, POS, VAL) \
    ST &= ~(((long long)MASK3) << ((POS) * BITS)); \
    ST |= ((long long)(VAL)) << ((POS) * BITS);

#define setState(ST, POS, VAL) \
    ST &= ~(((long long)MASK) << ((POS) * 2));\
    ST |= ((long long)(VAL)) << ((POS) * 2);

#define getState2(ST, POS)  ((ST) >> ((POS) * 2)) & MASK

#define getState(ST, CELL, POS) ((ST) >> (((CELL) - 1) * CELL_BITS + (POS) * ST_BITS)) & MASK

unordered_map<long long, int> cnts[2]; // key - state, value - state 在 qs 中的位置 index
int act = 0;                           // 当前生效的 map

class StAndCnt
{
public:
    long long st;
    long long cnt;

    StAndCnt()
    {
        st = cnt = 0;
    }
};

StAndCnt qs[2][Q_SIZE];
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

#define insertState(ST, CNT)   \
{\
    unordered_map<long long, int>::iterator it = cnts[1 - act].find(ST);\
    if (it != cnts[1 - act].end())\
    {\
        qs[1 - act][it->second].cnt += CNT;\
    }\
    else\
    {\
        qs[1 - act][qTail[1 - act]].st = ST;\
        qs[1 - act][qTail[1 - act]].cnt = CNT;\
        cnts[1 - act][state] = qTail[1 - act];\
        qTail[1 - act]++;\
    }\
}

int main()
{
    long long tmp;
    while (scanf("%d %d", &n, &m))
    {
        if (8 < n)
        {
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
            cnts[act][0] = 0;
            qs[act][0].st = 0;
            qs[act][0].cnt = 1;
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
                            long long state = qs[act][iQs].st;
                            long long pre_cnt = qs[act][iQs].cnt;
                            // 同 col 上一个 cell 的 右下插头，由于接下来的处理过程会清除掉该状态，将其移到后一列cell中
                            int k = getState(state, now_y, 3);
                            if (k)
                            {
                                setState4(state, now_y + 1, 1, k);
                                setCellState(state, now_y, 0);
                            }

                            cnts[1 - act][state] = iQs;
                            qs[1 - act][qTail[1 - act]].st = state;
                            qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                            qTail[1 - act]++;
                        }

                        cnts[act].clear();
                        qTail[act] = 0;
                        act = 1 - act;
                    }
                    continue;
                }

                // (now_x, now_y) 将要处理的 cell
                if (now_y & 1)
                {
                    for (size_t iQs = 0; iQs < qTail[act]; iQs++)
                    {
                        long long state = qs[act][iQs].st;
                        long long pre_cnt = qs[act][iQs].cnt;

                        // 2 in, 4 out
                        int i = 0, j = 0;
                        if (1 < now_y)
                        {
                            // 同 row 上一个 cell 的 同层插头
                            i = getState(state, now_y - 1, 0); // 一个 cell 用 8 bits 表示，4 个边
                            // 清空
                            if (i)
                            {
                                setState4(state, now_y - 1, 0, 0);
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

                                setState4(state, now_y + 1, 1, k);
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
                                    setCellState(state, now_y, (1 << 2) + (2 << 4));
                                    insertState(state, pre_cnt);
                                }

                                if (m > now_y && 0 == cells[now_x + 1][now_y + 1])
                                {
                                    // 1, 3
                                    setCellState(state, now_y, (1 << 2) + (2 << 6));
                                    insertState(state, pre_cnt);
                                }

                                if (m > now_y && 0 == cells[now_x][now_y + 1])
                                {
                                    // 1, 0
                                    setCellState(state, now_y, (1 << 2) + (2 << 0));
                                    insertState(state, pre_cnt);
                                }
                            }

                            if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y])
                            {
                                if (0 == cells[now_x + 1][now_y + 1])
                                {
                                    // 2, 3
                                    setCellState(state, now_y, (1 << 4) + (2 << 6));
                                    insertState(state, pre_cnt);
                                }

                                if (0 == cells[now_x][now_y + 1])
                                {
                                    // 2, 0
                                    setCellState(state, now_y, (1 << 4) + (2 << 0));
                                    insertState(state, pre_cnt);
                                }
                            }

                            if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y + 1] && 0 == cells[now_x][now_y + 1])
                            {
                                // 3, 0
                                setCellState(state, now_y, (1 << 6) + (2 << 0));
                                insertState(state, pre_cnt);
                            }
                        }
                        else if ((0 == i && 0 < j) || (0 < i && 0 == j))
                        {
                            int st = i + j;

                            if (1 < now_y && n > now_x && 0 == cells[now_x + 1][now_y - 1])
                            {
                                // 1
                                setCellState(state, now_y, st << 2);
                                insertState(state, pre_cnt);
                            }

                            if (n > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                // 2
                                setCellState(state, now_y, st << 4);
                                insertState(state, pre_cnt);
                            }

                            if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y + 1])
                            {
                                // 3
                                setCellState(state, now_y, st << 6);
                                insertState(state, pre_cnt);
                            }

                            if (m > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                // 0
                                setCellState(state, now_y, st << 0);
                                insertState(state, pre_cnt);
                            }
                        }
                        else if (1 == i && 1 == j)
                        {
                            setCellState(state, now_y, 0);
                            state = proc11(state, now_y);

                            insertState(state, pre_cnt);
                        }
                        else if (2 == i && 2 == j)
                        {
                            setCellState(state, now_y, 0);
                            state = proc22(state, now_y);

                            insertState(state, pre_cnt);
                        }
                        else
                        {
                            // 1, 2 or 2, 1
                            setCellState(state, now_y, 0);

                            insertState(state, pre_cnt);

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
                }
                else
                {
                    for (size_t iQs = 0; iQs < qTail[act]; iQs++)
                    {
                        long long state = qs[act][iQs].st;
                        long long pre_cnt = qs[act][iQs].cnt;

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
                                setState4(state, now_y - 1, 0, 0);

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
                                setState4(state, now_y + 1, 1, 0);

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
                                setCellState(state, now_y, (1 << 4) + (2 << 0));
                                insertState(state, pre_cnt);
                            }
                        }
                        else if (1 == cnt)
                        {
                            if (n > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                // 2
                                setCellState(state, now_y, st << 4);
                                insertState(state, pre_cnt);
                            }

                            if (m > now_y && 0 == cells[now_x][now_y + 1])
                            {
                                // 0
                                setCellState(state, now_y, st << 0);
                                insertState(state, pre_cnt);
                            }
                        }
                        else if (2 == cnt)
                        {
                            if (2 == st)
                            {
                                // 1, 1
                                setCellState(state, now_y, 0);
                                state = proc11(state, now_y);
                                insertState(state, pre_cnt);
                            }
                            else if (4 == st)
                            {
                                // 2, 2
                                setCellState(state, now_y, 0);
                                state = proc22(state, now_y);
                                insertState(state, pre_cnt);
                            }
                            else
                            {
                                // 1, 2 or 2, 1
                                setCellState(state, now_y, 0);
                                insertState(state, pre_cnt);

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
        else
        {
            // init
            cnts[0].clear();
            cnts[1].clear();
            act = 0;
            long long ans = 0;
            memset(cells, 0, sizeof(cells));
            qTail[0] = 0;
            qTail[1] = 0;

            char str[5];

            for (int i = 0; i < m; i++)
            {
                scanf("%s", str);

                int c = str[0] - 'A' + 1;
                int r = str[1] - 'A' + 1;

                cells[r][c] = 1;
            }

            m = n;
            n = 8;

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
            cnts[act][0] = 0;
            qs[act][0].st = 0;
            qs[act][0].cnt = 1;
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
                    if (0 == (now_x & 1) && 1 == now_y)
                    {
                        for (size_t iQs = 0; iQs < qTail[act]; iQs++)
                        {
                            long long state = qs[act][iQs].st;
                            long long pre_cnt = qs[act][iQs].cnt;

                            state <<= 2 * BITS;

                            cnts[1 - act][state] = iQs;
                            qs[1 - act][qTail[1 - act]].st = state;
                            qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                            qTail[1 - act]++;
                        }

                        cnts[act].clear();
                        qTail[act] = 0;
                        act = 1 - act;
                    }
                    continue;
                }

                // (now_x, now_y) 将要处理的 cell
                for (size_t iQs = 0; iQs < qTail[act]; iQs++)
                {
                    long long state = qs[act][iQs].st;
                    long long pre_cnt = qs[act][iQs].cnt;

                    if (0 == (now_x & 1) && 1 == now_y)
                    {
                        state <<= 2 * BITS;
                    }

                    int i = getState2(state, 2 * (now_y - 1));
                    int j = getState2(state, 2 * (now_y - 1) + 1);
                    int k = getState2(state, 2 * now_y);

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
                                    setState3(state, 2 * (now_y - 1), 9);
                                    insertState(state, pre_cnt);
                                }

                                if (0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                                {
                                    setState3(state, 2 * (now_y - 1), 33);
                                    insertState(state, pre_cnt);
                                }

                                if (0 == cells[now_x + 1][now_y + 1] && 0 == cells[now_x][now_y + 1])
                                {
                                    setState3(state, 2 * (now_y - 1), 36);
                                    insertState(state, pre_cnt);
                                }
                            }
                        }
                        else
                        {
                            if (n > now_x)
                            {
                                if (1 < now_y && 0 == cells[now_x + 1][now_y - 1] && 0 == cells[now_x + 1][now_y])
                                {
                                    setState3(state, 2 * (now_y - 1), 9);
                                    insertState(state, pre_cnt);
                                }

                                if (1 < now_y && m > now_y && 0 == cells[now_x + 1][now_y - 1] && 0 == cells[now_x][now_y + 1])
                                {
                                    setState3(state, 2 * (now_y - 1), 33);
                                    insertState(state, pre_cnt);
                                }

                                if (m > now_y && 0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                                {
                                    setState3(state, 2 * (now_y - 1), 36);
                                    insertState(state, pre_cnt);
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
                                setState3(state, 2 * (now_y - 1), st);
                                insertState(state, pre_cnt);
                            }

                            if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y + 1])
                            {
                                setState3(state, 2 * (now_y - 1), st * 4);
                                insertState(state, pre_cnt);
                            }
                        }
                        else
                        {
                            if (n > now_x && 1 < now_y && 0 == cells[now_x + 1][now_y - 1])
                            {
                                setState3(state, 2 * (now_y - 1), st);
                                insertState(state, pre_cnt);
                            }

                            if (n > now_x && 0 == cells[now_x + 1][now_y])
                            {
                                setState3(state, 2 * (now_y - 1), st * 4);
                                insertState(state, pre_cnt);
                            }
                        }

                        if (m > now_y && 0 == cells[now_x][now_y + 1])
                        {
                            setState3(state, 2 * (now_y - 1), st * 16);
                            insertState(state, pre_cnt);
                        }
                    }
                    else if (2 == cnt)
                    {
                        if (2 == st)
                        {
                            // 1, 1
                            setState3(state, 2 * (now_y - 1), 0);

                            int pos = 2 * now_y + 1;
                            int s = 1;
                            while (pos <= m * 2)
                            {
                                int st = getState2(state, pos);
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
                                        insertState(state, pre_cnt);
                                        break;
                                    }
                                }

                                pos++;
                            }
                        }
                        else if (4 == st)
                        {
                            // 2, 2
                            setState3(state, 2 * (now_y - 1), 0);

                            int pos = 2 * (now_y - 1) - 1;
                            int s = 1;
                            while (0 <= pos)
                            {
                                int st = getState2(state, pos);
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
                                        insertState(state, pre_cnt);
                                        break;
                                    }
                                }

                                pos--;
                            }
                        }
                        else if (3 == st)
                        {
                            // 1, 2 or 2, 1
                            setState3(state, 2 * (now_y - 1), 0);
                            insertState(state, pre_cnt);

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

                cnts[act].clear();
                qTail[act] = 0;
                act = 1 - act;
            }

            printf("%lld\n", ans);
        }
    }

    return 0;
}
