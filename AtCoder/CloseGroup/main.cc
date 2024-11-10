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
char dp[MAX_N + 1][MAX_2N];
char rnd[MAX_2N];     // st 第一次出现的 轮次

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
    
    int ans = 0;

    for (vector<int>::iterator it = cmpltGh[0].begin(); it != cmpltGh[0].end(); it++)
    {
        dp[1][*it] = 1;
        rnd[*it] = 1;
    }

    if (0 < dp[1][maxSt])
    {
        ans = 1;
    }
    else
    {
        for (size_t rd = 1; rd < n; rd++)
        {
            for (size_t st = 0; st <= maxSt; st++)
            {
                if (0 < dp[rd][st])
                {
                    // find first 0
                    int pos = 0;
                    for (; pos < n; pos++)
                    {
                        if (0 == (st & (1 << pos)))
                        {
                            break;
                        }
                    }
                    
                    for (vector<int>::iterator it = cmpltGh[pos].begin(); it != cmpltGh[pos].end(); it++)
                    {
                        int newSt = st | (*it);
                        if (newSt == maxSt)
                        {
                            ans = rd + 1;
                            goto finish;
                        }
                        else
                        {
                            if (0 == rnd[newSt])
                            {
                                rnd[newSt] = rd + 1;
                                dp[rd + 1][newSt] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

finish:
    cout << ans << endl;

    return 0;
}
