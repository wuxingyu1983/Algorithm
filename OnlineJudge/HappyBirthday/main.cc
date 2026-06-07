// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3153

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
#include <utility>

using namespace std;

const int MAX_N = 501;
short dp[MAX_N][MAX_N];

void deduplication(vector<int> &vec)
{
    sort(vec.begin(), vec.end());               // 先对vector进行排序
    auto last = unique(vec.begin(), vec.end()); // 去除重复的元素
    vec.erase(last, vec.end());                 // 删除多余的元素
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> ks, tmps;
    ks.reserve(MAX_N);
    tmps.reserve(MAX_N);

    for (;;)
    {
        int n;
        cin >> n;

        if (0 == n)
            break;
        
        ks.clear();
        tmps.clear();
        for (size_t i = 0; i < n; i++)
        {
            int k;
            cin >> k;

            ks.push_back(k);
            tmps.push_back(k);
        }

        deduplication(tmps);

        
    }

    return 0;
}
