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
#define Q_SIZE 12320000 // line queue size

class StAndCnt
{
public:
    long long st;
    int cnt;
    int p;

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
            qs[IDX][qTail[IDX]].p = P;                                   \
            qs[IDX][qTail[IDX]].cnt = CNT;                               \
            cnts[IDX][state] = qTail[IDX];                               \
            qTail[IDX]++;                                                \
        }                                                                \
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
                        long long state = qs[act][iQs].st;
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
                            p *= 2;
                            p %= mod;

                            pre_cnt *= 2;
                            pre_cnt %= mod;

                            insertState4(nIdx, state, p, pre_cnt);
                        }
                        else
                        {
                            setState(state, now_y - 1, 1);

                            // x 4
                            p *= 4;
                            p %= mod;

                            pre_cnt *= 4;
                            pre_cnt += p;
                            pre_cnt %= mod;

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
                                p *= 2;
                                p %= mod;

                                pre_cnt *= 2;
                                pre_cnt %= mod;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                            else
                            {
                                setState(state, now_y - 1, 1);

                                // x 4
                                p *= 4;
                                p %= mod;

                                pre_cnt *= 4;
                                pre_cnt += p;
                                pre_cnt %= mod;

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
                                p *= 4;
                                p %= mod;

                                pre_cnt *= 4;
                                pre_cnt += p;
                                pre_cnt %= mod;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                            else
                            {
                                // 处理 "|"
                                setState(state, now_y - 1, 1);

                                // x 2
                                p *= 2;
                                p %= mod;

                                pre_cnt *= 2;
                                pre_cnt += p;
                                pre_cnt %= mod;

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
        int ret = 0;

        cnts[act][0] = 0;
        qs[act][0].st = 0;
        qs[act][0].p = 1;
        qs[act][0].cnt = 0;
        qTail[act]++;

        int now_x = 1;
        int now_y = 1;

        while (qTail[act])
        {
            int nIdx = (act + 1) % 2;
            int pos = n - now_x + now_y - 1;

            // (now_x, now_y) 将要处理的 cell
            for (size_t iQs = 0; iQs < qTail[act]; iQs++)
            {
                long long state = qs[act][iQs].st;
                long long p = qs[act][iQs].p;
                long long pre_cnt = qs[act][iQs].cnt;

                int i = getState(state, pos);
                int j = getState(state, pos + 1);

                if (0 == i && 0 == j)
                {
                    if (m == now_y)
                    {
                        // 只能 “|”
                        if (n == now_x)
                        {
                            // x 2
                            p *= 2;
                            p %= mod;

                            pre_cnt *= 2;
                            pre_cnt %= mod;

                            insertState4(nIdx, state, p, pre_cnt);
                        }
                        else
                        {
                            setState(state, pos, 1);

                            // x 4
                            p *= 4;
                            p %= mod;

                            pre_cnt *= 4;
                            pre_cnt += p;
                            pre_cnt %= mod;

                            insertState4(nIdx, state, p, pre_cnt);
                        }
                    }
                    else
                    {
                        int k = getState(state, pos + 2);
                        if (k)
                        {
                            // 只能 "|"
                            if (n == now_x)
                            {
                                // x 2
                                p *= 2;
                                p %= mod;

                                pre_cnt *= 2;
                                pre_cnt %= mod;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                            else
                            {
                                setState(state, pos, 1);

                                // x 4
                                p *= 4;
                                p %= mod;

                                pre_cnt *= 4;
                                pre_cnt += p;
                                pre_cnt %= mod;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                        }
                        else
                        {
                            if (n == now_x)
                            {
                                // 只能 "--"
                                setState(state, pos + 1, 1);

                                // x 4
                                p *= 4;
                                p %= mod;

                                pre_cnt *= 4;
                                pre_cnt += p;
                                pre_cnt %= mod;

                                insertState4(nIdx, state, p, pre_cnt);
                            }
                            else
                            {
                                // 处理 "--"
                                setState(state, pos + 1, 1);

                                // x 2
                                p *= 2;
                                p %= mod;

                                pre_cnt *= 2;
                                pre_cnt += p;
                                pre_cnt %= mod;

                                insertState4(nIdx, state, p, pre_cnt);

                                // 处理 "|"
                                setState(state, pos, 1);
                                setState(state, pos + 1, 0);

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
                        setState(state, pos, 0);
                    }
                    else
                    {
                        setState(state, pos + 1, 0);
                    }

                    insertState4(nIdx, state, p, pre_cnt);
                }
            }

            // 处理 now_x, now_y, act
            cnts[act].clear();
            qTail[act] = 0;
            act = nIdx;

            if (n == now_x && m == now_y)
            {
                for (size_t iQs = 0; iQs < qTail[act]; iQs++)
                {
                    long long state = qs[act][iQs].st;
                    long long pre_cnt = qs[act][iQs].cnt;

                    ret += pre_cnt;
                    ret %= mod;
                }
                break;
            }
            else
            {
                if (1 == now_y || n == now_x)
                {
                    int sum = now_x + now_y + 1;
                    if (m >= (sum - 1))
                    {
                        now_x = 1;
                        now_y = sum - now_x;
                    }
                    else
                    {
                        now_y = m;
                        now_x = sum - now_y;
                    }
                }
                else
                {
                    now_x++;
                    now_y--;
                }
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
