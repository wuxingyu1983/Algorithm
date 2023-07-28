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

#define DEBUG 0
#define MAX_N 21
#define MAX_M 7
#define MAX_K 15
#define BITS 3
#define MASK 7
#define BLOCK 7
#define CANNON 5

#define getState(ST, POS) ((ST) >> (POS * BITS)) & MASK

#define setState(ST, POS, VAL)         \
    ST &= ~(((MASK)) << (POS * BITS)); \
    ST |= ((VAL)) << (POS * BITS);

#define insertState(IDX, K, ST, CNT)                        \
    {                                                       \
        if (m == now_y)                                     \
        {                                                   \
            ST &= mask;                                     \
        }                                                   \
        map<int, int>::iterator it = cnts[IDX][K].find(ST); \
        if (it == cnts[IDX][K].end() || CNT > it->second)   \
        {                                                   \
            cnts[IDX][K][ST] = CNT;                         \
        }                                                   \
    }

#define procUpST()                               \
    {                                            \
        if (1 == upSt || 2 == upSt || 3 == upSt) \
        {                                        \
            setState(st, upPos, 0);              \
        }                                        \
    }

#define getCannons()             \
    {                            \
        if (CANNON == leftSt)    \
            cannons++;           \
        if (CANNON == leftUpSt)  \
            cannons++;           \
        if (CANNON == upSt)      \
            cannons++;           \
        if (CANNON == rightUpSt) \
            cannons++;           \
    }

#define getPaths()         \
    {                      \
        if (4 > leftSt)    \
            paths++;       \
        if (4 > leftUpSt)  \
            paths++;       \
        if (4 > upSt)      \
            paths++;       \
        if (4 > rightUpSt) \
            paths++;       \
    }

#define frontWardProc(ST, START, VAL)       \
    {                                       \
        int pos = START;                    \
        int s = 1;                          \
        while (pos <= m + 1)                \
        {                                   \
            int oneSt = getState(ST, pos);  \
            if (1 == oneSt)                 \
            {                               \
                s++;                        \
            }                               \
            else if (2 == oneSt)            \
            {                               \
                s--;                        \
                if (0 == s)                 \
                {                           \
                    setState(ST, pos, VAL); \
                    break;                  \
                }                           \
            }                               \
            pos++;                          \
        }                                   \
    }

#define backWardProc(ST, START, VAL)        \
    {                                       \
        int pos = START;                    \
        int s = 1;                          \
        while (pos >= 0)                    \
        {                                   \
            int oneSt = getState(ST, pos);  \
            if (2 == oneSt)                 \
            {                               \
                s++;                        \
            }                               \
            else if (1 == oneSt)            \
            {                               \
                s--;                        \
                if (0 == s)                 \
                {                           \
                    setState(ST, pos, VAL); \
                    break;                  \
                }                           \
            }                               \
            pos--;                          \
        }                                   \
    }

#define blockCannonProc(ST, VAL)          \
    {                                     \
        if (n > now_x)                    \
        {                                 \
            setState(ST, leftPos, VAL);   \
        }                                 \
        else                              \
        {                                 \
            setState(ST, leftPos, 0);     \
        }                                 \
        if (m > now_y)                    \
        {                                 \
            setState(ST, leftUpPos, VAL); \
        }                                 \
        else                              \
        {                                 \
            setState(ST, leftUpPos, 0);   \
        }                                 \
    }

int n, m, k, mask;
char cells[MAX_N][MAX_M];
map<int, int> cnts[2][MAX_K]; // key - state, value - state 的最大打击数
int act = 0;                  // 当前生效的 map

int main()
{
    int ret = 0;

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

    for (int i = 1; i <= m; i++)
    {
        mask <<= BITS;
        mask |= MASK;
    }

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
                ret = cnts[act][k][0];
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

                    blockCannonProc(st, BLOCK);
                    procUpST();

                    insertState(nAct, iK, st, cnt);
                }
                else if ('S' == cells[now_x][now_y] || 'T' == cells[now_x][now_y])
                {
                    // 起点、终点
                    if (0 == leftSt || 0 == upSt)
                    {
                        // 左边、上边有一条路径
                        // 这种情况非法
                    }
                    else if (leftSt < 4 && upSt < 4)
                    {
                        // 左边、上边 都有插头
                        // 这种情况非法
                    }
                    else if (leftSt > 4 && upSt > 4)
                    {
                        // 左边、上边 为 障碍物 或 炮台
                        // 合法
                        // 路径在此开始
                        if (n > now_x && '#' != cells[now_x + 1][now_y])
                        {
                            // 向下
                            int st = state;
                            setState(st, leftPos, 3);
                            setState(st, leftUpPos, 0);

                            procUpST();

                            // 周边炮台的个数
                            int cannons = 0;
                            getCannons();

                            insertState(nAct, iK, st, (cnt + cannons));
                        }

                        if (m > now_y && '#' != cells[now_x][now_y + 1])
                        {
                            // 向右
                            int st = state;
                            setState(st, leftPos, 0);
                            setState(st, leftUpPos, 3);

                            procUpST();

                            // 周边炮台的个数
                            int cannons = 0;
                            getCannons();

                            insertState(nAct, iK, st, (cnt + cannons));
                        }
                    }
                    else
                    {
                        // 一边 是 插头，一边 是 障碍物 或 炮台
                        // 路径在此 cell 封住
                        if (3 == leftSt || 3 == upSt)
                        {
                            int st = state;
                            setState(st, leftPos, 0);
                            setState(st, leftUpPos, 0);

                            procUpST();

                            // 周边炮台的个数
                            int cannons = 0;
                            getCannons();

                            insertState(nAct, iK, st, (cnt + cannons));
                        }
                        else if (1 == leftSt || 1 == upSt)
                        {
                            // 从现在到最后，找到匹配的插头（2），改为 3
                            int st = state;
                            setState(st, leftPos, 0);
                            setState(st, leftUpPos, 0);

                            procUpST();

                            frontWardProc(st, rightUpPos, 3);

                            // 周边炮台的个数
                            int cannons = 0;
                            getCannons();

                            insertState(nAct, iK, st, (cnt + cannons));
                        }
                        else
                        {
                            // 2 == leftSt || 2 == upSt
                            // 从现在到最开始，找到匹配的插头（1），改为 3
                            int st = state;
                            setState(st, leftPos, 0);
                            setState(st, leftUpPos, 0);

                            procUpST();

                            backWardProc(st, leftPos - 1, 3);

                            // 周边炮台的个数
                            int cannons = 0;
                            getCannons();

                            insertState(nAct, iK, st, (cnt + cannons));
                        }
                    }
                }
                else
                {
                    // 正常的 cell，非 障碍物、起点、终点
                    if (0 == leftSt || 0 == upSt)
                    {
                        // 只能是 障碍物 或 炮台
                        {
                            // 障碍物
                            int st = state;

                            blockCannonProc(st, BLOCK);
                            procUpST();

                            insertState(nAct, iK, st, cnt);
                        }

                        if (iK < k)
                        {
                            // 炮台
                            int st = state;

                            blockCannonProc(st, CANNON);
                            procUpST();

                            int paths = 0;

                            getPaths();

                            insertState(nAct, (iK + 1), st, (cnt + paths));
                        }
                    }
                    else if (4 < leftSt && 4 < upSt)
                    {
                        // 路径拐角
                        {
                            if (n > now_x && m > now_y && '#' != cells[now_x + 1][now_y] && '#' != cells[now_x][now_y + 1])
                            {
                                int st = state;
                                setState(st, leftPos, 1);
                                setState(st, leftUpPos, 2);

                                procUpST();

                                // 周边炮台的个数
                                int cannons = 0;
                                getCannons();

                                insertState(nAct, iK, st, (cnt + cannons));
                            }
                        }

                        // 障碍物 或 炮台
                        {
                            // 障碍物
                            int st = state;

                            blockCannonProc(st, BLOCK);
                            procUpST();

                            insertState(nAct, iK, st, cnt);

                            if (iK < k)
                            {
                                // 炮台
                                st = state;

                                blockCannonProc(st, CANNON);
                                procUpST();

                                int paths = 0;

                                getPaths();

                                insertState(nAct, (iK + 1), st, (cnt + paths));
                            }
                        }
                    }
                    else if (4 > leftSt && 4 > upSt)
                    {
                        // left 和 up 中两个都是插头
                        int st = state;
                        setState(st, leftPos, 0);
                        setState(st, leftUpPos, 0);

                        procUpST();

                        if ((3 == leftSt && 3 == upSt) || (2 == leftSt && 1 == upSt) || (1 == leftSt && 2 == upSt))
                        {
                            // do nothing
                        }
                        else if ((3 == leftSt && 1 == upSt) || (1 == leftSt && 3 == upSt))
                        {
                            frontWardProc(st, rightUpPos, 3);
                        }
                        else if ((3 == leftSt && 2 == upSt) || (2 == leftSt && 3 == upSt))
                        {
                            backWardProc(st, leftPos - 1, 3);
                        }
                        else if (2 == leftSt && 2 == upSt)
                        {
                            backWardProc(st, leftPos - 1, 2);
                        }
                        else
                        {
                            // 1 == leftSt && 1 == upSt
                            frontWardProc(st, rightUpPos, 1);
                        }

                        // 周边炮台的个数
                        int cannons = 0;
                        getCannons();

                        insertState(nAct, iK, st, (cnt + cannons));
                    }
                    else
                    {
                        // left 和 up 中只有一个插头
                        int oneSt = leftSt;
                        if (4 > upSt)
                        {
                            oneSt = upSt;
                        }

                        if (n > now_x && '#' != cells[now_x][now_y])
                        {
                            // 向下
                            int st = state;
                            setState(st, leftPos, oneSt);
                            setState(st, leftUpPos, 0);

                            procUpST();

                            // 周边炮台的个数
                            int cannons = 0;
                            getCannons();

                            insertState(nAct, iK, st, (cnt + cannons));
                        }

                        if (m > now_y && '#' != cells[now_x][now_y + 1])
                        {
                            // 向右
                            int st = state;
                            setState(st, leftPos, 0);
                            setState(st, leftUpPos, oneSt);

                            procUpST();

                            // 周边炮台的个数
                            int cannons = 0;
                            getCannons();

                            insertState(nAct, iK, st, (cnt + cannons));
                        }
                    }
                }
            }

            cnts[act][iK].clear();
        }

        // 准备下一轮
        act = nAct;
    }

    cout << ret << endl;

    return 0;
}
