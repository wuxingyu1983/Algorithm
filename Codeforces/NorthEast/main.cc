// https://codeforces.com/problemsets/acmsguru/problem/99999/521

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

class City
{
public:
    int idx;
    int x, y;
    int ix, iy;

    City() : idx(0), x(0), y(0), ix(0), iy(0) {}
};

void deduplication(vector<int> &vec)
{
    sort(vec.begin(), vec.end());               // 先对vector进行排序
    auto last = unique(vec.begin(), vec.end()); // 去除重复的元素
    vec.erase(last, vec.end());                 // 删除多余的元素
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<City> cites(n);
    vector<int> xs(n), ys(n);
    for (size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;

        cites[i].idx = i + 1;

        cites[i].x = x;
        cites[i].y = y;

        xs[i] = x;
        ys[i] = y;
    }

    deduplication(xs);
    deduplication(ys);

    for (size_t i = 0; i < n; i++)
    {
        auto it = lower_bound(xs.begin(), xs.end(), cites[i].x);
        cites[i].ix = it - xs.begin() + 1;

        it = lower_bound(ys.begin(), ys.end(), cites[i].y);
        cites[i].iy = it - ys.begin() + 1;
    }



    return 0;
}
