// https://atcoder.jp/contests/arc091/tasks/arc091_c

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
#include <utility>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b;
    cin >> n >> a >> b;

    if (n < a + b - 1)
    {
        cout << "-1\n";
    }
    else if ((long long)n > (long long)a * (long long)b)
    {
        cout << "-1\n";
    }
    else
    {
        int lds_begin = 1;
        for (int lis = n - a + 1; lis <= n; lis++)
        {
            cout << lis << " ";

            if (lds_begin < n - a + 1)
            {
                int lds_end = lds_begin + b - 2;

                for (int l = min(lds_end, n - a); l >= lds_begin; l--)
                {
                    cout << l << " ";
                }

                lds_begin = min(lds_end, n - a) + 1;
            }
        }

        cout << "\n";
    }

    return 0;
}
