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

bool cmp(const unsigned int * x, const unsigned int * y)
{
    return (*x) < (*y);
}

unsigned int find(vector<unsigned int> &pa, unsigned int x)
{
    return pa[x] == x ? x : pa[x] = find(pa, pa[x]);
}

// set x => set y
void unite(vector<unsigned int> &pa, unsigned int x, unsigned int y)
{
    pa[find(pa, x)] = find(pa, y);
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
    vector< set<unsigned int> > hunter;
    // 被其他吃的关系
    vector< set<unsigned int> > prey;

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
                if (hunter[pax].end() != hunter[pax].find(pay))
                {
                    cnt ++;
                    continue;
                }

                if (hunter[pay].end() != hunter[pay].find(pax))
                {
                    cnt ++;
                    continue;
                }

                // 合并
                {
                    unsigned int a = pax, b = pay;

                    if (hunter[b].size() < hunter[a].size())
                    {
                        swap(a, b);
                    }

                    // update hunter
                    for (set<unsigned int>::iterator it = hunter[a].begin(); it != hunter[a].end(); it++)
                    {
                        prey[*it].erase(a);
                        prey[*it].insert(b);

                        hunter[b].insert(*it);
                    }
                    hunter[a].clear();

                    // update prey
                    for (set<unsigned int>::iterator it = prey[a].begin(); it != prey[a].end(); it++)
                    {
                        hunter[*it].erase(a);
                        hunter[*it].insert(b);

                        prey[b].insert(*it);
                    }
                    prey[a].clear();

                    // a => b
                    unite(pa, a, b);
                }
            }
        }
        else
        {
            if (x == y)
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
