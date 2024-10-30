// https://www.codechef.com/problems/COVERING

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

using namespace std;

#define MAX_N 20
#define MAX_2N 1048576
#define MOD 1000000007

long long pow2[MAX_N + 1];
long long d[MAX_2N];
long long f[MAX_2N];
long long g[MAX_2N];
long long h[MAX_2N];
long long sum[MAX_N + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int maxSt = (1 << n) - 1;

    for (size_t i = 0; i <= maxSt; i++)
    {
        cin >> f[i];
    }
    
    for (size_t i = 0; i <= maxSt; i++)
    {
        cin >> g[i];
    }

    for (size_t i = 0; i <= maxSt; i++)
    {
        cin >> h[i];
    }

    return 0;
}
