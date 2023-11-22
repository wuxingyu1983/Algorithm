// https://www.luogu.com.cn/problem/P3290

#include <cmath>
#include <cstdio>
#include <vector>
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

#define DEBUG 0
#define MAX_H   101
#define MAX_W   13
#define MAX_C   7
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 60000
#define MOD 1000000007

unsigned int all = 1;
unsigned int dp[MAX_H][MAX_W][4096][MAX_C][MAX_C];

inline void getNext(char * p, int * next, int len)
{
	next[0] = -1;
	int i = 0, j = -1;

	while (i < len)
	{
		if (j == -1 || p[i] == p[j])
		{
			++i;
			++j;
			next[i] = j;
		}	
		else
			j = next[j];
	}
}

int main()
{
    int h, w, c, q;

    cin >> h >> w >> c >> q;

    for (size_t i = 1; i <= h; i++)
    {
        for (size_t j = 1; j <= w; j++)
        {
            all *= 3;
            all %= MOD;
        }
    }
    
    for (size_t iQ = 0; iQ < q; iQ++)
    {
        char up[MAX_C], down[MAX_C];

        for (size_t i = 0; i < c; i++)
        {
            cin >> up[i];
        }

        for (size_t i = 0; i < c; i++)
        {
            cin >> down[i];
        }

        memset(dp, 0, sizeof(dp));

        // KMP
        int nxtUp[MAX_C], nxtDown[MAX_C];

        getNext(up, nxtUp, c);
        getNext(down, nxtDown, c);


    }

    return 0;
}
