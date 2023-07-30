// https://www.luogu.com.cn/problem/P2337
// https://www.luogu.com.cn/blog/65681/solution-p2337#

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
#define MAX_N 21
#define MAX_M 7
#define MAX_K 16
#define BITS 2
#define MASK 3
#define BLOCK 3
#define CANNON 1
#define PATH 0
#define QS_SIZE 400000

#define getState(ST, POS) ((ST) >> ((POS) * BITS)) & MASK

#define setState(ST, POS, VAL)         \
    ST &= ~(((MASK)) << ((POS) * BITS)); \
    ST |= ((VAL)) << ((POS) * BITS);

#define insertState(IDX, K, ST1, ST2, SUM)                                                                     \
    {                                                                                                          \
        unordered_map<short, unordered_map<short, int> >::iterator it1 = cnts[IDX][K].find(ST1);                \
        if (it1 == cnts[IDX][K].end())                                                                         \
        {                                                                                                      \
            cnts[IDX][K].insert(pair<short, unordered_map<short, int> >(ST1, unordered_map<short, int>())); \
        }                                                                                                      \
        unordered_map<short, int>::iterator it2 = cnts[IDX][K][ST1].find(ST2);                                 \
        if (it2 == cnts[IDX][K][ST1].end())                                                                    \
        {                                                                                                      \
            int idx = qTail[IDX];                                                                              \
            qs[IDX][idx].state1 = ST1;                                                                         \
            qs[IDX][idx].state2 = ST2;                                                                         \
            qs[IDX][idx].cnCnt = K;                                                                            \
            qs[IDX][idx].sum = SUM;                                                                            \
            qTail[IDX]++;                                                                                      \
            cnts[IDX][K][ST1][ST2] = idx;                                                                       \
        }                                                                                                      \
        else                                                                                                   \
        {                                                                                                      \
            int idx = it2->second;                                                                             \
            if (qs[IDX][idx].sum < SUM)                                                                        \
            {                                                                                                  \
                qs[IDX][idx].sum = SUM;                                                                        \
            }                                                                                                  \
        }                                                                                                      \
    }

#define getCannons()               \
    {                              \
        if (CANNON == leftCell)    \
            cannons++;             \
        if (CANNON == leftUpCell)  \
            cannons++;             \
        if (CANNON == upCell)      \
            cannons++;             \
        if (CANNON == rightUpCell) \
            cannons++;             \
    }

#define getPaths()            \
    {                         \
        if (0 == leftCell)    \
            paths++;          \
        if (0 == leftUpCell)  \
            paths++;          \
        if (0 == upCell)      \
            paths++;          \
        if (0 == rightUpCell) \
            paths++;          \
    }

#define frontWardProc(ST, START, VAL)       \
    {                                       \
        int pos = START;                    \
        int s = 1;                          \
        while (pos <= m)                    \
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

class Record
{
public:
    short state1;   // 轮廓线状态，0 - 无插头，1 - 左插头，2 - 右插头，3 - 独立插头
    short state2;   // 周边cells的状态，0 - 路径，1 - 炮台，3 - 障碍物 或 边界外部
    unsigned char cnCnt;    // 炮台数量
    unsigned char sum;

    Record()
    {
        state1 = state2 = cnCnt = sum = 0;
    }
};

Record qs[2][QS_SIZE];
int qTail[2];

int n, m, k, mask;
char cells[MAX_N][MAX_M];
unordered_map< short, unordered_map<short, int> > cnts[2][MAX_K]; // 第一级 key 是轮廓线状态，第二级 key 是 cells 的状态，value 是在 qs 的下标
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
    for (int i = 1; i <= m; i++)
    {
        mask <<= BITS;
        mask |= MASK;
    }

    qs[act][qTail[act]].state1 = 0;
    qs[act][qTail[act]].state2 = 0;
    qs[act][qTail[act]].cnCnt = 0;
    qs[act][qTail[act]].sum = 0;

    cnts[act][0][0][mask] = qTail[act];
    qTail[act] ++;
    int now_x = 0;
    int now_y = m;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;
        if (m == now_y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                // finished
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    if (0 == qs[act][iQ].state1)
                    {
                        if (ret < qs[act][iQ].sum)
                        {
                            ret = qs[act][iQ].sum;
                        }
                    }
                }
                break;
            }
        }
        else
        {
            now_y++;
        }

        // 处理主体
        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            short state1 = qs[act][iQ].state1;
            short state2 = qs[act][iQ].state2;
            unsigned char iK = qs[act][iQ].cnCnt;
            unsigned char sum = qs[act][iQ].sum;

            if (1 == now_y)
            {
                state1 <<= BITS;

                state2 &= mask;
                state2 <<= BITS;
            }

            int leftSt = getState(state1, now_y - 1);
            int upSt = getState(state1, now_y);
            
            int leftCell = BLOCK, leftUpCell = BLOCK, upCell = BLOCK, rightUpCell = BLOCK;

            if (1 < now_y)
            {
                leftCell = getState(state2, now_y - 2);
            }

            if (1 < now_y && 1 < now_x)
            {
                leftUpCell = getState(state2, now_y - 1);
            }

            if (1 < now_x)
            {
                upCell = getState(state2, now_y);
            }

            if (1 < now_x && m > now_y)
            {
                rightUpCell = getState(state2, now_y + 1);
            }

            if ('#' == cells[now_x][now_y])
            {
                // 障碍物
                if (0 < leftSt || 0 < upSt)
                {
                    // 非法
                    continue;
                }

                short st1 = state1;

                setState(st1, now_y - 1, 0);
                setState(st1, now_y, 0);

                short st2 = state2;
                setState(st2, now_y - 1, BLOCK);

                insertState(nAct, iK, st1, st2, sum);
            }
            else if ('S' == cells[now_x][now_y] || 'T' == cells[now_x][now_y])
            {
                // 起点、终点
                if ((0 == leftSt && 0 == leftCell) || (0 == upSt && 0 == upCell))
                {
                    // 左边、上边有一条路径
                    // 这种情况非法
                    continue;
                }
                else if (0 < leftSt && 0 < upSt)
                {
                    // 左边、上边 都有插头
                    // 这种情况非法
                    continue;
                }
                else if (0 < leftCell && 0 < upCell)
                {
                    // 左边、上边 为 障碍物 或 炮台
                    // 合法
                    // 路径在此开始
                    short st2 = state2;
                    setState(st2, now_y - 1, PATH);

                    // 周边炮台的个数
                    int cannons = 0;
                    getCannons();

                    if (n > now_x && '#' != cells[now_x + 1][now_y])
                    {
                        // 向下
                        short st1 = state1;
                        setState(st1, now_y - 1, 3);
                        setState(st1, now_y, 0);

                        insertState(nAct, iK, st1, st2, (sum + cannons));
                    }

                    if (m > now_y && '#' != cells[now_x][now_y + 1])
                    {
                        // 向右
                        short st1 = state1;
                        setState(st1, now_y - 1, 0);
                        setState(st1, now_y, 3);

                        insertState(nAct, iK, st1, st2, (sum + cannons));
                    }
                }
                else
                {
                    // 一边 是 插头，一边 是 障碍物 或 炮台
                    // 路径在此 cell 封住
                    short st1 = state1;
                    setState(st1, now_y - 1, 0);
                    setState(st1, now_y, 0);

                    short st2 = state2;
                    setState(st2, now_y - 1, PATH);

                    // 周边炮台的个数
                    int cannons = 0;
                    getCannons();

                    if (3 == leftSt || 3 == upSt)
                    {
                    }
                    else if (1 == leftSt || 1 == upSt)
                    {
                        // 从现在到最后，找到匹配的插头（2），改为 3
                        frontWardProc(st1, now_y + 1, 3);
                    }
                    else
                    {
                        // 2 == leftSt || 2 == upSt
                        // 从现在到最开始，找到匹配的插头（1），改为 3
                        backWardProc(st1, now_y - 2, 3);
                    }

                    insertState(nAct, iK, st1, st2, (sum + cannons));
                }
            }
            else
            {
                // 正常的 cell，非 障碍物、起点、终点
                if ((0 == leftSt && 0 == leftCell) || (0 == upSt && 0 == upCell))
                {
                    // 只能是 障碍物 或 炮台
                    {
                        // 障碍物
                        short st1 = state1;

                        setState(st1, now_y - 1, 0);
                        setState(st1, now_y, 0);

                        short st2 = state2;
                        setState(st2, now_y - 1, BLOCK);

                        insertState(nAct, iK, st1, st2, sum);
                    }

                    if (iK < k)
                    {
                        // 炮台
                        short st1 = state1;

                        setState(st1, now_y - 1, 0);
                        setState(st1, now_y, 0);

                        short st2 = state2;
                        setState(st2, now_y - 1, CANNON);

                        int paths = 0;
                        getPaths();

                        insertState(nAct, (iK + 1), st1, st2, (sum + paths));
                    }
                }
                else if (0 == leftSt && 0 == upSt)
                {
                    // 路径拐角
                    if (n > now_x && m > now_y && '#' != cells[now_x + 1][now_y] && '#' != cells[now_x][now_y + 1])
                    {
                        short st1 = state1;

                        setState(st1, now_y - 1, 1);
                        setState(st1, now_y, 2);

                        short st2 = state2;
                        setState(st2, now_y - 1, PATH);

                        // 周边炮台的个数
                        int cannons = 0;
                        getCannons();

                        insertState(nAct, iK, st1, st2, (sum + cannons));
                    }

                    // 障碍物 或 炮台
                    {
                        // 障碍物
                        short st1 = state1;

                        setState(st1, now_y - 1, 0);
                        setState(st1, now_y, 0);

                        short st2 = state2;
                        setState(st2, now_y - 1, BLOCK);

                        insertState(nAct, iK, st1, st2, sum);
                    }

                    if (iK < k)
                    {
                        // 炮台
                        short st1 = state1;

                        setState(st1, now_y - 1, 0);
                        setState(st1, now_y, 0);

                        short st2 = state2;
                        setState(st2, now_y - 1, CANNON);

                        int paths = 0;
                        getPaths();

                        insertState(nAct, (iK + 1), st1, st2, (sum + paths));
                    }
                }
                else if (0 < leftSt && 0 < upSt)
                {
                    // left 和 up 中两个都是插头
                    short st1 = state1;

                    setState(st1, now_y - 1, 0);
                    setState(st1, now_y, 0);

                    short st2 = state2;
                    setState(st2, now_y - 1, PATH);

                    if (1 == leftSt && 2 == upSt)
                    {
                        // 非法
                        continue;
                    }
                    else if ((3 == leftSt && 3 == upSt) || (2 == leftSt && 1 == upSt))
                    {
                        // do nothing
                    }
                    else if ((3 == leftSt && 1 == upSt) || (1 == leftSt && 3 == upSt))
                    {
                        frontWardProc(st1, now_y + 1, 3);
                    }
                    else if ((3 == leftSt && 2 == upSt) || (2 == leftSt && 3 == upSt))
                    {
                        backWardProc(st1, now_y - 2, 3);
                    }
                    else if (2 == leftSt && 2 == upSt)
                    {
                        backWardProc(st1, now_y - 2, 2);
                    }
                    else
                    {
                        // 1 == leftSt && 1 == upSt
                        frontWardProc(st1, now_y + 1, 1);
                    }

                    // 周边炮台的个数
                    int cannons = 0;
                    getCannons();

                    insertState(nAct, iK, st1, st2, (sum + cannons));
                }
                else
                {
                    // left 和 up 中只有一个插头
                    int oneSt = leftSt + upSt;

                    short st2 = state2;
                    setState(st2, now_y - 1, PATH);

                    // 周边炮台的个数
                    int cannons = 0;
                    getCannons();

                    if (n > now_x && '#' != cells[now_x + 1][now_y])
                    {
                        // 向下
                        short st1 = state1;

                        setState(st1, now_y - 1, oneSt);
                        setState(st1, now_y, 0);

                        insertState(nAct, iK, st1, st2, (sum + cannons));
                    }

                    if (m > now_y && '#' != cells[now_x][now_y + 1])
                    {
                        // 向右
                        short st1 = state1;

                        setState(st1, now_y - 1, 0);
                        setState(st1, now_y, oneSt);

                        insertState(nAct, iK, st1, st2, (sum + cannons));
                    }
                }
            }
        }

        // 准备下一轮
        qTail[act] = 0;
        for (size_t iK = 0; iK <= k; iK ++)
        {
            cnts[act][iK].clear();
        }
        
        act = nAct;
    }

    cout << ret << endl;

    return 0;
}
