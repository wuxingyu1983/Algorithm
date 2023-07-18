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
#define Q_SIZE 2320000 // line queue size

class StAndCnt
{
public:
    long long st;
    int cnt;

    StAndCnt()
    {
        st = cnt = 0;
    }
};

StAndCnt qs[3][Q_SIZE];
int qTail[3];
int n, m, mod;
unordered_map<long long, int> cnts[3]; // key - state, value - state 在 qs 中的位置 index
int act = 0;                     // 当前生效的 map

#define getState(ST, POS) ((ST) >> (POS)) & MASK

#define setState(ST, POS, VAL)             \
    ST &= ~(((long long)(MASK)) << (POS)); \
    ST |= ((long long)(VAL)) << (POS);

#define insertState(IDX, ST, CNT)                                        \
    {                                                                    \
        unordered_map<long long, int>::iterator it = cnts[IDX].find(ST); \
        if (it != cnts[IDX].end())                                       \
        {                                                                \
            qs[IDX][it->second].cnt += CNT;                              \
            qs[IDX][it->second].cnt %= mod;                              \
        }                                                                \
        else                                                             \
        {                                                                \
            qs[IDX][qTail[IDX]].st = ST;                                 \
            qs[IDX][qTail[IDX]].cnt = CNT;                               \
            cnts[IDX][state] = qTail[IDX];                               \
            qTail[IDX]++;                                                \
        }                                                                \
    }

int getAns()
{
    int ret = 0;

    for (size_t iQs = 0; iQs < qTail[act]; iQs++)
    {
        long long state = qs[act][iQs].st;
        long long pre_cnt = qs[act][iQs].cnt;

        int cnt = 0;
        for (size_t i = 0; i < m; i++)
        {
            int st = getState(state, i);
            if (st)
            {
                cnt++;
            }
        }

        pre_cnt *= (n * m - cnt) >> 1;
        pre_cnt %= mod;

        ret += pre_cnt;
        ret %= mod;
    }

    return ret;
}

class BearDestroys
{
public:
    int sumUp(int W, int H, int MOD)
    {
        n = H;
        m = W;
        mod = MOD;

        if (W > H)
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
        qs[act][0].cnt = 1;
        qTail[act]++;

        int now_x = 0;
        int now_y = m;

        while (qTail[act])
        {
            int nIdx = (act + 1) % 3;
            int nnIdx = (act + 2) % 3;
            if (m == now_y)
            {
                now_x++;
                now_y = 1;

                if (n < now_x)
                {
                    ret = getAns();
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
                        setState(state, now_y - 1, 1);

                        // x 2
                        pre_cnt *= 2;
                        pre_cnt %= mod;

                        insertState(nIdx, state, pre_cnt);
                    }
                    else
                    {
                        int k = getState(state, now_y + 1);
                        if (k)
                        {
                            // 只能 "|"
                            setState(state, now_y - 1, 1);

                            // x 2
                            pre_cnt *= 2;
                            pre_cnt %= mod;

                            insertState(nIdx, state, pre_cnt);
                        }
                        else
                        {
                            if (n == now_x)
                            {
                                // 只能 "--"
                                // x 4
                                pre_cnt *= 4;
                                pre_cnt %= mod;

                                insertState(nnIdx, state, pre_cnt);
                            }
                            else
                            {
                                // 处理 "|"
                                setState(state, now_y - 1, 1);
                                setState(state, now_y, 0);

                                // x 1
                                insertState(nIdx, state, pre_cnt);

                                // 处理 "--"
                                setState(state, now_y - 1, 0);

                                // x 2
                                pre_cnt *= 2;
                                pre_cnt %= mod;

                                insertState(nnIdx, state, pre_cnt);
                            }
                        }
                    }
                }
                else
                {
                    // x 2
                    pre_cnt *= 2;
                    pre_cnt %= mod;

                    if (i)
                    {
                        setState(state, now_y - 1, 0);
                    }
                    else
                    {
                        setState(state, now_y, 0);
                    }

                    insertState(nIdx, state, pre_cnt);
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
