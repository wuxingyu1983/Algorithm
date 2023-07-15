// https://vjudge.net/problem/ZOJ-3466

#include <cmath>
#include <cstdio>
#include <vector>
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
#define Q_SIZE  2320000     // line queue size

int n, m;

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

int main()
{
    while (scanf("%d %d", &n, &m))
    {
        // init
        cnts[0].clear();
        cnts[1].clear();
        act = 0;
        long long ans = 0;
        memset(cells, 0, sizeof(cells));
        qTail[0] = 0;
        qTail[1] = 0;

        char str[20];

        for (int i = 0; i < m; i++)
        {
            scanf("%s", str);

            int c = str[0] - 'A' + 1;
            int r = str[1] - 'A' + 1;

            cells[r][c] = 1;
        }

        m = n;
        n = MAX_N;

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

                                unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                if (it != cnts[1 - act].end())
                                {
                                    qs[1 - act][it->second].cnt += pre_cnt;
                                }
                                else
                                {
                                    qs[1 - act][qTail[1 - act]].st = state;
                                    qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                    cnts[1 - act][state] = qTail[1 - act];
                                    qTail[1 - act]++;
                                }
                            }

                            if (0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                            {
                                state = setState3(state, 2 * (now_y - 1), 33);

                                unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                if (it != cnts[1 - act].end())
                                {
                                    qs[1 - act][it->second].cnt += pre_cnt;
                                }
                                else
                                {
                                    qs[1 - act][qTail[1 - act]].st = state;
                                    qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                    cnts[1 - act][state] = qTail[1 - act];
                                    qTail[1 - act]++;
                                }
                            }

                            if (0 == cells[now_x + 1][now_y + 1] && 0 == cells[now_x][now_y + 1])
                            {
                                state = setState3(state, 2 * (now_y - 1), 36);
                                unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                if (it != cnts[1 - act].end())
                                {
                                    qs[1 - act][it->second].cnt += pre_cnt;
                                }
                                else
                                {
                                    qs[1 - act][qTail[1 - act]].st = state;
                                    qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                    cnts[1 - act][state] = qTail[1 - act];
                                    qTail[1 - act]++;
                                }
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
                                unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                if (it != cnts[1 - act].end())
                                {
                                    qs[1 - act][it->second].cnt += pre_cnt;
                                }
                                else
                                {
                                    qs[1 - act][qTail[1 - act]].st = state;
                                    qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                    cnts[1 - act][state] = qTail[1 - act];
                                    qTail[1 - act]++;
                                }
                            }

                            if (1 < now_y && m > now_y && 0 == cells[now_x + 1][now_y - 1] && 0 == cells[now_x][now_y + 1])
                            {
                                state = setState3(state, 2 * (now_y - 1), 33);
                                unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                if (it != cnts[1 - act].end())
                                {
                                    qs[1 - act][it->second].cnt += pre_cnt;
                                }
                                else
                                {
                                    qs[1 - act][qTail[1 - act]].st = state;
                                    qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                    cnts[1 - act][state] = qTail[1 - act];
                                    qTail[1 - act]++;
                                }
                            }

                            if (m > now_y && 0 == cells[now_x + 1][now_y] && 0 == cells[now_x][now_y + 1])
                            {
                                state = setState3(state, 2 * (now_y - 1), 36);
                                unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                if (it != cnts[1 - act].end())
                                {
                                    qs[1 - act][it->second].cnt += pre_cnt;
                                }
                                else
                                {
                                    qs[1 - act][qTail[1 - act]].st = state;
                                    qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                    cnts[1 - act][state] = qTail[1 - act];
                                    qTail[1 - act]++;
                                }
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
                            unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                            if (it != cnts[1 - act].end())
                            {
                                qs[1 - act][it->second].cnt += pre_cnt;
                            }
                            else
                            {
                                qs[1 - act][qTail[1 - act]].st = state;
                                qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                cnts[1 - act][state] = qTail[1 - act];
                                qTail[1 - act]++;
                            }
                        }

                        if (n > now_x && m > now_y && 0 == cells[now_x + 1][now_y + 1])
                        {
                            state = setState3(state, 2 * (now_y - 1), st * 4);
                            unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                            if (it != cnts[1 - act].end())
                            {
                                qs[1 - act][it->second].cnt += pre_cnt;
                            }
                            else
                            {
                                qs[1 - act][qTail[1 - act]].st = state;
                                qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                cnts[1 - act][state] = qTail[1 - act];
                                qTail[1 - act]++;
                            }
                        }
                    }
                    else
                    {
                        if (n > now_x && 1 < now_y && 0 == cells[now_x + 1][now_y - 1])
                        {
                            state = setState3(state, 2 * (now_y - 1), st);
                            unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                            if (it != cnts[1 - act].end())
                            {
                                qs[1 - act][it->second].cnt += pre_cnt;
                            }
                            else
                            {
                                qs[1 - act][qTail[1 - act]].st = state;
                                qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                cnts[1 - act][state] = qTail[1 - act];
                                qTail[1 - act]++;
                            }
                        }

                        if (n > now_x && 0 == cells[now_x + 1][now_y])
                        {
                            state = setState3(state, 2 * (now_y - 1), st * 4);
                            unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                            if (it != cnts[1 - act].end())
                            {
                                qs[1 - act][it->second].cnt += pre_cnt;
                            }
                            else
                            {
                                qs[1 - act][qTail[1 - act]].st = state;
                                qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                cnts[1 - act][state] = qTail[1 - act];
                                qTail[1 - act]++;
                            }
                        }
                    }

                    if (m > now_y && 0 == cells[now_x][now_y + 1])
                    {
                        state = setState3(state, 2 * (now_y - 1), st * 16);
                        unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                        if (it != cnts[1 - act].end())
                        {
                            qs[1 - act][it->second].cnt += pre_cnt;
                        }
                        else
                        {
                            qs[1 - act][qTail[1 - act]].st = state;
                            qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                            cnts[1 - act][state] = qTail[1 - act];
                            qTail[1 - act]++;
                        }
                    }
                }
                else if (2 == cnt)
                {
                    if (2 == st)
                    {
                        // 1, 1
                        state = setState3(state, 2 * (now_y - 1), 0);

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
                                    unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                    if (it != cnts[1 - act].end())
                                    {
                                        qs[1 - act][it->second].cnt += pre_cnt;
                                    }
                                    else
                                    {
                                        qs[1 - act][qTail[1 - act]].st = state;
                                        qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                        cnts[1 - act][state] = qTail[1 - act];
                                        qTail[1 - act]++;
                                    }
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
                                    unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                                    if (it != cnts[1 - act].end())
                                    {
                                        qs[1 - act][it->second].cnt += pre_cnt;
                                    }
                                    else
                                    {
                                        qs[1 - act][qTail[1 - act]].st = state;
                                        qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                                        cnts[1 - act][state] = qTail[1 - act];
                                        qTail[1 - act]++;
                                    }
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
                        unordered_map<long long, int>::iterator it = cnts[1 - act].find(state);
                        if (it != cnts[1 - act].end())
                        {
                            qs[1 - act][it->second].cnt += pre_cnt;
                        }
                        else
                        {
                            qs[1 - act][qTail[1 - act]].st = state;
                            qs[1 - act][qTail[1 - act]].cnt = pre_cnt;
                            cnts[1 - act][state] = qTail[1 - act];
                            qTail[1 - act]++;
                        }

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

    return 0;
}
