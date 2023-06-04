// https://loj.ac/p/10188
// 斜率优化 https://www.cnblogs.com/Xing-Ling/p/11210179.html, https://www.cnblogs.com/Parsnip/p/10323508.html

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
#define MAX_N   50005

long long n, l;

long long dp[MAX_N];
long long toys[MAX_N];
long long sum[MAX_N];
long long q[MAX_N];         // queue

inline long long a(int i)
{
    return sum[i] + i;
}

inline long long b(int i)
{
    return a(i) + l + 1;
}

inline long long x(int i)
{
    return b(i);
}

inline long long y(int i)
{
    return dp[i] + b(i) * b(i);
}

inline double slope(int i, int j)
{
    return (((y(j) - y(i)) * 1.0) / ((x(j) - x(i)) * 1.0));
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif
    
#if DEBUG
    fscanf(fp, "%lld %lld", &n, &l);
#else
    scanf("%lld %lld", &n, &l);
#endif

    for (size_t i = 1; i <= n; i++)
    {
        long long c;
#if DEBUG
        fscanf(fp, "%lld", &c);
#else
        scanf("%lld", &c);
#endif

        toys[i] = c;
        sum[i] = sum[i - 1] + c;
    }

    int head = 0, tail = 0;

    // 1
    dp[1] = (toys[1] - l) * (toys[1] - l);
    q[++tail] = 1;

    for (size_t i = 2; i <= n; i++)
    {
        while (head < tail && slope(q[head], q[head + 1]) <= 2 * a(i))
        {
            head ++;
        }

        dp[i] = dp[q[head]] + b(q[head]) * b(q[head]) - 2 * a(i) * b(q[head]) + a(i) * a(i);

        while (head < tail && slope(q[tail], q[tail - 1]) > slope(i, q[tail - 1]))
        {
            tail --;
        }

        q[++tail] = i;
    }

    cout << dp[n] << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
