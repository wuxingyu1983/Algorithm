// https://tlx.toki.id/problems/icpc-jakarta-2022/A

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <utility>

using namespace std;

const int MAX_N = 101;
const int MAX_K = 301;
char cells[MAX_N];  // 每行为 3 bits 的状态

short dp0[8][8][99];            // dp[st1][st2][interval] : 第i行的状态st1,第j行的状态st2,i行和j行中间还有interval行的最大距离
short dp1[MAX_N][8][MAX_K];     // dp[i][st][k] : 第 i 行的状态为st,选了k个点的最大距离
short dp2[MAX_N][64][MAX_K];    // dp[i][st][k] : 第 i - 1, i 行的状态为st,选了k个点的最大距离
char flags[8][8];
char bits[8];

void init()
{
    bits[1] = bits[2] = bits[4] = 1;
    bits[3] = bits[5] = bits[6] = 2;
    bits[7] = 3;

    for (int st1 = 0; st1 < 8; st1++)
    {
        int max = 0;
        if (7 == st1 || 3 == st1 || 6 == st1)
            max = 1;
        else if (5 == st1)
            max = 4;

        for (int st2 = 0; st2 < 8; st2++)
        {
            if (1 == flags[st1][st2])
                continue;

            if (7 == st2 || 3 == st2 || 6 == st2)
            {
                if (0 == max || max > 1)
                    max = 1;
            }
            else if (5 == st2)
            {
                if (0 == max)
                    max = 4;
            }

            for (int inter = 0; inter < 99; inter++)
            {
                if (1 == max)
                {
                    dp0[st1][st2][inter] = 1;
                    dp0[st2][st1][inter] = 1;
                }
                else
                {
                    // 4 == max or 0 == max
                    for (int p1 = 0; p1 < 3; p1++)
                    {
                        if (st1 & (1 << p1))
                        {
                            for (int p2 = 0; p2 < 3; p2++)
                            {
                                if (st2 & (1 << p2))
                                {
                                    int dist = (p1 - p2) * (p1 - p2) + (inter + 1) * (inter + 1);
                                    if (0 == max || dist < max)
                                        max = dist;
                                }
                            }
                        }
                    }

                    dp0[st1][st2][inter] = max;
                    dp0[st2][st1][inter] = max;
                }
            }

            flags[st1][st2] = 1;
            flags[st2][st1] = 1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int usable = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char ch;
            cin >> ch;

            if ('.' == cells[j])
            {
                usable ++;
            }
            else
            {
                // unusable cell, mark it in the bitmask
                cells[j] |= 1 << i;
            }
        }

        cin.ignore();
    }
    cells[0] = 7;

    if (usable < k)
    {
        cout << -1 << "\n";
        return 0;
    }

    // init
    init();

    int ans = 0;

    // row = 1;
    for (int st = 1; st < 8; st++)
    {
        if (cells[1] & st)
            continue;

        int num = bits[st];
        if (num > k)
            continue;

        dp1[1][st][num] = dp2[1][st][num] = dp0[0][st][0];

        if (num ==k)
        {
            if (ans == 0 || dp1[1][st][num] < ans)
                ans = dp1[1][st][num];
        }
    }

    return 0;
}
