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
#define MAX_COL     30001

vector<unsigned int> pa(MAX_COL);
vector<unsigned int> paSize(MAX_COL, 1);
vector<unsigned int> offset(MAX_COL, 0);

unsigned int find(unsigned int x)
{
    unsigned int ret = x;

    if (pa[x] != x)
    {
        ret = find(pa[x]);
        offset[x] += offset[pa[x]];
        pa[x] = ret;
    }

    return ret;
}

// set x => set y
void unite(unsigned int x, unsigned int y)
{
    unsigned int pax = find(x);
    unsigned int pay = find(y);

    if (pax == pay)
    {
        return;
    }

    offset[pax] = paSize[pay];
    paSize[pay] += paSize[pax];

    pa[pax] = pay;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
#endif

    // init
    iota(pa.begin(), pa.end(), 0);

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        char op;
        unsigned int i, j;
#if DEBUG
        inFile >> op >> i >> j;
#else
        cin >> op >> i >> j;
#endif

        if ('M' == op)
        {
            // i --> j
            unite(find(i), find(j));
        }
        else
        {
            if (i == j)
            {
                cout << 0 << endl;
            }
            else
            {
                unsigned int pai = find(i);
                unsigned int paj = find(j);

                if (pai == paj)
                {
                    if (offset[i] < offset[j])
                    {
                        cout << offset[j] - offset[i] - 1 << endl;
                    }
                    else
                    {
                        cout << offset[i] - offset[j] - 1 << endl;
                    }
                }
                else
                {
                    cout << -1 << endl;
                }
            }
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
