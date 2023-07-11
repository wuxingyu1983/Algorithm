/**    Author:*        Indestinee*    Date:*        2014.11.22*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define cls(a) memset(a, 0, sizeof(a))
#define rise(i, a, b) for (int i = a; i <= b; i++)
#define fall(i, a, b) for (int i = a; i >= b; i--)
int n, m, a[11][9], now, q, w, e, q2, w2, e2, newk, r, r2, cnt;
ll dp[2][1 << 17];
int main()
{
    while (scanf("%d %d", &n, &m) != EOF)
    {
        cls(a);
        now = 0;
        cls(dp[now]);
        rise(i, 1, m)
        {
            getchar();
            a[getchar() - 'A' + 1][getchar() - 'A' + 1] = 1;
        }
        dp[now][0] = 1;
        rise(i, 1, n) rise(j, 1, 8)
        {
            now ^= 1;
            cls(dp[now]);
            if (j == 1)
            {
                if (a[i][j] == 0)
                {
                    for (int k = (1 << 15) - 1; k >= 0; k--)
                    {
                        if (k & (1 << 14))
                            for (int l = 1; l <= 4; l <<= 1)
                                dp[now][k ^ (1 << 14) ^ (l << 14)] += dp[!now][k];
                        else
                        {
                            dp[now][k ^ (3 << 14)] += dp[!now][k];
                            dp[now][k ^ (5 << 14)] += dp[!now][k];
                            dp[now][k ^ (6 << 14)] += dp[!now][k];
                        }
                    }
                }
                else
                    for (int k = (1 << 14) - 1; k >= 0; k--)
                        dp[now][k] = dp[!now][k];
            }
            else if (j & 1)
            {
                q = 17 - (j << 1);
                w = q - 1;
                q2 = 1 << q;
                w2 = 1 << w;
                for (int k = (1 << 15) - 1; k >= 0; k--)
                {
                    newk = ((k >> (1 + q)) << (q + 3)) ^ (k & (w2 - 1));
                    if (a[i][j] == 0)
                    {
                        if ((k & q2) && (k & w2))
                            dp[now][newk] += dp[!now][k];
                        else if ((k & q2) || (k & w2))
                        {
                            for (int l = 1; l <= 8; l <<= 1)
                                dp[now][newk ^ (l << w)] += dp[!now][k];
                        }
                        else
                        {
                            dp[now][newk ^ (3 << w)] += dp[!now][k];
                            dp[now][newk ^ (5 << w)] += dp[!now][k];
                            dp[now][newk ^ (9 << w)] += dp[!now][k];
                            dp[now][newk ^ (6 << w)] += dp[!now][k];
                            dp[now][newk ^ (10 << w)] += dp[!now][k];
                            dp[now][newk ^ (12 << w)] += dp[!now][k];
                        }
                    }
                    else
                    {
                        if (((k & q2) == 0) && ((k & w2) == 0))
                            dp[now][newk] += dp[!now][k];
                    }
                }
            }
            else if (j != 8)
            {
                e = 16 - (j << 1);
                w = e + 1;
                q = w + 1;
                q2 = 1 << q;
                w2 = 1 << w;
                e2 = 1 << e;
                r = e - 1;
                r2 = 1 << r;
                for (int k = (1 << 17) - 1; k >= 0; k--)
                {
                    newk = ((k >> (q + 1)) << (q - 1)) ^ (k & (r2 - 1));
                    cnt = ((k & q2) > 0) + ((k & w2) > 0) + ((k & e2) > 0) + ((k & r2) > 0);
                    if (a[i][j] == 0)
                    {
                        if (cnt == 2)
                            dp[now][newk] += dp[!now][k];
                        else if (cnt == 1)
                        {
                            dp[now][newk ^ r2] += dp[!now][k];
                            dp[now][newk ^ e2] += dp[!now][k];
                        }
                        else if (cnt == 0)
                            dp[now][newk ^ r2 ^ e2] += dp[!now][k];
                    }
                    else
                    {
                        if (cnt == 0)
                            dp[now][newk] += dp[!now][k];
                    }
                }
            }
            else if (j == 8)
            {
                e = 0;
                w = 1;
                q = 2;
                q2 = 4;
                w2 = 2;
                e2 = 1;
                for (int k = (1 << 17) - 1; k >= 0; k--)
                {
                    newk = ((k >> 3) << 1);
                    cnt = ((k & q2) > 0) + ((k & w2) > 0) + ((k & e2) > 0);
                    if (a[i][j] == 0)
                    {
                        if (cnt == 1)
                            dp[now][newk ^ 1] += dp[!now][k];
                        else if (cnt == 2)
                            dp[now][newk] += dp[!now][k];
                    }
                    else
                    {
                        if (cnt == 0)
                            dp[now][newk] += dp[!now][k];
                    }
                }
            }
        }
        cout << dp[now][0] << endl;
    }
}
