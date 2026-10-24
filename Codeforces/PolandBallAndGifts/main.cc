// https://codeforces.com/contest/755/problem/F

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

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }

    vector<char> flags(n + 1, 0);
    vector<int> rings(n + 1, 0);

    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        flags[i] = 1;
        cnt ++;

        if (flags[p[i]])
        {
            rings[cnt] ++;
            cnt = 0;
        }
    }

    // minimum
    {
        int ans = 0;
        int tmp = k;
        int i = 2;
        while (k > 0)
        {
            while (0 == rings[i])
            {
                i ++;
            }
            
            {
                if (rings[i] * i <= k)
                {
                    ans += rings[i] * i;
                    k -= rings[i] * i;
                }
                else
                {
                    ans += i * (k / i);
                    ans += (k % i) + 1;
                    k = 0;
                }
            }
        }
        
        cout << ans << " ";
    }

    // maximum
    {
        int ans = 0;
        int tmp = k;
        while (k > 0)
        {
        }
        
        cout << ans << "\n";
    }

    return 0;
}
