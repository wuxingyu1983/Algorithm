// https://vjudge.net/problem/TopCoder-14069

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
#define BITS 1
#define MASK 1
#define Q_SIZE 50000 // line queue size

class StAndCnt
{
public:
    long long st;
    long long cnt;
    long long p;

    StAndCnt()
    {
        st = cnt = 0;
    }
};

StAndCnt qs[2][Q_SIZE];
int qTail[2];
int n, m, mod;
unordered_map<long long, int> cnts[2]; // key - state, value - state 在 qs 中的位置 index
int act = 0;                           // 当前生效的 map

StAndCnt wQs[16][33][Q_SIZE];
unordered_map<long long, int> wCnts[16][33]; // key - state, value - state 在 qs 中的位置 index
int wQTail[16][33];

#define getState(ST, POS) ((ST) >> (POS)) & MASK

#define setState(ST, POS, VAL)             \
    ST &= ~(((long long)(MASK)) << (POS)); \
    ST |= ((long long)(VAL)) << (POS);

#define insertState4(IDX, ST, P, CNT)                                    \
    {                                                                    \
        unordered_map<long long, int>::iterator it = cnts[IDX].find(ST); \
        if (it != cnts[IDX].end())                                       \
        {                                                                \
            qs[IDX][it->second].cnt += CNT;                              \
            qs[IDX][it->second].cnt %= mod;                              \
            qs[IDX][it->second].p += P;                                  \
            qs[IDX][it->second].p %= mod;                                \
        }                                                                \
        else                                                             \
        {                                                                \
            qs[IDX][qTail[IDX]].st = ST;                                 \
            qs[IDX][qTail[IDX]].p = P % mod;                             \
            qs[IDX][qTail[IDX]].cnt = CNT % mod;                         \
            cnts[IDX][ST] = qTail[IDX];                                  \
            qTail[IDX]++;                                                \
        }                                                                \
    }

#define insertState2D(X, Y, ST, P, CNT)                                    \
    {                                                                      \
        unordered_map<long long, int>::iterator it = wCnts[X][Y].find(ST); \
        if (it != wCnts[X][Y].end())                                       \
        {                                                                  \
            wQs[X][Y][it->second].cnt += CNT;                              \
            wQs[X][Y][it->second].cnt %= mod;                              \
            wQs[X][Y][it->second].p += P;                                  \
            wQs[X][Y][it->second].p %= mod;                                \
        }                                                                  \
        else                                                               \
        {                                                                  \
            wQs[X][Y][wQTail[X][Y]].st = ST;                               \
            wQs[X][Y][wQTail[X][Y]].p = P % mod;                           \
            wQs[X][Y][wQTail[X][Y]].cnt = CNT % mod;                       \
            wCnts[X][Y][ST] = wQTail[X][Y];                                \
            wQTail[X][Y]++;                                                \
        }                                                                  \
    }

class BearDestroys
{
public:
    int sumUp(int W, int H, int MOD)
    {
        n = H;
        m = W;
        mod = MOD;

        if (m > n)
        {
            return sumUpW();
        }
        else
        {
            return sumUpH();
        }
    }

private:
    int sumUpH()
    {
        int ret = 0;

        cnts[act][0] = 0;
        qs[act][0].st = 0;
        qs[act][0].p = 1;
        qs[act][0].cnt = 0;
        qTail[act]++;

        int now_x = 0;
        int now_y = m;

        while (qTail[act])
        {
            int nIdx = (act + 1) % 2;
            if (m == now_y)
            {
                now_x++;
                now_y = 1;

                if (n < now_x)
                {
                    for (size_t iQs = 0; iQs < qTail[act]; iQs++)
                    {
                        long long pre_cnt = qs[act][iQs].cnt;

                        ret += pre_cnt;
                        ret %= mod;
                    }

                    break;
                }
            }
            else
            {
                now_y++;
            }

            // (now_x, now_y) 将要处理的 cell
            for (size_t iQs = 0; iQs < qTail[act]; iQs++)
            {
                long long state = qs[act][iQs].st;
                long long p = qs[act][iQs].p;
                long long pre_cnt = qs[act][iQs].cnt;

                if (1 == now_y)
                {
                    state <<= BITS;
                }

                int i = getState(state, now_y - 1);
                int j = getState(state, now_y);

                if (0 == i && 0 == j)
                {
                    if (m == now_y)
                    {
                        // 只能 “|”
                        if (n == now_x)
                        {
                            // x 2
                            p <<= 1;
                            pre_cnt <<= 1;

                            insertState4(nIdx, state, p, pre_cnt);
                        }
                        else
                        {
                            setState(state, now_y - 1, 1);

                            // x 4
                            p <<= 2;
                            pre_cnt <<= 2;
                            pre_cnt += p;

                            insertState4(nIdx, state, p, pre_cnt);
                        }
                    }
                    else
                    {
                        int k = getState(state, now_y + 1);
                        if (k)
                        {
                            // 只能 "|"
                            if (n == now_x)
                            {
                                // x 2
                                p <<= 1;
                                pre_cnt <<= 1;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                            else
                            {
                                setState(state, now_y - 1, 1);

                                // x 4
                                p <<= 2;
                                pre_cnt <<= 2;
                                pre_cnt += p;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                        }
                        else
                        {
                            if (n == now_x)
                            {
                                // 只能 "--"
                                setState(state, now_y, 1);

                                // x 4
                                p <<= 2;
                                pre_cnt <<= 2;
                                pre_cnt += p;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                            else
                            {
                                // 处理 "|"
                                setState(state, now_y - 1, 1);

                                // x 2
                                p <<= 1;
                                pre_cnt <<= 1;
                                pre_cnt += p;

                                insertState4(nIdx, state, p, pre_cnt);

                                // 处理 "--"
                                setState(state, now_y - 1, 0);
                                setState(state, now_y, 1);

                                // x 2
                                insertState4(nIdx, state, p, pre_cnt);
                            }
                        }
                    }
                }
                else
                {
                    // do nothing
                    if (i)
                    {
                        setState(state, now_y - 1, 0);
                    }
                    else
                    {
                        setState(state, now_y, 0);
                    }

                    insertState4(nIdx, state, p, pre_cnt);
                }
            }

            cnts[act].clear();
            qTail[act] = 0;
            act = nIdx;
        }

        return ret;
    }

    int sumUpW()
    {
        long long ret = 0;

        int mask = (1 << n) - 1;

        int now_x = 1;
        int now_y = 2;

        wCnts[now_x][now_y][0] = 0;
        wQs[now_x][now_y][0].st = 0;
        wQs[now_x][now_y][0].p = 1;
        wQs[now_x][now_y][0].cnt = 0;
        wQTail[now_x][now_y]++;

        while (wQTail[now_x][now_y])
        {
            // 确定下一个（x, y）
            int nxt_x, nxt_y;
            if (1 == now_y || n == now_x)
            {
                int sum = now_x + now_y + 1;
                if (m >= (sum - 1))
                {
                    nxt_x = 1;
                    nxt_y = sum - nxt_x;
                }
                else
                {
                    nxt_y = m;
                    nxt_x = sum - nxt_y;
                }
            }
            else
            {
                nxt_x = now_x + 1;
                nxt_y = now_y - 1;
            }

            // 确定下下一个(x, y)
            int nnxt_x, nnxt_y;
            if (1 == nxt_y || n == nxt_x)
            {
                int sum = nxt_x + nxt_y + 1;
                if (m >= (sum - 1))
                {
                    nnxt_x = 1;
                    nnxt_y = sum - nnxt_x;
                }
                else
                {
                    nnxt_y = m;
                    nnxt_x = sum - nnxt_y;
                }
            }
            else
            {
                nnxt_x = nxt_x + 1;
                nnxt_y = nxt_y - 1;
            }

            // (now_x, now_y) 将要处理的 cell
            for (size_t iQs = 0; iQs < wQTail[now_x][now_y]; iQs++)
            {
                long long state = wQs[now_x][now_y][iQs].st;
                long long p = wQs[now_x][now_y][iQs].p;
                long long pre_cnt = wQs[now_x][now_y][iQs].cnt;

                int left = 1, up = 1, right = 1;
                int leftPos = now_x, upPos = now_x - 1, rightPos = now_x - 2;

                if (1 == now_x)
                {
                    state &= mask;
                    state <<= BITS;
                }
                else if (m == now_y)
                {
                    state &= mask;
                    state <<= BITS;
                }

                if (1 < now_y)
                {
                    left = getState(state, leftPos);
                }

                if (1 < now_x)
                {
                    up = getState(state, upPos);
                }

                if (1 < now_x && m > now_y)
                {
                    right = getState(state, rightPos);
                }

                if (0 == up)
                {
                    // 处理 “|”
                    setState(state, upPos, 1);

                    if (right)
                    {
                        if (n == now_x)
                        {
                            if (0 == left)
                            {
                                // left cell 永远不会再被覆盖到了
                                // x 8
                                p <<= 3;
                                pre_cnt <<= 3;
                                pre_cnt += p;
                            }
                            else
                            {
                                // x 4
                                p <<= 2;
                                pre_cnt <<= 2;
                                pre_cnt += p;
                            }

                            if (m == now_y)
                            {
                                ret += pre_cnt;
                                ret %= mod;
                            }
                        }
                        else
                        {
                            // x 4
                            p <<= 2;
                            pre_cnt <<= 2;
                            pre_cnt += p;
                        }
                        insertState2D(nxt_x, nxt_y, state, p, pre_cnt);
                    }
                    else
                    {
                        if (n == now_x)
                        {
                            if (0 == left)
                            {
                                // left cell 永远不会再被覆盖到了
                                // x 4
                                p <<= 2;
                                pre_cnt <<= 2;
                                pre_cnt += p;
                            }
                            else
                            {
                                // x 2
                                p <<= 1;
                                pre_cnt <<= 1;
                                pre_cnt += p;
                            }

                            if (m == now_y)
                            {
                                ret += pre_cnt;
                                ret %= mod;
                            }
                        }
                        else
                        {
                            // x 2
                            p <<= 1;
                            pre_cnt <<= 1;
                            pre_cnt += p;
                        }
                        insertState2D(nxt_x, nxt_y, state, p, pre_cnt);
                    }
                }
                else
                {
                    // 0 != up
                    if (left)
                    {
                        // 左边、上边的 cell 都占用了，该 cell 暂时 do nothing
                        setState(state, upPos, 0);
                        insertState2D(nxt_x, nxt_y, state, p, pre_cnt);

                        if (n == now_x && m == now_y)
                        {
                            ret += pre_cnt * 2;
                            ret %= mod;
                        }
                    }
                    else
                    {
                        if (n == now_x)
                        {
                            // 只能 “--”
                            setState(state, upPos, 1);
                            setState(state, leftPos, 1);

                            // x 4
                            p <<= 2;
                            pre_cnt <<= 2;
                            pre_cnt += p;
                            insertState2D(nxt_x, nxt_y, state, p, pre_cnt);

                            if (m == now_y)
                            {
                                ret += pre_cnt;
                                ret %= mod;
                            }
                        }
                        else
                        {
                            // 处理 “--”
                            setState(state, upPos, 1);
                            setState(state, leftPos, 1);

                            // x 2
                            p <<= 1;
                            pre_cnt <<= 1;
                            pre_cnt += p;
                            insertState2D(nxt_x, nxt_y, state, p, pre_cnt);

                            // left 的 cell 和下面的 cell 组成 “|”
                            setState(state, upPos, 0);
                            setState(state, leftPos, 1);

                            // 默认 x 2
                            if (n - 1 == now_x && 1 <= now_y - 2)
                            {
                                int lleft = getState(state, leftPos + 1);
                                if (0 == lleft)
                                {
                                    // x 4
                                    p <<= 1;
                                    pre_cnt <<= 1;
                                }
                            }

                            insertState2D(nnxt_x, nnxt_y, state, p, pre_cnt);
                        }
                    }
                }
            }

            if (n == now_x && m == now_y)
            {
                break;
            }
            else
            {
                now_x = nxt_x;
                now_y = nxt_y;
            }
        }

        return ret;
    }
};

int main()
{
    BearDestroys solver;

    scanf("%d %d %d", &m, &n, &mod);

    int ans = solver.sumUp(m, n, mod);

    cout << ans << endl;

    return 0;
}
