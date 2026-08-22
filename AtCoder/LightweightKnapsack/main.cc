// https://atcoder.jp/contests/abc442/tasks/abc442_g

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

using namespace std;

class Item
{
public:
    long long w, v, k;
    double perOne;

    Item(long long _w, long long _v, long long _k) : w(_w), v(_v), k(_k)
    {
        perOne = (double)v / (double)w;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long c;
    cin >> n >> c;

    vector<Item> items;

    for (int i = 0; i < n; i++)
    {
        long long w, v, k;
        cin >> w >> v >> k;

        items.push_back(Item(w, v, k));
    }

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.perOne > b.perOne;
    });

    long long ans = 0;

    

    cout << ans << "\n";

    return 0;
}