#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;
#define int long long
const int maxm = 1e6;
int d[(1 << 20)][20];
int g[20][20];
int n, m;
int lowbit(int i)
{
    return i & -i;
}
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a][b] = g[b][a] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        d[(1 << i)][i] = 1;
    }
    int ans = 0;
    for (int s = 0; s < (1 << n); s++)
    {
        int t = lowbit(s); // 起点
        for (int i = 0; i < n; i++)
        { // 枚举当前所在点
            if ((1 << i) < t)
                continue;
            for (int j = 0; j < n; j++)
            { // 枚举下一步要走的点
                if ((1 << j) < t || !g[i][j])
                    continue;
                if (s >> j & 1)
                {
                    if ((1 << j) == t) // 走回来了,说明出现环
                        ans += d[s][i];
                }
                else if (!(s >> j & 1))
                {
                    d[s | (1 << j)][j] += d[s][i];
                }
            }
        }
    }
    cout << (ans - m) / 2 << endl;
    return 0;
}
