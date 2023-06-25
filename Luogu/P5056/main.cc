// https://www.luogu.com.cn/problem/P5056

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

#define DEBUG       0
#define MAX_MN      12

unsigned char cells[MAX_MN + 1][MAX_MN + 1];        // 1 - obstacle

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

    for (size_t row = 1; row <= n; row++)
    {
        for (size_t col = 1; col <= m; col++)
        {
            char c;
#if DEBUG
            fscanf(fp, "%c", &c);
#else
            scanf("%c", &c);
#endif
            if ('*' == c)
            {
                cells[row][col] = 1;
            }
        }
    }

     

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
