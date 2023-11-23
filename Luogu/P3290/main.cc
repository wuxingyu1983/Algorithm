// https://www.luogu.com.cn/problem/P3290

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
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
#define MAX_H 102
#define MAX_W 14
#define MAX_C 7
#define ST_BITS 1
#define ST_MASK 1
#define MOD 1000000007

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

int act = 0;
unsigned int all = 1;
//unsigned int dp[MAX_H][MAX_W][4096][MAX_C][MAX_C]; // dp[row][col][state][idxUp][idxDown]
unsigned int dp[2][MAX_W][4096][MAX_C][MAX_C]; // dp[row][col][state][idxUp][idxDown]

inline void getNext(char *p, int *next, int len)
{
    next[0] = -1;
    next[len] = 0;
    int i = 0, j = -1;

    while (i < len)
    {
        if (j == -1 || p[i] == p[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }

    // 处理 next[len]
    for (size_t i = 1; i < len; i++)
    {
        for (size_t j = 0; i < len; j++)
        {
            if (len > j + i)
            {
                if (p[j] != p[j + i])
                {
                    break;
                }
            }
        }

        if (len == j + i)
        {
            next[len] = len - i;
            break;
        }
    }
}

int main()
{
    int h, w, c, q;

    cin >> h >> w >> c >> q;

    for (size_t i = 1; i <= h; i++)
    {
        for (size_t j = 1; j <= w; j++)
        {
            all *= 3;
            all %= MOD;
        }
    }

    for (size_t iQ = 0; iQ < q; iQ++)
    {
        char up[MAX_C], down[MAX_C];

        for (size_t i = 0; i < c; i++)
        {
            cin >> up[i];
        }

        for (size_t i = 0; i < c; i++)
        {
            cin >> down[i];
        }

        memset(dp, 0, sizeof(dp));

        // KMP
        int nxtUp[MAX_C], nxtDown[MAX_C];

        getNext(up, nxtUp, c);
        getNext(down, nxtDown, c);

        unsigned int cnt = 0;
        unsigned int maxSt = 1 << w;

        act = 0;
        dp[act][1][0][0][0] = 1;

        int nxtRow, nxtCol;
        int newIdxUp, newIdxDown;

        for (size_t row = 1; row <= h; row++)
        {
            int nAct = 1 - act;

            for (size_t col = 1; col <= w; col++)
            {
                nxtRow = act;

                if (w == col)
                {
                    nxtRow = nAct;
                    nxtCol = 1;
                }
                else
                {
                    nxtCol = col + 1;
                }

                for (size_t idxUp = 0; idxUp <= c; idxUp++)
                {
                    for (size_t idxDown = 0; idxDown <= c; idxDown++)
                    {
                        for (size_t st = 0; st < maxSt; st++)
                        {
                            if (dp[act][col][st][idxUp][idxDown])
                            {
                                int flag = getVal4St(st, col - 1);
                                int newSt = st;

                                // W-白子，B-黑子，X-无子
                                char colors[] = {'W', 'B', 'X'};

                                // 先处理第一行
                                for (size_t i = 0; i < 3; i++)
                                {
                                    char color = colors[i];

                                    // 先处理第一行
                                    {
                                        int j;
                                        if (c == idxUp)
                                        {
                                            j = nxtUp[c];
                                        }
                                        else
                                        {
                                            j = idxUp;
                                        }

                                        if (color == up[j])
                                        {
                                            newIdxUp = j + 1;
                                        }
                                        else
                                        {
                                            while (0 <= j && color != up[j])
                                            {
                                                j = nxtUp[j];
                                            }

                                            if (0 <= j)
                                            {
                                                newIdxUp = j + 1;
                                            }
                                            else
                                            {
                                                newIdxUp = 0;
                                            }
                                        }

                                        if (c == newIdxUp)
                                        {
                                            setVal4St(newSt, col - 1, 1);
                                        }
                                        else
                                        {
                                            setVal4St(newSt, col - 1, 0);
                                        }
                                    }

                                    // 再处理第二行
                                    {
                                        int j;
                                        if (c == idxDown)
                                        {
                                            j = nxtDown[c];
                                        }
                                        else
                                        {
                                            j = idxDown;
                                        }

                                        if (color == down[j])
                                        {
                                            newIdxDown = j + 1;
                                        }
                                        else
                                        {
                                            while (0 <= j && color != down[j])
                                            {
                                                j = nxtDown[j];
                                            }

                                            if (0 <= j)
                                            {
                                                newIdxDown = j + 1;
                                            }
                                            else
                                            {
                                                newIdxDown = 0;
                                            }
                                        }

                                        if (c == newIdxDown && 1 == flag)
                                        {
                                            // 第一、二行匹配上了，非法
                                        }
                                        else
                                        {
                                            if (1 == nxtCol)
                                            {
                                                newIdxUp = 0;
                                                newIdxDown = 0;
                                            }

                                            dp[nxtRow][nxtCol][newSt][newIdxUp][newIdxDown] += dp[act][col][st][idxUp][idxDown];
                                            dp[nxtRow][nxtCol][newSt][newIdxUp][newIdxDown] %= MOD;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            memset(dp[act], 0, sizeof(dp[act]));
            act = nAct;
        }

        for (size_t st = 0; st < maxSt; st++)
        {
            cnt += dp[act][1][st][0][0];
            cnt %= MOD;
        }

        cout << (MOD + all - cnt) % MOD << endl;
    }

    return 0;
}
