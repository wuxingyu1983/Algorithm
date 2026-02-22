// https://www.luogu.com.cn/problem/P6623

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

const int MAX_N = 525100;

int vs[MAX_N];
vector<int> children[MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (size_t i = 1; i <= n; i++)
    {
        cin >> vs[i];
    }
    
    for (size_t i = 2; i <= n; i++)
    {
        int parent;
        cin >> parent;

        children[parent].push_back(i);
        children[i].push_back(parent);
    }
    
    

    return 0;
}
