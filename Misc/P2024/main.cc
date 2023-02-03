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

#define DEBUG 1

unsigned int find(vector<unsigned int> &pa, unsigned int x)
{
    return pa[x] == x ? x : pa[x] = find(pa, pa[x]);
}

// set x => set y
unsigned int unite(vector<unsigned int> &pa, unsigned int x, unsigned int y)
{
    if (0 == x)
    {
        return y;
    }
    if (0 == y)
    {
        return x;
    }
    return pa[find(pa, x)] = find(pa, y);
}

void merge(vector<unsigned int> &pa, vector<unsigned int> &hunter, vector<unsigned int> &prey, unsigned int pax, unsigned int pay)
{
    unsigned int a = pax, b = pay;

    if (a > b)
    {
        swap(a, b);
    }

    // update hunter
    unite(pa, hunter[a], hunter[b]);
    
    // update prey
    unite(pa, prey[a], prey[b]);
    
    // a => b
    unite(pa, a, b);

    hunter[hunter[b]] = prey[b];
    prey[prey[b]] = hunter[b];
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned int n, k;
#if DEBUG
    inFile >> n >> k;
#else
    cin >> n >> k;
#endif

    // init
    vector<unsigned int> pa(n + 1);
    iota(pa.begin(), pa.end(), 0);

    // 吃其他的关系
    vector<unsigned int> hunter(n + 1, 0);
    // 被其他吃的关系
    vector<unsigned int> prey(n + 1, 0);

    unsigned int cnt = 0;
    for (size_t i_k = 0; i_k < k; i_k++)
    {
        unsigned int op, x, y;
#if DEBUG
        inFile >> op >> x >> y;
#else
        cin >> op >> x >> y;
#endif

        if (n < x || n < y)
        {
            cnt ++;
            continue;
        }

        if (1 == op)
        {
            unsigned int pax = find(pa, x);
            unsigned int pay = find(pa, y);
            if (pax != pay)
            {
                // 查看 pax、pay 之间是否有猎杀关系
                if (hunter[pax] == pay)
                {
                    cnt ++;
                    continue;
                }

                if (hunter[pay] == pax)
                {
                    cnt ++;
                    continue;
                }

                // 合并
                merge(pa, hunter, prey, pax, pay);
            }
        }
        else
        {
            unsigned int pax = find(pa, x);
            unsigned int pay = find(pa, y);

            if (pax == pay)
            {
                cnt ++;
                continue;
            }
        }
    }

    cout << cnt << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
