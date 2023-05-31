// https://www.luogu.com.cn/problem/P4767
// 四边形不等式优化 https://oi-wiki.org/dp/opt/quadrangle/

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
#define MAX_P   302
#define MAX_V   3002

int w[MAX_V][MAX_V];
int dp[MAX_V][MAX_P];
int ltr[MAX_V][MAX_V], rtl[MAX_V][MAX_V];
int opt[MAX_V][MAX_P];

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    unsigned int v, p;
#if DEBUG
    fscanf(fp, "%u %u", &v, &p);
#else
    scanf("%u %u", &v, &p);
#endif

    vector<unsigned int> villages(v + 1);

    villages[0] = 0;
    for (size_t i = 1; i <= v; i++)
    {
        unsigned int pos;
#if DEBUG
        fscanf(fp, "%u", &pos);
#else
        scanf("%u", &pos);
#endif

        villages[i] = pos;
    }

    sort(villages.begin(), villages.end());

    // pre proc w[][]
    for (size_t step = 1; step < v; step++)
    {
        for (size_t i = 1; i + step <= v; i++)
        {
            int j = i + step;
            if (1 == step)
            {
                w[i][j] = ltr[i][j] = rtl[i][j] = villages[j] - villages[i];
            }
            else
            {
                ltr[i][j] = ltr[i + 1][j] + villages[j] - villages[i];
                rtl[i][j] = rtl[i][j - 1] + villages[j] - villages[i];
            }
        }
    }

    for (size_t step = 2; step < v; step++)
    {
        for (size_t i = 1; i + step <= v; i++)
        {
            int j = i + step;
            int mid = (i + j) / 2;

            w[i][j] = ltr[i][mid] + rtl[mid][j];
        }
    }

    for (size_t i = 2; i <= v; i++)
    {
        dp[i][1] = w[1][i];
    }

    for (size_t j = 2; j <= p; j++)
    {
        // dp[i][j]
        for (size_t i = j; i <= v; i++)
        {
            int tmp = 0;
            int l = j - 1;
            int r = i - 1;
            if (opt[i][j - 1])
            {
                l = opt[i][j - 1];
            }
            if (opt[i + 1][j])
            {
                r = opt[i + 1][j];
            }
            for (size_t k = l; k <= r; k++)
            {
                tmp = dp[k][j - 1] + w[k + 1][i];
                if (0 == dp[i][j] || dp[i][j] > tmp)
                {
                    dp[i][j] = tmp;
                    opt[i][j] = k;
                }
            }
        }
    }
        
    cout << dp[v][p] << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
