// http://acm.hdu.edu.cn/showproblem.php?pid=6035
// Virtual Tree : https://oi-wiki.org/graph/virtual-tree/
// LCA : https://cp-algorithms.com/graph/lca.html#the-idea-of-the-algorithm
// Segment Tree : https://oi-wiki.org/ds/seg/

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
#include <stack>

using namespace std;

#define DEBUG   0
#define MAX_N   200001

unsigned int n;
vector<unsigned int> colors(MAX_N);     // color count
vector<unsigned int> nodes(MAX_N);
vector< vector<unsigned int> > roads(MAX_N);

unsigned int func(const unsigned int idx, const unsigned int parent, const unsigned int c, unsigned long long &cnt)
{
    unsigned int ret = 0;

    if (c != nodes[idx])
    {
        ret ++;
    }

    for (vector<unsigned int>::iterator it = roads[idx].begin(); it != roads[idx].end(); it ++)
    {
        if (parent != *it)
        {
            unsigned int subRet = func(*it, idx, c, cnt);

            if (c == nodes[idx])
            {
                if (0 < subRet)
                {
                    cnt += (unsigned long long)subRet * (unsigned long long)(subRet - 1) / 2;
                }
            }
            else
            {
                ret += subRet;
            }
        }
    }

    if (1 == idx && c != nodes[idx])
    {
        // root and not == color
        cnt += (unsigned long long)ret * (unsigned long long)(ret - 1) / 2;
    }

    return ret;
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif
    
    unsigned int testcase = 1;
#if DEBUG
    while (fscanf(fp, "%u", &n))
#else
    while (scanf("%u", &n))
#endif
    {
        // init
        colors.assign(n + 1, 0);

        for (size_t i = 1; i <= n; i++)
        {
            unsigned int c;
#if DEBUG
            fscanf(fp, "%u", &c);
#else
            scanf("%u", &c);
#endif

            colors[c] ++;
            nodes[i] = c;
            roads[i].clear();
        }

        for (size_t i = 1; i < n; i++)
        {
            unsigned int x, y;
#if DEBUG
            fscanf(fp, "%u %u", &x, &y);
#else
            scanf("%u %u", &x, &y);
#endif
            roads[x].push_back(y);
            roads[y].push_back(x);
        }

        unsigned long long colorCnt = 0;
        unsigned long long ans = 0;

        for (size_t i = 1; i <= n; i++)
        {
            if (0 < colors[i])
            {
                colorCnt ++;

                func(1, 0, i, ans);
            }
        }

        ans = colorCnt * n * (n - 1) / 2 - ans;

        printf("Case #%u: %llu\n", testcase ++, ans);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
