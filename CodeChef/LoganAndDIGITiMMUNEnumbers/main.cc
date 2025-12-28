// https://www.codechef.com/problems/DIGIMU

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
#include <unordered_map>
#include <bitset>

using namespace std;

int odds[4] = {3, 5, 7, 9};
long long dp[19][16][4096];     // dp[pos][status][mod]  status = 3579, mod = 335557779999
long long power[19][4];         // power[pos][num] num = 3,5,7,9
long long sum[19][4];           // sum[pos][num] num = 3,5,7,9
int offset[4] = {0, 2, 5, 8};
int mask[4] = {3, 28, 224, 3840};

void init()
{
    power[0][0] = 1;
    power[0][1] = 1;
    power[0][2] = 1;
    power[0][3] = 1;
    for (int pos = 1; pos < 19; pos++)
    {
        for (int i = 0; i < 4; i++)
        {
            power[pos][i] = (power[pos - 1][i] * 10) % odds[i];
        }
    }
}

int main()
{
    int q;
    cin >> q;

    init();

    return 0;
}
