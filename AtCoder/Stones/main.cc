// https://atcoder.jp/contests/dp/tasks/dp_k

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

using namespace std;

int a[100];
int dp[100002];     // 1 - 先手胜，0 - 先手负

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i < a[j])
            {
                break;
            }

            if (i == a[j])
            {
                dp[i] = 1;
                break;
            }

            if (dp[i - a[j]] == 0)
            {
                dp[i] = 1;
                break;
            }
        }
    }

    if (dp[k] == 1)
    {
        cout << "First" << endl;
    }
    else
    {
        cout << "Second" << endl;
    }

    return 0;
}
