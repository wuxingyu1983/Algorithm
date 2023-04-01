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
#include <queue>

using namespace std;

#define DEBUG 0
#define MAX_N 500002

class House
{
public:
    unsigned int t;
    unsigned int max;
    int diff;
    int depth;

    vector<House *> children;

    House()
    {
        depth = diff = t = max = 0;
    }
};

inline bool comp(House *a, House *b)
{
    return (a->diff > b->diff);
}

inline bool compDepth(House * a, House * b)
{
    return (a->depth > b->depth);
}

vector<House> raws(MAX_N);
vector<House *> houses(MAX_N);
vector< vector<int> > edges(MAX_N);

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

        raws[i].max = raws[i].diff = c;
        houses[i] = &(raws[i]);
    }

    for (size_t i = 1; i < n; i++)
    {
        int a, b;
#if DEBUG
        inFile >> a >> b;
#else
        cin >> a >> b;
#endif
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    houses[1]->depth = 1;

    queue<int> que;
    que.push(1);
    while (0 < que.size())
    {
        int curr = que.front();
        int depth = houses[curr]->depth;

        for (vector<int>::iterator it = edges[curr].begin(); it != edges[curr].end(); it++)
        {
            if (0 == houses[*it]->depth)
            {
                houses[curr]->children.push_back(houses[*it]);
                houses[*it]->depth = depth + 1;
                que.push(*it);
            }
        }

        que.pop();
    }

    // sort houses by depth desc
    sort(houses.begin() + 1, houses.begin() + 1 + n, compDepth);

    for (size_t curr = 1; curr <= n; curr++)
    {
        if (0 < houses[curr]->children.size())
        {
            // sort, desc, greedy
            sort(houses[curr]->children.begin(), houses[curr]->children.end(), comp);

            int t = 0;
            int max = 0;

            for (vector<House *>::iterator it = houses[curr]->children.begin(); it != houses[curr]->children.end(); it++)
            {
                if (t + (*it)->max + 1 > max)
                {
                    max = t + (*it)->max + 1;
                }

                t += (*it)->t + 2;
            }

            houses[curr]->t = t;
            if (n != curr)
            {
                if (houses[curr]->max < max)
                {
                    houses[curr]->max = max;
                }
            }
            else
            {
                if (houses[curr]->max + houses[curr]->t > max)
                {
                    houses[curr]->max = houses[curr]->max + houses[curr]->t;
                }
                else
                {
                    houses[curr]->max = max;
                }
            }

            houses[curr]->diff = houses[curr]->max - houses[curr]->t;
        }
    }

    cout << houses[n]->max << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
