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
#define MAX_N       1000001

class Node
{
public:
    unsigned long long cnt;
    unsigned long long sum;
    
    unsigned long long sump;    // sum from parent;

    int parent; 
    vector<int> leafs;

    Node()
    {
        cnt = 1;
    }
};

Node nodes[MAX_N];
unsigned long long sums[MAX_N];
vector<int> edges[MAX_N];
int n;

void build(int p)
{
    for (vector<int>::iterator it = edges[p].begin(); it != edges[p].end(); it ++)
    {
        if (*it != nodes[p].parent)
        {
            nodes[p].leafs.push_back(*it);
            nodes[*it].parent = p;
            
            build(*it);

            nodes[p].cnt += nodes[*it].cnt;
            nodes[p].sum += nodes[*it].sum + nodes[*it].cnt;
        }
    }
}

void proc(int p)
{
    for (vector<int>::iterator it = nodes[p].leafs.begin(); it != nodes[p].leafs.end(); it ++)
    {
        unsigned long long sump = 0;

        sump += nodes[p].sump;
        sump += nodes[p].sum - nodes[*it].sum - nodes[*it].cnt;
        sump += n - nodes[*it].cnt;

        nodes[*it].sump = sump;

        sums[*it] = sump + nodes[*it].sum;

        proc(*it);
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    for (size_t i = 1; i < n; i ++)
    {
        int u, v;
#if DEBUG
        inFile >> u >> v;
#else
        cin >> u >> v;
#endif

        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    // init root start from 1
    build(1);

    sums[1] = nodes[1].sum;

    proc(1);

    int index = 1;
    unsigned long long max = sums[1];
    for (size_t i = 2; i <= n; i++)
    {
        if (sums[i] > max)
        {
            index = i;
            max = sums[i];
        }
    }

    cout << index << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
