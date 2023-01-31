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

class Edge
{
public:
    unsigned int x, y;

    Edge()
    {
        x = y = 0;
    }
};

bool cmp(Edge &a, Edge &b)
{
    bool ret = false;

    if (a.x < b.x)
    {
        ret = true;
    }
    else if (a.x == b.x)
    {
        return a.y <= b.y;
    }

    return ret;
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

    int n, m;
#if DEBUG
    inFile >> n >> m;
#else
    cin >> n >> m;
#endif

    vector<Edge> edges(m);
    for (size_t i_m = 0; i_m < m; i_m++)
    {
#if DEBUG
        inFile >> edges[i_m].x >> edges[i_m].y;
#else
        cin >> edges[i_m].x >> edges[i_m].y;
#endif
        if (edges[i_m].x > edges[i_m].y)
        {
            swap(edges[i_m].x, edges[i_m].y);
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    unsigned int k;
#if DEBUG
    inFile >> k;
#else
    cin >> k;
#endif

    // init
    vector<unsigned int> pa(n);
    iota(pa.begin(), pa.end(), 0);

    vector<unsigned int> set_size(n, 1);

    multimap<unsigned int, unsigned int> targets_map;
    unsigned int cnt = n - k;

    vector<unsigned int> targets(k);
    for (size_t i_k = 0; i_k < k; i_k++)
    {
#if DEBUG
        inFile >> targets[i_k];
#else
        cin >> targets[i_k];
#endif

        set_size[targets[i_k]] = 0;
    }
    
    for (size_t i_m = 0; i_m < m; i_m++)
    {
        if (set_size[edges[i_m].x] && set_size[edges[i_m].y])
        {
            // x, y not in targets
            unsigned int pa_x = find(pa, edges[i_m].x);
            unsigned int pa_y = find(pa, edges[i_m].y);

            if (pa_x != pa_y)
            {
                if (set_size[pa_x] < set_size[pa_y])
                {
                    unite(pa, pa_x, pa_y);
                    set_size[pa_y] += set_size[pa_x];
                }
                else
                {
                    unite(pa, pa_y, pa_x);
                    set_size[pa_x] += set_size[pa_y];
                }

                cnt --;
            }
        }
        else
        {
            targets_map.insert(make_pair(edges[i_m].x, edges[i_m].y));
            targets_map.insert(make_pair(edges[i_m].y, edges[i_m].x));
        }
    }

    vector<unsigned int> cnts;
    cnts.push_back(cnt);

    for (vector<unsigned int>::reverse_iterator rit = targets.rbegin(); rit != targets.rend(); rit++)
    {
        set_size[*rit] = 1;
        cnt ++;

        {
            auto pr = targets_map.equal_range(*rit);
            if (pr.first != std::end(targets_map))
            {
                for (auto iter = pr.first; iter != pr.second; ++iter)
                {
                    if (set_size[iter->second])
                    {
                        unsigned int pa_x = find(pa, *rit);
                        unsigned int pa_y = find(pa, iter->second);

                        if (pa_x != pa_y)
                        {
                            if (set_size[pa_x] < set_size[pa_y])
                            {
                                unite(pa, pa_x, pa_y);
                                set_size[pa_y] += set_size[pa_x];
                            }
                            else
                            {
                                unite(pa, pa_y, pa_x);
                                set_size[pa_x] += set_size[pa_y];
                            }

                            cnt--;
                        }
                    }
                }
            }
        }

        cnts.push_back(cnt);
    }

    for (vector<unsigned int>::reverse_iterator rit = cnts.rbegin(); rit != cnts.rend(); rit++)
    {
        cout << *rit << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
