// https://loj.ac/p/10147 类似的 https://vijos.org/p/1312

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
#define MAX_N   202

long long dpMin[2 * MAX_N][2 * MAX_N];
long long dpMax[2 * MAX_N][2 * MAX_N];
long long dp[2 * MAX_N][2 * MAX_N];

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    unsigned int n;
#if DEBUG
    fscanf(fp, "%u", &n);
#else
    scanf("%u", &n);
#endif

    vector<long long> pile(n);
    for (size_t i = 0; i < n; i++)
    {
        long long cnt;
#if DEBUG
        fscanf(fp, "%lld", &cnt);
#else
        scanf("%lld", &cnt);
#endif

        pile[i] = cnt;
        dp[i][i] = cnt;
    }

    for (size_t i = n; i < 2 * n - 1; i++)
    {
        dp[i][i] = pile[i - n];
    }

    for (size_t stp = 1; stp < n; stp++)
    {
        for (size_t i = 0; i <= 2 * n - 2 - stp; i++)
        {
            int j = i + stp;

            dp[i][j] = dp[i][i] + dp[i + 1][j];
            
            long long tmpMin, tmpMax;
            tmpMin = dpMin[i][j];
            tmpMax = dpMax[i][j];

            for (size_t k = i; k < j; k++)
            {
                long long tmp = dp[i][j] + dpMin[i][k] + dpMin[k + 1][j];
                if (0 == tmpMin || tmpMin > tmp)
                {
                    tmpMin = tmp;
                }

                tmp = dp[i][j] + dpMax[i][k] + dpMax[k + 1][j];
                if (tmpMax < tmp)
                {
                    tmpMax = tmp;
                }
            }

            dpMin[i][j] = tmpMin;
            dpMax[i][j] = tmpMax;
        }
    }

    long long ansMin = 0, ansMax = 0;

    for (size_t i = 0; i < n; i++)
    {
        int j = i + n - 1;
        if (0 == ansMin || ansMin > dpMin[i][j])
        {
            ansMin = dpMin[i][j];
        }
        
        if (ansMax < dpMax[i][j])
        {
            ansMax = dpMax[i][j];
        }
    }
    

    cout << ansMin << endl;
    cout << ansMax << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
