// https://www.luogu.com.cn/problem/P3092

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

#define MAX_K   16 
#define MAX_N   100000
#define MAX_2K  65536

unsigned int k, n;
int coins[MAX_K];
int costs[MAX_N];

class Item
{
public:
    unsigned short state;
    int remain;
    Item * prev, * next;

    Item() {}
};

Item dp[MAX_2K];
Item * head[MAX_K + 1];

int main()
{
    cin >> k >> n;

    for (size_t i = 0; i < k; i++)
    {
        cin >> coins[i];
    }

    for (size_t i = 0; i < n; i++)
    {
        cin >> costs[i];
    }



    return 0;
}
