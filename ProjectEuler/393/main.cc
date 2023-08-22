// https://projecteuler.net/problem=393

#include <cmath>
#include <cstdio>
#include <vector>
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
#define N       10
#define BITS    1
#define MASK    1

class Record
{
public:
    unsigned short state1;      // 轮廓线段状态
    unsigned short state2;      // 轮廓cells状态

    Record() {}
};

#define getState(ST, POS) ((ST) >> ((POS)*BITS)) & MASK

#define setState(ST, POS, VAL)       \
    ST &= ~((MASK) << ((POS)*BITS)); \
    ST |= (VAL) << ((POS)*BITS);

unsigned int dp[2][1 << (N + 1)][1 << N];       // dp[act][st1][st2]
Record qs[2][1 << (2 * N + 1)];
int qTail[2];
int act = 0;          // 当前生效的 map
int n = N, m = N;

int main()
{
    int now_x = 0;
    int now_y = m;

    act = 0;
    qTail[act] = 1;
    dp[act][0][0] = 1;

    while (0 < qTail[act])
    {
        int nAct = 1 - act;
        if (m == now_y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                cout << dp[act][0][(1 << m) - 1] << endl;
                break;
            }
        }
        else
        {
            now_y++;
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned short st1 = qs[act][iQ].state1;
            unsigned short st2 = qs[act][iQ].state2;

            if (1 == now_y)
            {
                st1 <<= 1;
            }

            int left = 0, up = 0;
            int leftCell = 1, upCell = 1;
            if (1 < now_y)
            {
                left = getState(st1, (now_y - 1));
                leftCell = getState(st2, (now_y - 2));
            }
            if (1 < now_x)
            {
                up = getState(st1, now_y);
                upCell = getState(st2, (now_y - 1));
            }

            
        }
    }

    return 0;
}
