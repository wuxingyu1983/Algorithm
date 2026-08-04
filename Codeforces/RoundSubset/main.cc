// https://codeforces.com/contest/837/problem/D

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
#include <unordered_map>

using namespace std;

const int MAXN = 201;

int cnt2[MAXN], cnt5[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        long long a;
        cin >> a;

        long long tmp = a;
        while (tmp % 2 == 0)
        {
            cnt2[i]++;
            tmp /= 2;
        }
        
        tmp = a;
        while (tmp % 5 == 0)
        {
            cnt5[i]++;
            tmp /= 5;
        }

        
    }

    return 0;
}
