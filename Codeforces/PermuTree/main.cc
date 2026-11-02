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

void dfs(int node, const vector<vector<int>>& children, vector<int>& sums)
{
    sums[node] = 1; // Count the current node

    for (int child : children[node])
    {
        dfs(child, children, sums);
        sums[node] += sums[child]; // Add the size of the subtree rooted at the child
    }
}

void solve(int node, const vector<vector<int>>& children, vector<int>& sums, long long &ans)
{
    long long max = 0;

    int left = 0;
    int right = sums[node] - 1; // Exclude the current node

    for (int child : children[node])
    {
        left += sums[child];
        right -= sums[child];
        long long current = (long long)left * (long long)right;
        if (current > max)
        {
            max = current;
        }

        solve(child, children, sums, ans);
    }

    ans += max;
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

    vector<int> sums(n + 1, 0);

    dfs(1, children, sums);

    long long ans = 0;

    solve(1, children, sums, ans);

    cout << ans << "\n";

    return 0;
}
