// https://codeforces.com/contest/1856/problem/E2

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

bitset<1000002> dp;

void dfs(int node, const vector<vector<int>>& children, vector<long long>& sums)
{
    sums[node] = 1; // Count the current node

    for (int child : children[node])
    {
        dfs(child, children, sums);
        sums[node] += sums[child]; // Add the size of the subtree rooted at the child
    }
}

void solve(int n, const vector<vector<int>>& children, vector<long long>& sums, long long &ans)
{
    long long max = 0;

    for (int node = 1; node <= n; node++)
    {
        if (1 < children[node].size())
        {
            vector<long long> vec;
            for (int child : children[node])
            {
                vec.push_back(sums[child]);
            }
            sort(vec.begin(), vec.end());
            vec.push_back(0);
            
            dp.reset();
            dp[0] = 1;

            int pre = 0;
            int cnt = 0;
            for (int i = 0; i < vec.size(); i++)
            {
                if (pre != vec[i])
                {
                    int step = 1;
                    while (step <= cnt)
                    {
                        dp |= dp << (step * pre);
                        cnt -= step;
                        step <<= 1;
                    }

                    if (0 < cnt)
                    {
                        dp |= dp << (cnt * pre);
                    }

                    pre = vec[i];
                    cnt = 1;
                }
                else
                {
                    cnt ++;
                }
            }

            for (int i = (sums[node] - 1) / 2; i >= 1; i--)
            {
                if (dp[i])
                {
                    max = i;
                    break;
                }
            }

            ans += max * (sums[node] - 1 - max);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;

        children[p].push_back(i);
    }

    vector<long long> sums(n + 1, 0);

    dfs(1, children, sums);

    long long ans = 0;

    solve(n, children, sums, ans);

    cout << ans << "\n";

    return 0;
}
