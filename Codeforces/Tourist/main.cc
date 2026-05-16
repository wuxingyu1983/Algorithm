// https://codeforces.com/contest/76/problem/F

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

using namespace std;

const int MAX_N = 100000;

class Event 
{
public:
    long long x, t;
    long long a, b;
    int ai, bi;
};

void deduplication(vector<long long> &xs)
{
    sort(xs.begin(), xs.end());               // 先对vector进行排序
    auto last = unique(xs.begin(), xs.end()); // 去除重复的元素
    xs.erase(last, xs.end());                 // 删除多余的元素
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Event> events;

    {
        Event e;
        e.x = 0;
        e.t = 0;

        events.push_back(e);
    }

    for (size_t i = 0; i < n; i++)
    {
        long long x, t;
        cin >> x >> t;

        Event e;
        e.x = x;
        e.t = t;

        events.push_back(e);
    }
    
    long long v;
    cin >> v;

    vector<long long> as, bs;
    for (size_t i = 0; i <= n; i++)
    {
        events[i].a = v * events[i].t - events[i].x;
        events[i].b = v * events[i].t + events[i].x;

        as.push_back(events[i].a);
        bs.push_back(events[i].b);
    }

    // a, b 去重
    deduplication(as);
    deduplication(bs);

    // 离散化
    for (size_t i = 0; i <= n; i++)
    {
        auto it = lower_bound(as.begin(), as.end(), events[i].a);
        events[i].ai = it - as.begin() + 1;

        it = lower_bound(bs.begin(), bs.end(), events[i].b);
        events[i].bi = it - bs.begin() + 1; 
    }

    int rslt = 0;
    
    
    cout << rslt << " ";

    rslt = 0;


    cout << rslt << "\n";

    return 0;
}
