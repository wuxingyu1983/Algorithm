// https://codeforces.com/problemset/gymProblem/100917/I

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <map>

using namespace std;

const int MAX_N = 1048576;

long long nxt[MAX_N];
char wins[MAX_N];   // 0 - loss, 1 - win
string strHash;

int main()
{
    // init
    {
        for (size_t i = 0; i < MAX_N; i++)
        {
            int cnt = __builtin_popcount(i);
            if (1 & cnt)
            {
                // odd
                wins[i] = 1;
            }
        }

        strHash.reserve(2 * MAX_N + 2);
        memset(nxt, -1, sizeof(nxt));

        long long x = 0;
        for (size_t i = 0; i < MAX_N; i++)
        {
            x = x * 487237 + 1011807;
            x %= MAX_N;

            if (1 & x)
            {
                // odd
                strHash += '1';
            }
            else
            {
                strHash += '0';
            }
        }
    }

    return 0;
}
