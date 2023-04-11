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
#define MAX_N 100001
#define MAX_K 101
#define MOD 1000000007

unsigned long long dp[MAX_N][2][4][MAX_K]; // [index][active][type][num]
unsigned char active[MAX_N];               // 0, 1
vector< vector<unsigned int> > vertexes(MAX_N);
unsigned int cnt[MAX_N];
unsigned int n, k;

void func(unsigned int node, unsigned int parent)
{
    unsigned char act = active[node];

    cnt[node] = 1;
    if (0 < parent && 1 == vertexes[node].size())
    {
        // leaf, no children
        dp[node][act][0][0] = 1;
        dp[node][act][2][1] = 1;
    }
    else
    {
        vector<unsigned int>::iterator it = vertexes[node].begin();

        if (parent == *it)
        {
            it++;
        }

        func(*it, node);
        cnt[node] += cnt[*it];

        // first
        {
            unsigned char chact = active[*it];

            unsigned int upper = k;
            if(k > cnt[node])
            {
                upper = cnt[node];
            }
            for (size_t num = 0; num <= upper; num++)
            {
                // type : 0, no equipment in node, and node is not monitored
                dp[node][act][0][num] = dp[*it][chact][1][num];

                // type : 1,  no equipment in node, and node is monitored
                dp[node][act][1][num] = dp[*it][chact][3][num];

                if (0 < num)
                {
                    // type : 2, equipment in node, and node is not monitored
                    dp[node][act][2][num] = dp[*it][chact][0][num - 1] + dp[*it][chact][1][num - 1];

                    // type : 3, equipment in node, and node is monitored
                    dp[node][act][3][num] = dp[*it][chact][2][num - 1] + dp[*it][chact][3][num - 1];
                }
            }
        }

        for (it++; it != vertexes[node].end(); it++)
        {
            if (parent != *it)
            {
                func(*it, node);
                cnt[node] += cnt[*it];

                act = 1 - act;
                unsigned char chact = active[*it];

                // clear
                memset(dp[node][act], 0, 4 * sizeof(unsigned long long) * MAX_K);

                unsigned int upper = k;
                if (k > cnt[node])
                {
                    upper = cnt[node];
                }
                for (size_t num = 0; num <= upper; num++)
                {
                    for (size_t i = 0; i <= num; i++)
                    {
                        // type : 0, no equipment in node, and node is not monitored
                        dp[node][act][0][num] += dp[node][1 - act][0][i] * dp[*it][chact][1][num - i];
                        dp[node][act][0][num] %= MOD;

                        // type : 1,  no equipment in node, and node is monitored
                        dp[node][act][1][num] += dp[node][1 - act][0][i] * dp[*it][chact][3][num - i];
                        dp[node][act][1][num] += dp[node][1 - act][1][i] * (dp[*it][chact][3][num - i] + dp[*it][chact][1][num - i]);
                        dp[node][act][1][num] %= MOD;

                        //                        if (0 < num && i < num)
                        {
                            // type : 2, equipment in node, and node is not monitored
                            dp[node][act][2][num] += dp[node][1 - act][2][i] * (dp[*it][chact][0][num - i] + dp[*it][chact][1][num - i]);
                            dp[node][act][2][num] %= MOD;

                            // type : 3, equipment in node, and node is monitored
                            dp[node][act][3][num] += dp[node][1 - act][2][i] * (dp[*it][chact][2][num - i] + dp[*it][chact][3][num - i]);
                            dp[node][act][3][num] += dp[node][1 - act][3][i] * (dp[*it][chact][0][num - i] + dp[*it][chact][1][num - i] +
                                                                                dp[*it][chact][2][num - i] + dp[*it][chact][3][num - i]);
                            dp[node][act][3][num] %= MOD;
                        }
                    }
                }
            }
        }

        active[node] = act;
    }
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

#if DEBUG
    fscanf(fp, "%u %u", &n, &k);
#else
    scanf("%u %u", &n, &k);
#endif

    for (size_t i = 0; i < n - 1; i++)
    {
        unsigned int v1, v2;

#if DEBUG
        fscanf(fp, "%u %u", &v1, &v2);
#else
        scanf("%u %u", &v1, &v2);
#endif

        vertexes[v1].push_back(v2);
        vertexes[v2].push_back(v1);
    }

    unsigned long long ans = 0;

    func(1, 0);

    ans = dp[1][active[1]][1][k] + dp[1][active[1]][3][k];
    ans %= MOD;

    printf("%llu\n", ans);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
