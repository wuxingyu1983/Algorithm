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

using namespace std;

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    long long n, x, k;

#if DEBUG
    inFile >> n >> x >> k;
#else
    cin >> n >> x >> k;
#endif

    vector<long long> a(n);

    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> a[i];
#else
        cin >> a[i];
#endif
    }

    sort(a.begin(), a.end());

    long long cnt = 0;
    for (size_t i = 0; i < n; i++)
    {
        long long sn = 0, en = 0;
        if (0 == a[i] % x)
        {
            if (0 == k)
            {
                continue;
            }
            else
            {
                sn = a[i] + (k - 1) * x;
                en = a[i] + k * x;
            }
        }
        else
        {
            sn = (a[i] / x) * x + k * x;
            if (sn < a[i])
            {
                sn = a[i];
            }
            en = (a[i] / x) * x + (k + 1) * x;
        }

        vector<long long>::iterator sit = lower_bound(a.begin(), a.end(), sn);
        vector<long long>::iterator eit = lower_bound(a.begin(), a.end(), en);

        if (sit != a.end())
        {
            if (eit == a.end())
            {
                cnt += n - (sit - a.begin());
            }
            else
            {
                cnt += eit - a.begin() - (sit - a.begin());
            }
        }
    }

    cout << cnt << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
