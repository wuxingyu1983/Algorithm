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
    int pos = 0;
    power[pos][0] = 1;
    power[pos][1] = 1;
    power[pos][2] = 1;
    power[pos][3] = 1;
    for (pos = 1; pos < 19; pos++)
    {
        for (int i = 0; i < 4; i++)
        {
            power[pos][i] = (power[pos - 1][i] * 10) % odds[i];
        }
    }

    pos = 0;
    for (int i = 0; i < 4; i++)
    {
        int num = odds[i];
        int mod = 0;
        for (int j = 0; j < 4; j++)
        {
            mod |= (num % odds[j]) << offset[j];
        }
        
        dp[pos][1 << i][mod] = 1;
    }
    
    for (; pos < 18; pos++)
    {
        for (int oldSt = 1; oldSt < 16; oldSt++)
        {
            for (int oldMod = 0; oldMod < 4096; oldMod++)
            {
                if (dp[pos][oldSt][oldMod])
                {
                    
                }
            }
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
