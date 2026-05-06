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
    int x, t;
};

bool myfunc(Event &a, Event &b)
{
    bool bRet = false;

    if (a.t < b.t)
    {
        bRet = true;
    }
    else if (a.t == b.t)
    {
        if (a.x < b.x)
        {
            bRet = true;
        }
    }

    return bRet;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Event> events;
    for (size_t i = 0; i < n; i++)
    {
        int x, t;
        cin >> x >> t;

        Event e;
        e.x = x;
        e.t = t;

        events.push_back(e);
    }
    
    int v;
    cin >> v;

    // sort
    sort(events.begin(), events.end(), myfunc);

    

    return 0;
}
