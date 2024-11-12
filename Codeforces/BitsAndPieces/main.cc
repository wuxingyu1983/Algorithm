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
#define MAX_2M 2097151
#define MAX_N 1000000

int max1st[MAX_2M + 1];     // 最大的 index
int max2nd[MAX_2M + 1];     // 第二大的 index
int min1st[MAX_2M + 1];     // 最小的 index

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

    // init
    memset(max1st, -1 ,sizeof(max1st));
    memset(max2nd, -1 ,sizeof(max2nd));
    memset(min1st, -1 ,sizeof(min1st));

    for (size_t i = 0; i < n; i++)
    {
        if (0 > min1st[MAX_2M - a[i]])
        {
            min1st[MAX_2M - a[i]] = i;
        }
    }
    
    for (int i = n - 1; i >= 0; i--)
    {
        if (0 > max1st[a[i]])
        {
            max1st[a[i]] = i;
        }
        else if (0 > max2nd[a[i]])
        {
            max2nd[a[i]] = i;
        }
    }
    
    // st 的超集的最大、第二大的index
    for (int i = 0; i < MAX_M; ++i)
    {
        for (int st = 0; st <= MAX_2M; ++st)
        {
            if (0 == (st & (1 << i)))
            {
                int othSt = st ^ (1 << i);

                if (max1st[st] >= max1st[othSt])
                {
                    if (max2nd[st] < max1st[othSt])
                    {
                        max2nd[st] = max1st[othSt];
                    }
                }
                else
                {
                    // max1st[st] < max1st[othSt]
                    if (max1st[st] >= max2nd[othSt])
                    {
                        max2nd[st] = max1st[st];
                    }
                    else
                    {
                        max2nd[st] = max2nd[othSt];
                    }

                    max1st[st] = max1st[othSt];
                }
            }
        }
    }

    // 只要处理 min1st 和 max2nd 这两个数组
    for (size_t st = 0; st <= (MAX_2M / 2); st++)
    {
        swap(max2nd[st], max2nd[MAX_2M - st]);
    }

    // 求 min1st 的超集最小的 index
    for (int i = 0; i < MAX_M; ++i)
    {
        for (int st = 0; st <= MAX_2M; ++st)
        {
            if (0 == (st & (1 << i)))
            {
                int othSt = st ^ (1 << i);

                if (0 <= min1st[st] && 0 <= min1st[othSt])
                {
                    if (min1st[st] > min1st[othSt])
                    {
                        min1st[st] = min1st[othSt];
                    }
                }
                else if (0 <= min1st[othSt])
                {
                    min1st[st] = min1st[othSt];
                }
            }
        }
    }

    // 求 max2nd 的超集最大的 index
    for (int i = 0; i < MAX_M; ++i)
    {
        for (int st = 0; st <= MAX_2M; ++st)
        {
            if (0 == (st & (1 << i)))
            {
                int othSt = st ^ (1 << i);

                if (max2nd[st] < max2nd[othSt])
                {
                    max2nd[st] = max2nd[othSt];
                }
            }
        }
    }

    int ans = -1;

    for (int st = 0; st <= MAX_2M; ++st)
    {
        if (0 <= min1st[st] && 0 <= max2nd[st])
        {
            if (min1st[st] < max2nd[st])
            {
                ans = MAX_2M - st;
                break;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
