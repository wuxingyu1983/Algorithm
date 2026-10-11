// https://codeforces.com/problemset/problem/506/A

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
#include <deque>

using namespace std;

const int MAXN = 30001;

int islands[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d;
    cin >> n >> d;

    for (int i = 0; i < n; i++)
    {
        int loc;
        cin >> loc;

        islands[loc] ++;
    }

    int left = 0;
    int right = 0;
    

    return 0;
}
