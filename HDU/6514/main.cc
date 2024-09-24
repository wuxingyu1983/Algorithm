// https://acm.hdu.edu.cn/showproblem.php?pid=6514

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
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

#define MAX_MN  10000001

char land[MAX_MN];
int dp[MAX_MN];

int main()
{
    int n, m;   // n = rows, m = cols
    cin >> n >> m;

    int p;
    cin >> p;
    
    for (size_t i = 0; i < p; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        x1 --;
        y1 --;
        x2 --;
        y2 --;

        for (size_t row = x1; row <= x2; row++)
        {
            memset(&(land[row * m + y1]), 1, (y2 - y1 + 1));
        }
    }
    

    return 0;
}
