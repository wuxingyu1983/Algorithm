// https://codeforces.com/problemset/problem/1208/F

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

#define MAX_M 21
#define MAX_2M 2097152
#define MAX_N 1000000

int max1st[MAX_2M];     // 最大的 index
int max2nd[MAX_2M];     // 第二大的 index
int min1st[MAX_2M];     // 最小的 index

int a[MAX_N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
    }

        

    return 0;
}
