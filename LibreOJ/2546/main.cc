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
#define MAX_N 100001
#define MAX_K 101
#define MOD 1000000007

unsigned int dp[MAX_N][4][MAX_K]; // [index][type][num]
vector< vector<unsigned int> > vertexes(MAX_N);
unsigned int cnt[MAX_N];
unsigned int n, k;
stack<unsigned int> nodes;
unsigned int parents[MAX_N];

void init(unsigned int node, unsigned int parent)
{
    for (vector<unsigned int>::iterator it = vertexes[node].begin(); it != vertexes[node].end(); it++)
    {
        if (parent != *it)
        {
            nodes.push(*it);
            init(*it, node);
            parents[*it] = node;
        }
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

    nodes.push(1);
    init(1, 0);

    while (0 < nodes.size())
    {
        unsigned int node = nodes.top();

        {
            cnt[node] = 1;

            if (1 < node && 1 == vertexes[node].size())
            {
                // not root, leaf, no children
                dp[node][0][0] = 1;
                dp[node][2][1] = 1;
            }
            else
            {
                vector<unsigned int>::iterator it = vertexes[node].begin();

                if (parents[node] == *it)
                {
                    it++;
                }

                cnt[node] += cnt[*it];

                // first
                {
                    unsigned int upper = k;

                    if (k > cnt[node])
                    {
                        upper = cnt[node];
                    }

                    for (int num = upper; num >= 0; num--)
                    {
                        // type : 0, no equipment in node, and node is not monitored
                        dp[node][0][num] = dp[*it][1][num];

                        // type : 1,  no equipment in node, and node is monitored
                        dp[node][1][num] = dp[*it][3][num];

                        if (0 < num)
                        {
                            // type : 2, equipment in node, and node is not monitored
                            dp[node][2][num] = dp[*it][0][num - 1] + dp[*it][1][num - 1];

                            if (MOD < dp[node][2][num])
                            {
                                dp[node][2][num] %= MOD;
                            }

                            // type : 3, equipment in node, and node is monitored
                            dp[node][3][num] = dp[*it][2][num - 1] + dp[*it][3][num - 1];

                            if (MOD < dp[node][3][num])
                            {
                                dp[node][3][num] %= MOD;
                            }
                        }
                    }
                }

                for (it++; it != vertexes[node].end(); it++)
                {
                    if (parents[node] != *it)
                    {
                        cnt[node] += cnt[*it];

                        unsigned int upper = k;

                        if (k > cnt[node])
                        {
                            upper = cnt[node];
                        }

                        for (int num = upper; num >= 0; num--)
                        {
                            for (int i = num; i >= 0; i--)
                            {
                                unsigned long long tmp = 0;
                                // type : 0, no equipment in node, and node is not monitored
                                if (num == i)
                                {
                                    tmp = (unsigned long long)dp[node][0][i] * (unsigned long long)dp[*it][1][num - i];
                                }
                                else
                                {
                                    tmp = dp[node][0][num] + (unsigned long long)dp[node][0][i] * (unsigned long long)dp[*it][1][num - i];
                                }

                                if (MOD < tmp)
                                {
                                    tmp %= MOD;
                                }

                                dp[node][0][num] = tmp;

                                // type : 1,  no equipment in node, and node is monitored
                                if (num == i)
                                {
                                    tmp = (unsigned long long)dp[node][0][i] * (unsigned long long)dp[*it][3][num - i] +
                                          (unsigned long long)dp[node][1][i] * (unsigned long long)(dp[*it][3][num - i] + dp[*it][1][num - i]);
                                }
                                else
                                {
                                    tmp = dp[node][1][num] + (unsigned long long)dp[node][0][i] * (unsigned long long)dp[*it][3][num - i] +
                                          (unsigned long long)dp[node][1][i] * (unsigned long long)(dp[*it][3][num - i] + dp[*it][1][num - i]);
                                }

                                if (MOD < tmp)
                                {
                                    tmp %= MOD;
                                }

                                dp[node][1][num] = tmp;

                                // type : 2, equipment in node, and node is not monitored
                                if (num == i)
                                {
                                    tmp = (unsigned long long)dp[node][2][i] * (unsigned long long)(dp[*it][0][num - i] +
                                                                                                    dp[*it][1][num - i]);
                                }
                                else
                                {
                                    tmp = dp[node][2][num] + (unsigned long long)dp[node][2][i] * (unsigned long long)(dp[*it][0][num - i] +
                                                                                                                       dp[*it][1][num - i]);
                                }

                                if (MOD < tmp)
                                {
                                    tmp %= MOD;
                                }

                                dp[node][2][num] = tmp;

                                // type : 3, equipment in node, and node is monitored
                                if (num == i)
                                {
                                    tmp = (unsigned long long)dp[node][2][i] * (unsigned long long)(dp[*it][2][num - i] + dp[*it][3][num - i]) + (unsigned long long)dp[node][3][i] * (unsigned long long)(dp[*it][0][num - i] + dp[*it][1][num - i] + dp[*it][2][num - i] + dp[*it][3][num - i]);
                                }
                                else
                                {
                                    tmp = dp[node][3][num] + (unsigned long long)dp[node][2][i] * (unsigned long long)(dp[*it][2][num - i] + dp[*it][3][num - i]) + (unsigned long long)dp[node][3][i] * (unsigned long long)(dp[*it][0][num - i] + dp[*it][1][num - i] + dp[*it][2][num - i] + dp[*it][3][num - i]);
                                }

                                if (MOD < tmp)
                                {
                                    tmp %= MOD;
                                }

                                dp[node][3][num] = tmp;
                            }
                        }
                    }
                }
            }
        }

        nodes.pop();
    }

    unsigned int ans = 0;

    ans = dp[1][1][k] + dp[1][3][k];

    printf("%u\n", ans);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
