// https://www.luogu.com.cn/problem/P5911

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
#include <cstring>

using namespace std;

#define MAX_W   401
#define MAX_N   16

unsigned int time4Person[MAX_N];
unsigned int weight4Person[MAX_N];

unsigned int time4Group[65536];
unsigned int weight4Group[65536];
unsigned int dp[65536];

unsigned int w, n;

int main()
{
    cin >> w >> n;

    for (size_t i = 0; i < n; i++)
    {
        cin >> time4Person[i] >> weight4Person[i];
    }

    unsigned int maxGroup = (1 << n) - 1;

    for (size_t group = 1; group <= maxGroup; group++)
    {
        for (size_t i = 0, person = 1; person <= group; i++, person <<= 1)
        {
            if (group & person)
            {
                weight4Group[group] += weight4Person[i];
                if (time4Group[group] < time4Person[i])
                {
                    time4Group[group] = time4Person[i];
                }
            }
        }

        if (w >= weight4Group[group])
        {
            dp[group] = time4Group[group];
        }
    }

    for (size_t group = 1; group <= maxGroup; group++)
    {
        if (0 == dp[group])
        {
            for (size_t subGroup = 1; subGroup <= group; subGroup++)
            {
                if (subGroup == (subGroup & group))
                {
                    if (0 == dp[group] || dp[group] > (dp[subGroup] + dp[group - subGroup]))
                    {
                        dp[group] = dp[subGroup] + dp[group - subGroup];
                    }
                }
            }
        }
    }

    cout << dp[maxGroup] << endl;

    return 0;
}
