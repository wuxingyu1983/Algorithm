// https://www.spoj.com/problems/SUPPER/

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
#include <unordered_map>

using namespace std;

const int MAX_N = 100005;

int p[MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (size_t i = 0; i < 10; i++)
    {
        int n;
        cin >> n;

        for (size_t j = 0; j < n; j++)
        {
            cin >> p[j];
        }

    }

    return 0;
}
