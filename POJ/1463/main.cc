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
#define MAX_N 1502

vector< vector<unsigned int> > roads(MAX_N);
unsigned int dp[MAX_N][2];

void func(unsigned int node, unsigned int parent)
{
    dp[node][1] = 1;
    for (vector<unsigned int>::iterator it = roads[node].begin(); it != roads[node].end(); it++)
    {
        if (parent != *it)
        {
            func(*it, node);

            dp[node][0] += dp[*it][1];
            if (dp[*it][0] > dp[*it][1])
            {
                dp[node][1] += dp[*it][1];
            }
            else
            {
                dp[node][1] += dp[*it][0];
            }
        }
    }

    roads[node].clear();
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
    FILE *fp = fopen("input.txt", "r");
#endif

    unsigned int n;
#if DEBUG
    while (inFile >> n)
#else
    while (cin >> n)
//    while (scanf("%u", &n))
#endif
    {
        for (size_t i = 0; i < n; i++)
        {
            unsigned int self, num;
#if DEBUG
            fscanf(fp, "%u:(%u)", &self, &num);
#else
            scanf("%u:(%u)", &self, &num);
#endif

            for (size_t j = 0; j < num; j++)
            {
                unsigned int node;
#if DEBUG
                inFile >> node;
#else
                cin >> node;
#endif
                roads[self].push_back(node);
                roads[node].push_back(self);
            }
        }

        unsigned int ans = 0;

        func(0, 0);
        ans = dp[0][0];
        if (ans > dp[0][1])
        {
            ans = dp[0][1];
        }

        cout << ans << endl;

        memset(dp, 0, MAX_N * 2 * sizeof(unsigned int));
    }

#if DEBUG
    inFile.close();
    fclose(fp);
#endif

    return 0;
}
