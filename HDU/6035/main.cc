// http://acm.hdu.edu.cn/showproblem.php?pid=6035
// https://cloud.tencent.com/developer/article/1087961
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
vector<unsigned int> sz(MAX_N);
vector<unsigned long long> sum(MAX_N);

unsigned int func(const unsigned int idx, const unsigned int parent, unsigned long long &cnt)
{
    sz[idx] = 1;

    unsigned long long all = 0;
    for (vector<unsigned int>::iterator it = roads[idx].begin(); it != roads[idx].end(); it ++)
    {
        if (parent != *it)
        {
            unsigned long long last = sum[nodes[idx]];
            sz[idx] += func(*it, idx, cnt);
            unsigned long long add = sum[nodes[idx]] - last;
            cnt += (sz[*it] - add) * (sz[*it] - add - 1) / 2;
            all += sz[*it] - add;
        }
    }
    sum[nodes[idx]] += all + 1; 

    return sz[idx];
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
        unsigned long long colorCnt = 0;

        // init
        colors.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        sum.assign(n + 1, 0);

        for (size_t i = 1; i <= n; i++)
        {
            unsigned int c;
#if DEBUG
            fscanf(fp, "%u", &c);
#else
            scanf("%u", &c);
#endif
            if (0 == colors[c])
            {
                colorCnt ++;
            }
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

        unsigned long long ans = 0;
        func(1, 0, ans);

        for (size_t i = 1; i <= n; i++)
        {
            if (0 < colors[i])
            {
                ans += (n - sum[i]) * (n - sum[i] - 1) / 2;
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
