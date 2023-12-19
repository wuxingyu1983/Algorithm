// https://pintia.cn/problem-sets/91827364500/exam/problems/91827369832?type=7&page=28

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

#define DEBUG 0
#define MAX_N 501

#define getVal4St(ST, POS) ((ST) >> (POS)) & 1

#define setVal4St(ST, POS, VAL) \
    ST &= ~(1 << (POS));        \
    if (VAL)                    \
        ST |= (VAL) << (POS);

int l;
int dp[MAX_N][4097];
int roads[MAX_N];
unsigned char pos[17];

void init()
{
    memset(dp, 0xff, sizeof(dp));

    dp[0][0] = 0;
}

int main()
{
    pos[2] = 1;
    pos[4] = 2;
    pos[8] = 3;
    pos[16] = 4;

    int t;
    cin >> t;

    for (size_t iT = 0; iT < t; iT++)
    {
        cin >> l;

        for (size_t i = 1; i <= l; i++)
        {
            cin >> roads[i];
        }

        init();

        for (size_t i = 1; i <= l; i++)
        {
            int idx = pos[roads[i]];

            for (size_t st = 0; st <= 4096; st++)
            {
                if (0 <= dp[i - 1][st])
                {
                    int sum = roads[i] + dp[i - 1][st];

                    if (getVal4St(st, idx))
                    {

                    }
                    else
                    {
                        unsigned int newSt = st;

                        setVal4St(newSt, idx, 1);

                        if (sum > dp[i][newSt])
                        {
                            dp[i][newSt] = sum;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
