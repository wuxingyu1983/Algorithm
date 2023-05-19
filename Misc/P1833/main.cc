// https://www.luogu.com.cn/problem/P1833

#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
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
#define MAX_T   1001

class Flower
{
public:
    int t, c;

    Flower()
    {
        t = c = 0;
    }
};

vector<long long> dp(MAX_T, -1);
unsigned int n, tim;

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    unsigned int sH, sM, eH, eM;
#if DEBUG
    fscanf(fp, "%u:%u %u:%u %u", &sH, &sM, &eH, &eM, &n);
#else
    scanf("%u:%u %u:%u %u", &sH, &sM, &eH, &eM, &n);
#endif

    vector<Flower>  que;
    vector<Flower>  queInf;     // infinite
    for (size_t i = 0; i < n; i++)
    {
        int t, c, p;
#if DEBUG
        fscanf(fp, "%d %d %d", &t, &c, &p);
#else
        scanf("%d %d %d", &t, &c, &p);
#endif

        if (0 == p)
        {
            // infinite
            Flower f;
            f.t = t;
            f.c = c;

            queInf.push_back(f);
        }
        else if (1 < p)
        {
            int ct = 1;
            while (p > ct)
            {
                Flower f;
                p -= ct;
                f.t = ct * t;
                f.c = ct * c;
                ct *= 2;

                que.push_back(f);
            }

            Flower f;
            f.t = p * t;
            f.c = p * c;
            que.push_back(f);
        }
        else
        {
            // 1 == p
            Flower f;
            f.t = t;
            f.c = c;

            que.push_back(f);
        }
    }

    unsigned int eT = 60 * eH + eM;
    unsigned int sT = 60 * sH + sM;
    tim = eT - sT;

    long long ans = 0;

    if (0 < tim)
    {
        dp[0] = 0;

        for (vector<Flower>::iterator it = que.begin(); it != que.end(); it++)
        {
            for (int i = tim; i >= 1; i--)
            {
                if (0 <= i - (*it).t)
                {
                    if (0 <= dp[i - (*it).t])
                    {
                        long long tmp = dp[i - (*it).t] + (*it).c;
                        if (tmp > dp[i])
                        {
                            dp[i] = tmp;

                            if (tmp > ans)
                            {
                                ans = tmp;
                            }
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= tim; i++)
        {
            for (vector<Flower>::iterator it = queInf.begin(); it != queInf.end(); it++)
            {
                if (0 <= i - (*it).t)
                {
                    if (0 <= dp[i - (*it).t])
                    {
                        long long tmp = dp[i - (*it).t] + (*it).c;
                        if (tmp > dp[i])
                        {
                            dp[i] = tmp;

                            if (tmp > ans)
                            {
                                ans = tmp;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%lld\n", ans);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
