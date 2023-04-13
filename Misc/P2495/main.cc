// https://www.luogu.com.cn/problem/P2495
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

#define DEBUG 0
#define MAX_N   250001

unsigned int depth[MAX_N];
unsigned int vertices[2 * MAX_N];    // path island index
unsigned int heights[2 * MAX_N * 4]; // path island height, segment tree
unsigned int minwgt[2 * MAX_N * 4];  // min weight, segment tree
unsigned int firsInPath[MAX_N];      // first in path

vector< vector<unsigned int> > roads(MAX_N);

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    unsigned int n;
#if DEBUG
    fscanf(fp, "%u", &n);
#else
    scanf("%u", &n);
#endif

    for (size_t i = 0; i < n - 1; i++)
    {
        unsigned int u, v, w;
#if DEBUG
        fscanf(fp, "%u %u %u", &u, &v, &w);
#else
        scanf("%u %u %u", &u, &v, &w);
#endif


    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
