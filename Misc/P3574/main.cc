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
    unsigned long long c, max;
    vector<House> children;

    House()
    {
        c = max = t = 0;
    }
};

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
            houses[curr].children.push_back(houses[it->second]);
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

        houses[i].c = c;
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

#if DEBUG
    inFile.close();
#endif

    return 0;
}
