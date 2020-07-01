#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG   0
#define MAX_M   1005

using namespace std;

int bk[MAX_M];
long long c[MAX_M][MAX_M];      // cost
int p[MAX_M][MAX_M];            // pos

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        bk[0] = 0;
        for (size_t i = 0; i < m; i++)
        {
            cin >> bk[i + 1];
        }
        bk[m + 1] = n;

        for (size_t step = 2; step <= m + 1; step++)
        {
            for (size_t i = 0; i < m; i++)
            {
                int j = i + step;
                if (m + 1 < j)
                {
                    break;
                }

                c[i][j] = 0;
                p[i][j] = 0;

                int start = i + 1;
                if (start < p[i][j - 1])
                {
                    start = p[i][j - 1];
                }
                int end = j - 1;
                if (p[i + 1][j] && p[i + 1][j] < end)
                {
                    end = p[i + 1][j];
                }

                for (size_t k = start; k <= end; k++)
                {
                    long long tmp = bk[j] - bk[i] + c[i][k] + c[k][j];
                    if (0 == c[i][j] || tmp < c[i][j])
                    {
                        c[i][j] = tmp;
                        p[i][j] = k;
                    }
                }
            }
        }

        cout << c[0][m + 1] << endl;
    }

    return 0;
}