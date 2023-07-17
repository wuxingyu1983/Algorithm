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
#define MAX_H 13    // row
#define MAX_W 30    // col
#define BITS 2
#define MASK 3
#define MASK3 63
#define Q_SIZE  2320000     // line queue size

class StAndCnt
{
public:
    int st;
    int cnt;

    StAndCnt()
    {
        st = cnt = 0;
    }
};

StAndCnt qs[2][Q_SIZE];
int qTail[2];
int n, m;
unordered_map<int, int> cnts[2]; // key - state, value - state 在 qs 中的位置 index
int act = 0;                           // 当前生效的 map

#define getState(ST, POS)  ((ST) >> ((POS) * 2)) & MASK

#define setState(ST, POS, VAL)    \
    ST &= ~((MASK) << ((POS)*2)); \
    ST |= ((VAL)) << ((POS)*2);

#define insertState(ST, CNT)                                                 \
    {                                                                        \
        unordered_map<int, int>::iterator it = cnts[1 - act].find(ST); \
        if (it != cnts[1 - act].end())                                       \
        {                                                                    \
            qs[1 - act][it->second].cnt = CNT;                              \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            qs[1 - act][qTail[1 - act]].st = ST;                             \
            qs[1 - act][qTail[1 - act]].cnt = CNT;                           \
            cnts[1 - act][state] = qTail[1 - act];                           \
            qTail[1 - act]++;                                                \
        }                                                                    \
    }

class BearDestroys
{
public:
    int sumUp(int W, int H, int MOD)
    {
        int ret = 0;

        n = H;
        m = W;

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
                        pre_cnt %= MOD;

                        insertState(state, pre_cnt);
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
                            pre_cnt %= MOD;

                            insertState(state, pre_cnt);
                        }
                        else
                        {
                            if (n == now_x)
                            {
                                // 处理 "--"
                                setState(state, now_y, 1);

                                // x 2
                                pre_cnt *= 2;
                                pre_cnt %= MOD;

                                insertState(state, pre_cnt);
                            }
                            else
                            {
                                // 处理 "--"
                                setState(state, now_y, 1);

                                // x 1
                                insertState(state, pre_cnt);

                                // 处理 "|"
                                setState(state, now_y - 1, 0);
                                setState(state, now_y, 1);
                                
                                // x 1
                                insertState(state, pre_cnt);
                            }
                        }
                    }
                }
                else
                {
                    // x 2
                    pre_cnt *= 2;
                    pre_cnt %= MOD;

                    if (i)
                    {
                        setState(state, now_y - 1, 0);
                    }
                    else
                    {
                        setState(state, now_y, 0);
                    }

                    insertState(state, pre_cnt);
                }
            }
        }

        return ret;
    }
};


int main()
{
    return 0;
}
