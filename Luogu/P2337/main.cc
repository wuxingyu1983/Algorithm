// https://www.luogu.com.cn/problem/P2337
// https://www.luogu.com.cn/blog/65681/solution-p2337#

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
#define MAX_N   21
#define MAX_M   7 
#define MAX_K   15
#define BITS    3
#define MASK    7
#define BLOCK   7

#define getState(ST, POS) ((ST) >> (POS * BITS)) & MASK

#define setState(ST, POS, VAL)         \
    ST &= ~(((MASK)) << (POS * BITS)); \
    ST |= ((VAL)) << (POS * BITS);

#define insertState(IDX, K, ST, CNT)                        \
    {                                                       \
        map<int, int>::iterator it = cnts[IDX][K].find(ST); \
        if (it == cnts[IDX][K].end() || CNT > it->second)   \
        {                                                   \
            cnts[IDX][K][ST] = CNT;                         \
        }                                                   \
    }

int n, m, k;
char cells[MAX_N][MAX_M];
map<int, int> cnts[2][MAX_K];           // key - state, value - state 的最大打击数
int act = 0;                           // 当前生效的 map

int main()
{
    cin >> n >> m >> k;

    if (n >= m)
    {
        for (size_t i = 1; i <= n; i++)
        {
            for (size_t j = 1; j <= m; j++)
            {
                cin >> cells[i][j];
            }
        }
    }
    else
    {
        // n < m
        for (size_t i = 1; i <= n; i++)
        {
            for (size_t j = 1; j <= m; j++)
            {
                cin >> cells[j][i];
            }
        }

        swap(n, m);
    }

    // init
    cnts[act][0][0] = 0;
    int now_x = 0;
    int now_y = m;

    while (true)
    {
        int nAct = 1 - act;
        if (m == now_y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                // finished 
                break;
            }
        }
        else
        {
            now_y++;
        }

        // 处理主体
        for (size_t iK = 0; iK <= k; iK++)
        {
            for (map<int, int>::iterator it = cnts[act][iK].begin(); it != cnts[act][iK].end(); it++)
            {
                int state = it->first;
                int cnt = it->second;

                if (1 == now_y)
                {
                    state <<= 2 * BITS;
                }

                int leftPos = now_y - 1;
                int leftUpPos = now_y;
                int upPos = now_y + 1;
                int rightUpPos = now_y + 2;

                int leftSt = BLOCK, leftUpSt = BLOCK, upSt = BLOCK, rightUpSt = BLOCK;

                if (1 < now_y)
                {
                    leftSt = getState(state, leftPos);
                }
                
                if (1 < now_y && 1 < now_x)
                {
                    leftUpSt = getState(state, leftUpPos);
                }

                if (1 < now_x)
                {
                    upSt = getState(state, upPos);
                }

                if (1 < now_x && m > now_y)
                {
                    rightUpSt = getState(state, rightUpPos);
                }

                if ('#' == cells[now_x][now_y])
                {
                    // 障碍物
                    int st = state;
                    setState(st, leftPos, BLOCK);
                    setState(st, leftUpPos, BLOCK);

                    insertState(nAct, iK, st, cnt);
                }
                else if ('S' == cells[now_x][now_y])
                {
                    // 起点
                }
                else if ('T' == cells[now_x][now_y])
                {
                    // 终点
                }
                else
                {

                }
            }

            cnts[act][iK].clear();
        }

        // 准备下一轮
        act = nAct;
    }

    return 0;
}
