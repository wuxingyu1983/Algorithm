// https://loj.ac/p/10173

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
#define MAX_N   101                 // row
#define MAX_M   11                  // colum
#define MAX_2M  1025

int dp[MAX_N][MAX_2M][MAX_2M];
unsigned char oneCnt[MAX_2M];       // 某个数二进制表示 1 的个数
unsigned char disable[MAX_2M];      // 0 - 合法的，1 - 非法的
unsigned int position[MAX_N];       // 每一行阵地的情况，bit 1 为 高地
unsigned int m2m;
vector<int> enables;
vector<int> enVecs[MAX_2M];

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    int n, m;
#if DEBUG
    fscanf(fp, "%d %d", &n, &m);
#else
    scanf("%d %d", &n, &m);
#endif

    for (size_t row = 0; row < n; row++)
    {
        for (size_t col = 0; col < m; col++)
        {
            char c;
#if DEBUG
            fscanf(fp, "%c", &c);
#else
            scanf("%c", &c);
#endif

            if ('H' == c)
            {
                position[row] |= 1 << col;
            }
        }
    }

    // init
    m2m = (1 << m) - 1;
    int flag = 1;

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j <= m2m; j++)
        {
            if (j & flag)
            {
                oneCnt[j] ++;
            }
        }

        flag <<= 1;
    }

    int flag3 = 3;
    int flag5 = 5;

    for (size_t i = 0; i <= m2m; i++)
    {
        flag3 = 3;
        flag5 = 5;

        for (size_t j = 0; j < m; j++)
        {
            if ((i & flag3) == flag3)
            {
                disable[i] = 1;
                break;
            }

            if ((i & flag5) == flag5)
            {
                disable[i] = 1;
                break;
            }

            flag3 <<= 1;
            flag5 <<= 1;
        }

        if (0 == disable[i])
        {
            enables.push_back(i);
        }
    }
    
    for (vector<int>::iterator it = enables.begin(); it != enables.end(); it++)
    {
        for (vector<int>::iterator jt = enables.begin(); jt != enables.end(); jt++)
        {
            if (0 == (*it & *jt))
            {
                enVecs[*it].push_back(*jt);
            }
        }
    }

    int ans = 0;
    int row = 0;

    // row = 0;
    for (vector<int>::iterator it = enables.begin(); it != enables.end(); it++)
    {
        if (0 == (*it & position[row]))
        {
            dp[row][*it][0] = oneCnt[*it];
            if (dp[row][*it][0] > ans)
            {
                ans = dp[row][*it][0];
            }
        }
    }
    
    if (1 < n)
    {
        for (vector<int>::iterator it = enables.begin(); it != enables.end(); it++)
        {
            for (vector<int>::iterator jt = enables.begin(); jt != enables.end(); jt++)
            {
                if (0 == (*it & position[row]) && 0 == (*jt & position[row + 1]) && 0 == (*it & *jt))
                {
                    dp[row][*it][*jt] = oneCnt[*it] + oneCnt[*jt];
                    if (dp[row][*it][*jt] > ans)
                    {
                        ans = dp[row][*it][*jt];
                    }
                }
            }
        }
    }

    if (2 < n)
    {
        for (row = 1; row < n - 1; row++)
        {
            for (vector<int>::iterator it = enables.begin(); it != enables.end(); it++)
            {
                if (0 == (*it & position[row]))
                {
                    for (vector<int>::iterator jt = enVecs[*it].begin(); jt != enVecs[*it].end(); jt++)
                    {
                        if (0 == (*jt & position[row + 1]))
                        {
                            for (vector<int>::iterator kt = enVecs[*it].begin(); kt != enVecs[*it].end(); kt++)
                            {
                                if (0 == (*jt & *kt) && (0 < dp[row - 1][*kt][*it] || (0 == *kt && 0 == *it)))
                                {
                                    int tmp = dp[row - 1][*kt][*it] + oneCnt[*jt];
                                    if (tmp > dp[row][*it][*jt])
                                    {
                                        dp[row][*it][*jt] = tmp;
                                    }
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
            
        }
    }

    cout << ans << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
