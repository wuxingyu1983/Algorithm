// https://atcoder.jp/contests/abc187/tasks/abc187_f

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

#define MAX_N 18
#define MAX_2N 262144

int edges[MAX_N];
vector<int> cmpltGh[MAX_N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        a--;
        b--;

        edges[a] |= 1 << b;
        edges[b] |= 1 << a;
    }
    
    // init
    for (size_t i = 0; i < n; i++)
    {
        edges[i] |= 1 << i;
    }

    int maxSt = (1 << n) - 1;

    // 找到所有的完全图
    for (size_t st = 1; st <= maxSt; st++)
    {
        int tmp = maxSt;

        for (size_t pos = 0; pos < n; pos++)
        {
            if (st & (1 << pos))
            {
                tmp &= edges[pos];
            }
        }

        if (st == tmp)
        {
            // 完全图
            for (size_t pos = 0; pos < n; pos++)
            {
                if (st & (1 << pos))
                {
                    cmpltGh[pos].push_back(st);
                }
            }
        }
    }
    

    return 0;
}
