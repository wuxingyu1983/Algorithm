// https://codeforces.com/problemset/problem/10/D

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

const int MAX_NM = 500;

int main()
{
    int n, m;
    vector<int> vecF;
    vector<int> vecS;

    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        vecF.push_back(tmp);
    }

    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;
        vecS.push_back(tmp);
    }
    


    return 0;
}
