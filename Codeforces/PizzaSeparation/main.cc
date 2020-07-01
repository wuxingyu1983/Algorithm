#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define DEBUG   0
#define MAX_N   360
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a;
    a.reserve(2 * MAX_N);

    int sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        int tmp = 0;
        cin >> tmp;
        sum += tmp;
        a[i] = sum;
    }

    if (1 == n)
    {
        cout << 360 << endl;
    }
    else
    {
        int ret = 361;
        sum = 0;
        for (size_t i = 0; i < n; i++)
        {
            vector<int>::iterator it = lower_bound(a.begin() + i, a.begin() + n + i, sum + 180);
            if (*it == sum + 180)
            {
                ret = 0;
                break;
            }
            else
            {
                ret = ret > (2 * (*it - sum) - 360) ? (2 * (*it - sum) - 360) : ret;
                a[i + n] = a[n - 1] + a[i];
                sum = a[i];
            }
        }
        cout << ret << endl;
    }

    return 0;
}
