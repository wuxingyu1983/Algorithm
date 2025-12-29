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
long long sum[19];              // sum[pos]
int offset[4] = {0, 2, 5, 8};
int mask[4] = {3, 28, 224, 3840};

bool valid(int st, int mod)
{
    bool ret = true;

    for (int i = 0; i < 4; i++)
    {
        if (st & (1 << i))
        {
            int mod = (mod & mask[i]) >> offset[i];
            if (0 == mod)
            {
                ret = false;
                break;
            }
        }
    }

    return ret;
}

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
                    for (int i = 0; i < 4; i++)
                    {
                        int num = odds[i];
                        int newSt = oldSt | (1 << i);
                        int newMod = 0;

                        for (int j = 0; j < 4; j++)
                        {
                            int mod = (num * power[pos + 1][j] + ((oldMod & mask[j]) >> offset[j])) % odds[j];
                            newMod |= mod << offset[j];
                        }

                        dp[pos + 1][newSt][newMod] += dp[pos][oldSt][oldMod];

                        if (valid(newSt, newMod))
                        {
                            sum[pos + 1] += dp[pos][oldSt][oldMod];
                        }
                    }
                }
            }
        }

        sum[pos + 1] += sum[pos];
    }
}

long long getCount(long long num)
{
    long long ret = 0;

    string strN = to_string(num);
    int len = strN.length();
    int preSt = 0, preMod = 0;
    
    for (int pos = 0; pos < len; pos++)
    {
        int d = strN.at(pos) - '0';
        int up = d - 1;

        if (0 == pos && 1 < len)
        {
            ret += sum[len - 2];
        }

        if (len - 1 == pos)
        {
            up = d;
        }

        if (3 > up)
        {
            break;
        }

        for (int n = 3; n <= up; n+=2)
        {

        }
        
        if (1 != d && d & 1)
        {
            // 3,5,7,9
            preSt |= 1 << d;

            int newMod = 0;
            for (int j = 0; j < 4; j++)
            {
                int mod = (d * power[len - 1 - pos][j] + ((preMod & mask[j]) >> offset[j])) % odds[j];
                newMod |= mod << offset[j];
            }

            preMod = newMod;
        }
    }

    return ret;
}

long long getKNum(long long k)
{
    long long ret = 0;

    return ret;
}

int main()
{
    int q;
    cin >> q;

    init();

    for (int i = 0; i < q; i++)
    {
        long long a, b, k;
        cin >> a >> b >> k;

        long long cntB = getCount(b);
        long long cntA = getCount(a - 1);
        int cnt = cntB - cntA;
        if (cnt < k)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << getKNum(k + cntA) << endl;
        }
    }

    return 0;
}
