// https://codeforces.com/contest/95/problem/E

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
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

const int MAXN = 1e5 + 1;
vector<bool> is_lucky(MAXN, true);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
    }
    
    // init
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        while (x > 0)
        {
            int digit = x % 10;
            if (digit != 4 && digit != 7)
            {
                is_lucky[i] = false;
                break;
            }
            x /= 10;
        }
    }

    

    return 0;
}
