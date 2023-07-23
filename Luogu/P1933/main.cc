// https://www.luogu.com.cn/problem/P1933

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

#define DEBUG   0
#define MAX_H   51
#define MAX_W   4
#define BITS    8
#define MASK    255
#define MOD     11192869
#define ASC     1       // 增序
#define DESC    2       // 降序

#define getState(ST, POS) ((ST) >> ((POS) * BITS)) & MASK

#define setState(ST, POS, VAL)         \
    ST &= ~(((long long)(MASK)) << ((POS)*BITS)); \
    ST |= ((long long)(VAL)) << ((POS)*BITS);

char hall[MAX_H][MAX_W];
char path[155];

int h, w;

map<long long, int> cnts[2]; // key - state, value - count
int act = 0;                             // 当前生效的 map

vector<int> idxes[8];

#define insertState(IDX, ST, CNT)                                  \
    {                                                              \
        map<long long, int>::iterator itPriv = cnts[IDX].find(ST); \
        if (itPriv != cnts[IDX].end())                             \
        {                                                          \
            cnts[IDX][ST] = (itPriv->second + CNT) % MOD;          \
        }                                                          \
        else                                                       \
        {                                                          \
            cnts[IDX][ST] = CNT;                                   \
        }                                                          \
    }

int main()
{
    int ret = 0;

    cin >> w >> h;
    
    for (size_t j = 1; j <= w; j++)
    {
        for (size_t i = 1; i <= h; i++)
        {
            int t;
            cin >> t;
            
            hall[i][j] = t;
        }
    }
    
    int flag = 0;
    for (size_t i = 1; i <= w * h; i++)
    {
        int l;
        cin >> l;

        path[i] = l;

        flag <<= 1;
        flag &= 7;
        flag |= l;

        if (3 <= i)
        {
            idxes[flag].push_back(i - 1);
        }
    }

    cnts[act][0] = 1;

    int now_x = 0;
    int now_y = w;

    while (!cnts[act].empty())
    {
        int nIdx = (act + 1) % 2;
        if (w == now_y)
        {
            now_x++;
            now_y = 1;

            if (h < now_x)
            {
                for (map<long long, int>::iterator it = cnts[act].begin(); it != cnts[act].end(); it++)
                {
                    ret += it->second;
                    ret %= MOD;
                }
            }
        }
        else
        {
            now_y++;
        }

        // (now_x, now_y) 将要处理的 cell
        // 遍历
        for (map<long long, int>::iterator it = cnts[act].begin(); it != cnts[act].end(); it++)
        {
            // state 的组成 0# 边的值，0# 边的方向（1 - 增序，2 - 降序），1# ....
            long long state = it->first;
            int cnt = it->second;

            if (1 == now_y)
            {
                state <<= BITS * 2;
            }

            int left = getState(state, 2 * (now_y - 1));
            int leftDir = getState(state, 2 * (now_y - 1) + 1);
            int up = getState(state, 2 * now_y);
            int upDir = getState(state, 2 * now_y + 1);

            if (0 == left && 0 == up)
            {
                if (1 == now_x || 1 == now_y || h == now_x || w == now_y)
                {
                    // 起点
                    if (hall[now_x][now_y] == path[1])
                    {
                        // 向下
                        if (h > now_x && path[2] == hall[now_x + 1][now_y])
                        {
                            long long st = state;
                            setState(st, 2 * (now_y - 1), 2);
                            setState(st, 2 * (now_y - 1) + 1, ASC);

                            insertState(nIdx, st, cnt);
                        }

                        // 向右
                        if (w > now_y && path[2] == hall[now_x][now_y + 1])
                        {
                            long long st = state;
                            setState(st, 2 * now_y, 2);
                            setState(st, 2 * now_y + 1, ASC);

                            insertState(nIdx, st, cnt);
                        }
                    }
                }

                // 终点
                if (hall[now_x][now_y] == path[h * w])
                {
                    // 向下
                    if (h > now_x && hall[now_x + 1][now_y] == path[h * w -1])
                    {
                        long long st = state;
                        setState(st, 2 * (now_y - 1), h * w - 1);
                        setState(st, 2 * (now_y - 1) + 1, DESC);

                        insertState(nIdx, st, cnt);
                    }

                    // 向右
                    if (w > now_y && hall[now_x][now_y + 1] == path[h * w - 1])
                    {
                        long long st = state;
                        setState(st, 2 * now_y, h * w - 1);
                        setState(st, 2 * now_y + 1, DESC);

                        insertState(nIdx, st, cnt);
                    }
                }

                if (h > now_x && w > now_y)
                {
                    int idx = hall[now_x + 1][now_y] << 2 | hall[now_x][now_y] << 1 | hall[now_x][now_y + 1];

                    for (vector<int>::iterator it = idxes[idx].begin(); it != idxes[idx].end(); it++)
                    {
                        // 向下 *it - 1, 向右 *it + 1
                        long long st = state;
                        setState(st, 2 * (now_y - 1), *it - 1);
                        setState(st, 2 * (now_y - 1) + 1, DESC);
                        setState(st, 2 * now_y, *it + 1);
                        setState(st, 2 * now_y + 1, ASC);

                        insertState(nIdx, st, cnt);
                    }

                    idx = hall[now_x + 1][now_y] | hall[now_x][now_y] << 1 | hall[now_x][now_y + 1] << 2;

                    for (vector<int>::iterator it = idxes[idx].begin(); it != idxes[idx].end(); it++)
                    {
                        // 向下 *it + 1, 向右 *it - 1
                        long long st = state;
                        setState(st, 2 * (now_y - 1), *it + 1);
                        setState(st, 2 * (now_y - 1) + 1, ASC);
                        setState(st, 2 * now_y, *it - 1);
                        setState(st, 2 * now_y + 1, DESC);

                        insertState(nIdx, st, cnt);
                    }
                }
            }
            else if (left && up)
            {
                if (left == up && leftDir != upDir)
                {
                    long long st = state;
                    setState(st, 2 * (now_y - 1), 0);
                    setState(st, 2 * (now_y - 1) + 1, 0);
                    setState(st, 2 * now_y, 0);
                    setState(st, 2 * now_y + 1, 0);

                    insertState(nIdx, st, cnt);
                }
            }
            else
            {
                int curr = left + up;
                int dir = leftDir + upDir;

                if (h * w == curr)
                {
                    // 终点
                    long long st = state;
                    setState(st, 2 * (now_y - 1), 0);
                    setState(st, 2 * (now_y - 1) + 1, 0);
                    setState(st, 2 * now_y, 0);
                    setState(st, 2 * now_y + 1, 0);

                    insertState(nIdx, st, cnt);
                }
                else if (1 == curr)
                {
                    if (1 == now_x || h == now_x || 1 == now_y || w == now_y)
                    {
                        long long st = state;
                        setState(st, 2 * (now_y - 1), 0);
                        setState(st, 2 * (now_y - 1) + 1, 0);
                        setState(st, 2 * now_y, 0);
                        setState(st, 2 * now_y + 1, 0);

                        insertState(nIdx, st, cnt);
                    }
                }
                else
                {
                    if (ASC == dir)
                    {
                        if (h > now_x && hall[now_x + 1][now_y] == path[curr + 1])
                        {
                            long long st = state;
                            setState(st, 2 * (now_y - 1), curr + 1);
                            setState(st, 2 * (now_y - 1) + 1, dir);
                            setState(st, 2 * now_y, 0);
                            setState(st, 2 * now_y + 1, 0);

                            insertState(nIdx, st, cnt);
                        }

                        if (w > now_y && hall[now_x][now_y + 1] == path[curr + 1])
                        {
                            long long st = state;
                            setState(st, 2 * (now_y - 1), 0);
                            setState(st, 2 * (now_y - 1) + 1, 0);
                            setState(st, 2 * now_y, curr + 1);
                            setState(st, 2 * now_y + 1, dir);

                            insertState(nIdx, st, cnt);
                        }
                    }
                    else
                    {
                        // DESC
                        if (h > now_x && hall[now_x + 1][now_y] == path[curr - 1])
                        {
                            long long st = state;
                            setState(st, 2 * (now_y - 1), curr - 1);
                            setState(st, 2 * (now_y - 1) + 1, dir);
                            setState(st, 2 * now_y, 0);
                            setState(st, 2 * now_y + 1, 0);

                            insertState(nIdx, st, cnt);
                        }

                        if (w > now_y && hall[now_x][now_y + 1] == path[curr - 1])
                        {
                            long long st = state;
                            setState(st, 2 * (now_y - 1), 0);
                            setState(st, 2 * (now_y - 1) + 1, 0);
                            setState(st, 2 * now_y, curr - 1);
                            setState(st, 2 * now_y + 1, dir);

                            insertState(nIdx, st, cnt);
                        }
                    }
                }
            }
        }

        cnts[act].clear();
        act = nIdx;
    }

    cout << ret << endl;

    return 0;
}
