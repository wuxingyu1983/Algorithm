#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define DEBUG 0
#define MOD 1000000007

using namespace std;

int primes[19] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int masks[71];
long long freq[71];
long long cnt[2][524288];
long long fc[71][2][2];

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif
    
    // init masks array
    for (size_t i = 2; i <= 70; i++)
    {
        for (size_t j = 0; j < 19; j++)
        {
            if (0 == i / primes[j])
            {
                break;
            }
            else
            {
                if (0 == i % primes[j])
                {
                    masks[i] = (1 << j) ^ masks[i / primes[j]];
                    break;
                }
            }
        }
    }
    
    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif
    
    for (size_t i = 0; i < n; i++)
    {
        int a;
#if DEBUG
        inFile >> a;
#else
        cin >> a;
#endif
        
        freq[a] ++;
    }
    
    int index = 0;
    
    cnt[index][0] = 1;
    for (size_t i = 1; i <= 70; i++)
    {
        if (freq[i])
        {            
            int ifc = 0;
            fc[i][0][0] = 1;
            for (int f = 1; f <= freq[i]; f++)
            {
                fc[i][1 - ifc][0] = fc[i][ifc][1] + fc[i][ifc][0];
                fc[i][1 - ifc][1] = fc[i][ifc][0] + fc[i][ifc][1];
                fc[i][1 - ifc][0] %= MOD;
                fc[i][1 - ifc][1] %= MOD;

                ifc = 1 - ifc;
            }

            long long even = fc[i][ifc][0];
            long long odd = fc[i][ifc][1];
            
            for (size_t j = 0; j < 524288; j++)
            {
                cnt[1 - index][j] = cnt[index][j] * even;
                cnt[1 - index][j] %= MOD;
            }
            
            for (size_t j = 0; j < 524288; j++)
            {
                cnt[1 - index][j ^ masks[i]] += ((cnt[index][j] * odd) % MOD);
                cnt[1 - index][j ^ masks[i]] %= MOD;
            }
            
            index = 1 - index;
        }
    }
    
    int ret = (MOD + cnt[index][0] - 1) % MOD;
    
    cout << ret << endl;
    
#if DEBUG
    inFile.close();
#endif
    
    return 0;
}
