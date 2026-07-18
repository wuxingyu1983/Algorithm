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
#include <iomanip>

using namespace std;

const int MAX_N = 101;
const int MAX_K = 301;
char cells[MAX_N]; // 每行为 3 bits 的状态
int sums[MAX_N];

short dp0[8][8][99];         // dp[st1][st2][interval] : 第i行的状态st1,第j行的状态st2,i行和j行中间还有interval行的最大距离
short dp2[MAX_N][64][MAX_K]; // dp[i][st][k] : 第 i - 1, i 行的状态为st,选了k个点的最大距离
char flags[8][8];
char bits[8];

vector<int> states;

void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        sums[i] = sums[i - 1] + 3 - bits[cells[i]];
    }

    memset(dp2, -1, sizeof(dp2));

    bits[1] = bits[2] = bits[4] = 1;
    bits[3] = bits[5] = bits[6] = 2;
    bits[7] = 3;

    for (int st1 = 0; st1 < 8; st1++)
    {
        for (int st2 = 0; st2 < 8; st2++)
        {
            if (1 == flags[st1][st2])
                continue;

            int max = 0;
            if (7 == st1 || 3 == st1 || 6 == st1 || 7 == st2 || 3 == st2 || 6 == st2)
                max = 1;
            else if (5 == st1 || 5 == st2)
                max = 4;

            if (1 == max)
            {
                for (int inter = 0; inter < 99; inter++)
                {
                    dp0[st1][st2][inter] = 1;
                    dp0[st2][st1][inter] = 1;
                }
            }
            else
            {
                for (int inter = 0; inter < 99; inter++)
                {
                    // 4 == max or 0 == max
                    int tmp = max;
                    for (int p1 = 0; p1 < 3; p1++)
                    {
                        if (st1 & (1 << p1))
                        {
                            for (int p2 = 0; p2 < 3; p2++)
                            {
                                if (st2 & (1 << p2))
                                {
                                    int dist = (p1 - p2) * (p1 - p2) + (inter + 1) * (inter + 1);
                                    if (0 == tmp || dist < tmp)
                                        tmp = dist;
                                }
                            }
                        }
                    }

                    if (0 == inter && 1 != tmp && 0 < st1 + st2)
                    {
                        if (0 < st1)
                        {
                            states.push_back((st2 << 3) | st1);
                        }
                        if (0 < st2)
                        {
                            states.push_back((st1 << 3) | st2);
                        }
                    }

                    dp0[st1][st2][inter] = tmp;
                    dp0[st2][st1][inter] = tmp;
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

            if ('.' == ch)
            {
                usable++;
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
    init(n);

    int ans = 1;

    // row = 1;
    for (int i = 0; i < 4; i++)
    {
        int st = states[i];
        if (cells[1] & st || 1 == dp0[0][st][0])
            continue;

        int num = bits[st];
        if (num > k)
            continue;

        dp2[1][st][num] = dp0[0][st][0];

        if (num == k)
        {
            if (dp2[1][st][num] > ans)
                ans = dp2[1][st][num];
        }
    }

    if (2 <= n)
    {
        // row == 2
        for (int i = 0; i < states.size(); i++)
        {
            int st = states[i];
            int st1 = st >> 3;
            int st2 = st & 7;

            if (0 == st2 || (cells[1] & st1) || (cells[2] & st2) || 1 == dp0[st1][st2][0])
                continue;

            int num = bits[st1] + bits[st2];
            if (num > k)
                continue;

            dp2[2][st][num] = dp0[st1][st2][0];

            if (num == k)
            {
                if (dp2[2][st][num] > ans)
                    ans = dp2[2][st][num];
            }
        }
    }

    if (2 < n)
    {
        for (int row = 3; row <= n; row++)
        {
            for (int i = 0; i < states.size(); i++)
            {
                int st = states[i];
                int st1 = st >> 3;
                int st2 = st & 7;

                if (cells[row - 1] & st1 || cells[row] & st2)
                    continue;

                int num = bits[st1] + bits[st2];
                if (num > k)
                    continue;

                for (int r = row - 2; r >= 1 && r >= row - 4; r--)
                {
                    for (int j = 0; j < states.size(); j++)
                    {
                        int preSt = states[j];
                        int st_1 = preSt >> 3; // row - 3
                        int st_2 = preSt & 7;  // row - 2

                        if (cells[r] & st_2 || cells[r - 1] & st_1)
                            continue;

                        for (int cnt = 0; cnt <= min(sums[r], k - num); cnt++)
                        {
                            if (0 <= dp2[r][preSt][cnt])
                            {
                                int max = dp2[r][preSt][cnt];
                                if (0 < dp0[st1][st2][0])
                                {
                                    if (0 == max || max > dp0[st1][st2][0])
                                        max = dp0[st1][st2][0];
                                }

                                if (0 < dp0[st_2][st2][row - r - 1])
                                {
                                    if (0 == max || max > dp0[st_2][st2][row - r - 1])
                                        max = dp0[st_2][st2][row - r - 1];
                                }

                                if (0 < dp0[st_1][st1][row - r - 1])
                                {
                                    if (0 == max || max > dp0[st_1][st1][row - r - 1])
                                        max = dp0[st_1][st1][row - r - 1];
                                }

                                if (0 < dp0[st_2][st1][row - r - 2])
                                {
                                    if (0 == max || max > dp0[st_2][st1][row - r - 2])
                                        max = dp0[st_2][st1][row - r - 2];
                                }

                                if (max > dp2[row][st][num + cnt])
                                {
                                    dp2[row][st][num + cnt] = max;
                                }

                                if (k == num + cnt && max > ans)
                                    ans = max;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < 3; i++)
            {
                int st = states[i];
                int st1 = st >> 3;
                int st2 = st & 7;

                if (cells[row - 1] & st1 || cells[row] & st2)
                    continue;

                int num = bits[st1] + bits[st2];
                if (num > k)
                    continue;

                for (int r = row - 5; r >= 1; r--)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        int preSt = states[j];
                        int st_1 = preSt >> 3; // row - 3
                        int st_2 = preSt & 7;  // row - 2

                        if (cells[r] & st_2 || cells[r - 1] & st_1)
                            continue;

                        for (int cnt = 0; cnt <= min(sums[r], k - num); cnt++)
                        {
                            if (0 <= dp2[r][preSt][cnt])
                            {
                                int max = dp2[r][preSt][cnt];
                                if (0 < dp0[st1][st2][0])
                                {
                                    if (0 == max || max > dp0[st1][st2][0])
                                        max = dp0[st1][st2][0];
                                }

                                if (0 < dp0[st_2][st2][row - r - 1])
                                {
                                    if (0 == max || max > dp0[st_2][st2][row - r - 1])
                                        max = dp0[st_2][st2][row - r - 1];
                                }

                                if (0 < dp0[st_1][st1][row - r - 1])
                                {
                                    if (0 == max || max > dp0[st_1][st1][row - r - 1])
                                        max = dp0[st_1][st1][row - r - 1];
                                }

                                if (0 < dp0[st_2][st1][row - r - 2])
                                {
                                    if (0 == max || max > dp0[st_2][st1][row - r - 2])
                                        max = dp0[st_2][st1][row - r - 2];
                                }

                                if (max > dp2[row][st][num + cnt])
                                {
                                    dp2[row][st][num + cnt] = max;
                                }

                                if (k == num + cnt && max > ans)
                                    ans = max;
                            }
                        }
                    }
                }
            }
        }
    }

//    cout << fixed << setprecision(6) << sqrt(ans) << "\n";
    cout << fixed << setprecision(6) << ans << "\n";

    return 0;
}
