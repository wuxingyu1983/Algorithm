// https://atcoder.jp/contests/arc136/tasks/arc136_d

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
#include <functional>

using namespace std;

#define MAX_A   1000010

int threshold[] = {10, 100, 1000, 10000, 100000, 1000000};

vector<int> d;
vector<int> b;

// segment tree functions
void update(int l, int r, int c, int s, int t, int p)
{
    if (l <= s && t <= r)
    {
        d[p] += (t - s + 1) * c, b[p] += c;
        return;
    }
    int m = s + ((t - s) >> 1);
    if (b[p] && s != t)
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    if (l <= m)
        update(l, r, c, s, m, p * 2);
    if (r > m)
        update(l, r, c, m + 1, t, p * 2 + 1);
    d[p] = d[p * 2] + d[p * 2 + 1];
}

int getsum(int l, int r, int s, int t, int p)
{
    if (l <= s && t <= r)
        return d[p];
    int m = s + ((t - s) >> 1);
    if (b[p])
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    int sum = 0;
    if (l <= m)
        sum = getsum(l, r, s, m, p * 2);
    if (r > m)
        sum += getsum(l, r, m + 1, t, p * 2 + 1);
    return sum;
}

int main()
{
    int n;
    cin >> n;

    vector<int> a;
    for (size_t i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        a.push_back(tmp);
    }

    // init segment tree
    d.clear();
    d.resize(4 * MAX_A + 4, 0);
    b.clear();
    b.resize(4 * MAX_A + 4, 0);

    long long ans = 0;

    for (size_t i = 0; i < n; i++)
    {
        int tmp = a[i];

        // get sum
        for (size_t j = 0; j < 6; j++)
        {
            if (threshold[j] > tmp)
            {
                ans += getsum(threshold[j] - tmp, threshold[j], 0, 1000000, 1);
            }
        }

        // update segment tree
        update(tmp, tmp, 1, 0, 1000000, 1);
    }

    cout << ans << endl; 

    return 0;
}
