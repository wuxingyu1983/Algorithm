#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>

using namespace std;

#define DEBUG 0
#define MAX_N 500002

class House
{
public:
    unsigned int t;
    unsigned int max;
    int diff;

    House()
    {
        diff = t = max = 0;
    }
};

inline bool comp(House *a, House *b)
{
    return (a->diff > b->diff);
}

vector<House> houses(MAX_N);
multimap<int, int> edges;
vector<House *> children(MAX_N);

void init_houses(int curr, int parent)
{
    pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret = edges.equal_range(curr);

    int size = 0;
    for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
    {
        if (parent != it->second)
        {
            init_houses(it->second, curr);
        }
    }

    for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
    {
        if (parent != it->second)
        {
            children[size++] = &(houses[it->second]);
        }
    }

    if (0 < size)
    {
        // sort, desc
        sort(children.begin(), children.begin() + size, comp);

        int t = 0;
        int max = 0;

        for (vector<House *>::iterator it = children.begin(); it != children.begin() + size; it++)
        {
            if (t + (*it)->max + 1 > max)
            {
                max = t + (*it)->max + 1;
            }

            t += (*it)->t + 2;
        }

        houses[curr].t = t;
        if (1 != curr)
        {
            if (houses[curr].max < max)
            {
                houses[curr].max = max;
            }
        }
        else
        {
            if (houses[curr].max + houses[curr].t > max)
            {
                houses[curr].max = houses[curr].max + houses[curr].t;
            }
            else
            {
                houses[curr].max = max;
            }
        }

        houses[curr].diff = houses[curr].max - houses[curr].t;
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    for (size_t i = 1; i <= n; i++)
    {
        int c;
#if DEBUG
        inFile >> c;
#else
        cin >> c;
#endif

        houses[i].max = houses[i].diff = c;
    }

    for (size_t i = 1; i < n; i++)
    {
        int a, b;
#if DEBUG
        inFile >> a >> b;
#else
        cin >> a >> b;
#endif
        edges.insert(pair<int, int>(a, b));
        edges.insert(pair<int, int>(b, a));
    }

    init_houses(1, 0);

    cout << houses[1].max << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
