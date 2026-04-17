// https://atcoder.jp/contests/arc149/tasks/arc149_b

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
#include <map>

using namespace std;

vector<int> vecA, vecB;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        vecA.push_back(a);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        int b;
        cin >> b;
        vecB.push_back(b);
    }

    return 0;
}
