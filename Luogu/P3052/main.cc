// https://www.luogu.com.cn/problem/P3052
// 状压DP

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
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
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>
#include <cstring>

using namespace std;

#define MAX_N   18

int n, w;
int c[MAX_N];

class Item
{
public:
    int elevator;
    int remain;

    Item() {}
};

Item dp[262144];

int main()
{
    cin >> n >> w;

    for (size_t i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    
    

    return 0;
}
