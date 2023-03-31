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

#define DEBUG       0
#define MAX_N       500002

class House
{
public:
    unsigned int t;
    unsigned int max;
    vector<House *> children;

    House()
    {
        t = max = 0;
    }
};

bool comp(House * a, House * b)
{
    return (a->max - a->t > b->max - b->t);
}

vector<House> houses(MAX_N);
multimap<int, int> edges;

void init_houses(int curr, int parent)
{
    pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret = edges.equal_range(curr);

    for(multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
    {
        if (parent != it->second)
        {
            init_houses(it->second, curr);
            houses[curr].children.push_back(&(houses[it->second]));
        }
    }

    if (0 < houses[curr].children.size())
    {
        // sort, desc
        sort(houses[curr].children.begin(), houses[curr].children.end(), comp);

        int t = 0;
        int max = 0;

        for (vector<House *>::iterator it = houses[curr].children.begin(); it != houses[curr].children.end(); it++)
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
            if (houses[curr].max > max)
            {
            }
            else
            {
                houses[curr].max = max;
            }
        }
        else
        {
            if (houses[curr].max + houses[curr].t  > max)
            {
                houses[curr].max = houses[curr].max + houses[curr].t;
            }
            else
            {
                houses[curr].max = max;
            }
        }
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

        houses[i].max = c;
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

